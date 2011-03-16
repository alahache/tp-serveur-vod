/*************************************************************************
                           ActionConnection  -  description
                             -------------------
    début                : ...
    copyright            : (C) 2011 par Arnaud Lahache
*************************************************************************/

//---------- Réalisation de la classe <ActionConnection> (fichier ActionConnection.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <fcntl.h>
#include <cstdlib>			// exit
#include <sys/types.h>		// Pour plus de compatibilité
#include <sys/socket.h>		// Sockets
#include <sys/epoll.h>		// Gestion de multiples descripteurs (socket)
#include <arpa/inet.h>		// inet_ntoa

//------------------------------------------------------ Include personnel
#include "ActionConnection.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void ActionConnection::Execute(epoll_event event)
{
	int s = event.data.fd;

	// On accepte la demande de connexion :
	sockaddr_in client_addr;
	socklen_t client_addr_len = sizeof(client_addr);
	int conn_sock = accept(s, (struct sockaddr *) &client_addr, &client_addr_len);
	if(conn_sock < 0)
	{
		cerr << "accept" << endl;
		exit(EXIT_FAILURE);
	}
	
	//cout << "[" << conn_sock << "] Nouveau client : " << inet_ntoa(client_addr.sin_addr) << endl;
	
	// On ajoute un nouveau client :
	Action* actionClient = new ActionClient(io, stream, conn_sock);
	clients.push_back(actionClient);
	
	// On met le descripteur en "non bloquant" (cf. man epoll - EPOLLET) :
	setNonBlocking(conn_sock);

	// On ajoute le descripteur au gestionnaire d'e/s :
	io.AddAction(conn_sock, &actionClient, EPOLLIN | EPOLLET);
}

void ActionConnection::RemoveClient(Action* client)
{
	// On supprime le client de la liste des clients connectés :
	clients.erase(client);
	
	// On détruit l'action associée au client :
	delete client;
}

ActionConnection::~ActionConnection()
{
	for(int i=0; i<clients.size(); i++)
	{
		delete clients[i];
	}
}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

void ActionConnection::setNonBlocking(int fd)
{
	int flags = fcntl(fd, F_GETFL, 0);
	fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}
