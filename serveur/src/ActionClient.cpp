/*************************************************************************
                           ActionClient  -  description
                             -------------------
    début                : ...
    copyright            : (C) 2011 par Arnaud Lahache
*************************************************************************/

//---------- Réalisation de la classe <ActionClient> (fichier Actionclient->cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>			// pipe
#include <fcntl.h>			// O_NONBLOCK

//------------------------------------------------------ Include personnel
#include "ActionClient.h"
#include "DataTransfertTCPPull.h"
#include "DataTransfertTCPPush.h"
#include "DataTransfertUDPPull.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void ActionClient::Execute(epoll_event event)
{

	char buffer[MSG_BUFFER_SIZE];
	
	if(event.events & EPOLLERR)
	{
		// ERREUR QUELCONQUE
		cerr << "[" << fd << "] Erreur de transfert" << endl;
	}
	else if(event.events & EPOLLIN)
	{
		// DEMANDE DE LECTURE
		//cout << "[" << fd << "] Réception d'une requête de lecture..." << endl;
		
		sockaddr_in addr;
		string client_addr;
		Client* client;
		
		// On va recevoir le message différement selon qu'on soit en UDP ou TCP :
		int received;
		if(stream->GetProtocol() == UDP_PULL || stream->GetProtocol() == UDP_PUSH)
		{
			int addrsize = sizeof(addr);
			received = recvfrom(fd, buffer, MSG_BUFFER_SIZE, 0, (sockaddr*) &addr, (socklen_t*) &addrsize);
			client_addr = addrToKey(addr);
			
			// On récupère le client associé :
			client = &clients[client_addr];
				client->clientAddress=addr.sin_addr;
		}
		else if(stream->GetProtocol() == TCP_PULL || stream->GetProtocol() == TCP_PUSH)
		{
			received = recv(fd, buffer, MSG_BUFFER_SIZE, 0);
			
			// On récupère le client associé :
			client_addr = tcp_client;
			client = &clients[client_addr];
		}
		
		if(received > 0)
		{
			// LECTURE D'UN MESSAGE
			buffer[received] = '\0';
			//cout << "[" << fd << "] Lecture de " << received << " octets : " << buffer << endl;
			
			stringstream message(buffer);
			string line;
			while(getline(message, line))	// Enlève LF
			{
				line.resize(line.size()-1);		// Enlever CR
				if(line.empty()) continue;		// Lignes vides
				stringstream sline(line);
				string command;
				sline >> command;
				
				bool transfertStarted = client->transfertStarted;
				if(!transfertStarted)
				{
					// DEBUT DU TRANSFERT
				
					bool beginTransfert = false;
					if(command == "get" || command == "GET")
					{
						sline >> videoId;
					}
					else if(command == "fragment_size" || command == "FRAGMENT_SIZE")
					{
						sline >> client->fragmentSize;
						beginTransfert = true;
					}
					else if(command == "listen_port" || command == "LISTEN_PORT")
					{
						sline >> client->clientPort;
						if(stream->GetProtocol() == TCP_PULL || stream->GetProtocol() == TCP_PUSH)
							beginTransfert = true;
					}
					
					// On va créer le transfert
					if(beginTransfert)
					{
						// On va créer le pipe de communication avec le thread :
						int pipefds[2];
						//int flags = 0;
						//if(stream->GetProtocol() == UDP_PUSH || stream->GetProtocol() == TCP_PUSH)
						//	flags = flags | O_NONBLOCK;
						//pipe2(pipefds, flags);
						pipe(pipefds);
						if(stream->GetProtocol() == UDP_PUSH || stream->GetProtocol() == TCP_PUSH)
							setNonBlocking(pipefds[1]);
						client->pipefd = pipefds[1];
					
						// On va créer le transfert :
						if(stream->GetProtocol() == TCP_PUSH)
						{
							client->transfert = new DataTransfertTCPPush(*stream, client->clientAddress, client->clientPort, pipefds[0]);
						}
						else if(stream->GetProtocol() == TCP_PULL)
						{
							client->transfert = new DataTransfertTCPPull(*stream, client->clientAddress, client->clientPort, pipefds[0]);
						}
						else if(stream->GetProtocol() == UDP_PUSH)
						{
							//client->transfert = new DataTransfertUDPPull(*stream, client->clientAddress, client->clientPort, client->fragmentSize, pipefds[0]);
						}
						else if(stream->GetProtocol() == UDP_PULL)
						{
							client->transfert = new DataTransfertUDPPull(*stream, client->clientAddress, client->clientPort, client->fragmentSize, pipefds[0]);
						}
						
						// On va enfin créer un nouveau thread qui partira de ce transfert :
						int err = pthread_create(&(client->transfertThread), NULL, client->transfert->BeginThread, client->transfert);
						if(err)
						{
							cerr << "Erreur : pthread_create" << endl;
							Disconnect(client_addr);
						}
						
						client->transfertStarted = true;
					}
					
				} // -- début du transfert
				else
				{
					// TRANSFERT EN COURS

					if(command == "end" || command == "END" || command == "close" || command == "CLOSE")
					{
						// DECONNEXION
						string pipecmd = "END";
						write(client->pipefd, pipecmd.c_str(), pipecmd.size()+1);
						int err = pthread_join(client->transfertThread, NULL);
						if(err)
						{
							cerr << "Erreur : pthread_join" << endl;
						}
						Disconnect(client_addr);
					}
					
					else if(stream->GetProtocol() == TCP_PULL || stream->GetProtocol() == UDP_PULL)
					{
						// PROTOCOLE PULL
						
						if(command == "get" || command == "GET")
						{
							string image_id;
							sline >> image_id;
							write(client->pipefd, image_id.c_str(), image_id.size()+1);
						}
						
					} // -- commande pull
					else
					{
						// PROTOCOLE PUSH
						
						if(command == "start" || command == "START")
						{
							string pipecmd = "START";
							write(client->pipefd, pipecmd.c_str(), pipecmd.size()+1);
						}
						else if(command == "pause" || command == "PAUSE")
						{
							string pipecmd = "PAUSE";
							write(client->pipefd, pipecmd.c_str(), pipecmd.size()+1);
						}
						else if(command == "alive" || command == "ALIVE")
						{
							string pipecmd = "ALIVE";
							write(client->pipefd, pipecmd.c_str(), pipecmd.size()+1);
						}
						else if(command == "listen_port" || command == "LISTEN_PORT")
						{
							sline >> client->clientPort;
							// TODO : récréer le transfert avec le port listenPort
						}
						
					} // -- commande push
					
				} // -- transfert en cours
				
				line.clear();
			} // -- ligne
			
		} // -- message
		else
		{
			// DECONNEXION
			// Message nul ou < 0
			Disconnect(client_addr);
		}
		
	}
}

void ActionClient::Disconnect(string client_addr)
{
	//cout << "[" << fd << "] Déconnexion du client" << endl;
	
	delete clients[client_addr].transfert;
	
	if(client_addr == tcp_client)
	{
		// On supprime le descipteur de la connexion :
		io.RemoveAction(fd);
		close(fd);
	
		// On supprime le client de l'action de connexion :
		connection->RemoveClient(this);
	}
	
}

void ActionClient::SetTCPClient(sockaddr_in _tcpClientAddr, ActionConnection* _connection)
{
	connection = _connection;
	
	tcp_client = addrToKey(_tcpClientAddr);
	clients[tcp_client].clientAddress = _tcpClientAddr.sin_addr;
}

//-------------------------------------------- Constructeurs - destructeur


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

string ActionClient::addrToKey(sockaddr_in addr)
{
	stringstream ss;
	ss << inet_ntoa(addr.sin_addr);
	ss << ":" << ntohs(addr.sin_port);
	return ss.str();
}

void ActionClient::setNonBlocking(int fd)
{
	int flags = fcntl(fd, F_GETFL, 0);
	fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}
