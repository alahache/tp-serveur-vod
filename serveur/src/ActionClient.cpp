/*************************************************************************
                           ActionClient  -  description
                             -------------------
    début                : ...
    copyright            : (C) 2011 par Arnaud Lahache
*************************************************************************/

//---------- Réalisation de la classe <ActionClient> (fichier ActionClient.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <sstream>
#include <string>
#include <sys/socket.h>

//------------------------------------------------------ Include personnel
#include "ActionClient.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void ActionClient::Execute(epoll_event event)
{

	char buffer[BUFFER_SIZE];
	
	if(event.events & EPOLLHUP)
	{
		// DECONNEXION
		Disconnect();
	}
	else if(event.events & EPOLLERR)
	{
		// ERREUR QUELCONQUE
		cerr << "[" << fd << "] Erreur de transfert" << endl;
	}
	else if(event.events & EPOLLIN)
	{
		// DEMANDE DE LECTURE
		//cout << "[" << fd << "] Réception d'une requête de lecture..." << endl;
		
		int received = recv(fd, buffer, BUFFER_SIZE, 0);
		//int received = read(fd, buffer, BUFFER_SIZE);
		if(received > 0)
		{
			// LECTURE D'UN MESSAGE
			buffer[received] = '\0';
			//cout << "[" << fd << "] Lecture de " << received << " octets : " << buffer << endl;
			
			stringstream message(buffer);
			string line;
			while(getline(message, line))	// Enlève LF
			{
			
				if(line.empty()) continue;		// Lignes vides
				line.resize(line.size()-1);		// Enlever CR
				stringstream sline(line);
				string command;
				sline >> command;
				
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
						sline >> fragmentSize;
						beginTransfert = true;
					}
					else if(command == "listen_port" || command == "LISTEN_PORT")
					{
						sline >> clientPort;
						if(stream.GetProtocol() == TCP_PULL || stream.GetProtocol() == TCP_PUSH)
							beginTransfert = true;
					}
					
					// On va créer le transfert
					if(beginTransfert)
					{
					
						// On va créer le pipe de communication avec le thread :
						int pipefds[2];
						int flags = 0;
						if(stream.GetProtocol() == UDP_PUSH || stream.GetProtocol() == UDP_PULL)
							flags = flags | O_NONBLOCK;
						pipe2(pipefds, flags);
						pipefd = pipefds[1];
					
						// On va créer le transfert :
						if(stream.GetProtocol() == TCP_PUSH)
						{
							// transfert = new DataTransfertTCPPush(stream, clientAddress, listenPort, pipefds[0]);
						}
						else if(stream.GetProtocol() == TCP_PULL)
						{
							//transfert = new DataTransfertTCPPull(stream, clientAddress, listenPort, pipefds[0]);
						}
						else if(stream.GetProtocol() == UDP_PUSH)
						{
							//transfert = new DataTransfertUDPPush(stream, clientAddress, listenPort, pipefds[0], fragmentSize);
						}
						else if(stream.GetProtocol() == UDP_PULL)
						{
							//transfert = new DataTransfertUDPPull(stream, clientAddress, listenPort, pipefds[0], fragmentSize);
						}
						
						// On va enfin créer un nouveau thread qui partira de ce transfert :
						int err = pthread_create(&transfertThread, NULL, transfert->Begin, NULL);
						if(err)
						{
							cerr << "Erreur : pthread_create" << endl;
							Disconnect();
						}
						
						transfertStarted = true;
					}
					
				} // -- début du transfert
				else
				{
					// TRANSFERT EN COURS
				
					if(command == "end" || command == "END" || command == "close" || command == "CLOSE")
					{
						// DECONNEXION
						string pipecmd = "END";
						write(pipefd, pipecmd.c_str(), pipecmd.size()+1);
						int err = pthread_join(transfertThread, NULL);
						if(err)
						{
							cerr << "Erreur : pthread_join" << endl;
						}
						Disconnect();
					}
					
					else if(stream.GetProtocol() == TCP_PULL || stream.GetProtocol() == UDP_PULL)
					{
						// PROTOCOLE PULL
						
						if(command == "get" || command == "GET")
						{
							string image_id;
							sline >> image_id;
							
							write(pipefd, image_id.c_str(), image_id.size()+1);
						}
						
					} // -- commande pull
					else
					{
						// PROTOCOLE PUSH
						
						if(command == "start" || command == "START")
						{
							string pipecmd = "START";
							write(pipefd, pipecmd.c_str(), pipecmd.size()+1);
						}
						else if(command == "pause" || command == "PAUSE")
						{
							string pipecmd = "PAUSE";
							write(pipefd, pipecmd.c_str(), pipecmd.size()+1);
						}
						else if(command == "alive" || command == "ALIVE")
						{
							string pipecmd = "ALIVE";
							write(pipefd, pipecmd.c_str(), pipecmd.size()+1);
						}
						else if(command == "listen_port" || command == "LISTEN_PORT")
						{
							sline >> listenPort;
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
			Disconnect();
		}
		
	}
}

void ActionClient::Disconnect()
{
	//cout << "[" << fd << "] Déconnexion du client" << endl;

	// On supprime le descipteur de la connexion :
	io.RemoveAction(fd);
	close(fd);
	
	// On supprime le client de l'action de connexion :
	connection.RemoveClient(this);
}


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

