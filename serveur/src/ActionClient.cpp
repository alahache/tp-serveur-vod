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
	int fd = event.data.fd;
	
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
			string line, command;
			while(getline(message, line))		// Enlève LF
			{
				if(line.empty()) continue;		// Lignes vides
				line.resize(command.size()-1);	// Enlever CR
				stringstream sline(line);
				sline >> command;
				
				if(!transfertStarted)
				{
					// DEBUT DU TRANSFERT
				
					if(command == "get" || command == "GET")
					{
						sline >> videoId;
					}
					else if(command == "fragment_size" || command == "FRAGMENT_SIZE")
					{
						sline >> fragmentSize;
						transfertStarted = true;
					}
					else if(command == "listen_port" || command == "LISTEN_PORT")
					{
						sline >> listenPort;
						if(stream.GetProtocol() == TCP_PULL || stream.GetProtocol() == TCP_PUSH)
							transfertStarted = true;
					}
					
					// On va créer le transfert
					if(transfertStarted)
					{
						if(stream.GetProtocol() == TCP_PUSH)
						{
							// TODO : créer instance transfert
						}
						else if(stream.GetProtocol() == TCP_PULL)
						{
							// TODO : créer instance transfert
						}
						else if(stream.GetProtocol() == UDP_PUSH)
						{
							// TODO : créer instance transfert
						}
						else if(stream.GetProtocol() == UDP_PULL)
						{
							// TODO : créer instance transfert
						}
						
						// TODO : créer pipe
						
						// TODO : créer thread
					}
				} // -- début du transfert
				else
				{
					// TRANSFERT EN COURS
				
					if(command == "end" || command == "END" || command == "close" || command == "CLOSE")
					{
						// DECONNEXION
						Disconnect();
					}
					else if(stream.GetProtocol() == TCP_PULL || stream.GetProtocol() == UDP_PULL)
					{
						// PROTOCOLE PULL
						
						if(command == "get" || command == "GET")
						{
							int image_id;
							sline >> image_id;
							// TODO envoyer image_id au pipe
						}
						
					} // -- commande pull
					else
					{
						// PROTOCOLE PUSH
						
						if(command == "start" || command == "START")
						{
							// TODO : envoyer command au pipe
						}
						else if(command == "pause" || command == "PAUSE")
						{
							// TODO : envoyer command au pipe
						}
						else if(command == "alive" || command == "ALIVE")
						{
							// TODO : envoyer command au pipe	
						}
						else if(command == "listen_port" || command == "LISTEN_PORT")
						{
							sline >> listenPort;
							// TODO : récréer le transfert avec le port listenPort
						}
						
					} // -- commande push
				} // -- transfert en cours
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

