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
			
			string message = buffer;
			message.resize(message.length()-2);	// Enlever CRLF
			
			if(message == "end" || message == "END" || message == "close" || message == "CLOSE")
			{
				// DECONNEXION
				Disconnect();
			}
		}
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
	connection.Removeclient(this);
}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

