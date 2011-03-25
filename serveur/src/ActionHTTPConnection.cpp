/*************************************************************************
                           ActionHTTPConnection  -  description
                             -------------------
    début                : ...
    copyright            : (C) 2011 par Arnaud Lahache
*************************************************************************/

//---------- Réalisation de la classe <ActionHTTPConnection> (fichier ActionHTTPConnection.cpp) -------

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
#include "ActionHTTPConnection.h"
#include "ActionHTTPClient.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void ActionHTTPConnection::Execute(epoll_event event)
{
	int s = event.data.fd;

	// On accepte la demande de connexion :
	sockaddr_in client_addr;
	socklen_t client_addr_len = sizeof(client_addr);
	int conn_sock = accept(s, (struct sockaddr *) &client_addr, &client_addr_len);
	if(conn_sock == -1)
	{
		cerr << "accept" << endl;
		exit(EXIT_FAILURE);
	}
	
	//cout << "[" << conn_sock << "] Nouveau client : " << inet_ntoa(client_addr.sin_addr) << endl;
	
	// /!\	- Attention : Pour plus de performances, on pourra décommenter la ligne
	//		  suivante et ajouter l'évenement EPOLLOUT pour envoyer les réponses
	//		  HTTP en plusieurs fois si le fichier est trop gros.
	//		- Pour plus de simplicité, on va simplement envoyer le fichier en
	//		  une seule fois en supposant que ce dernier ne soit pas trop gros.
	//setNonBlocking(conn_sock);

	// On ajoute le descripteur au gestionnaire d'e/s :
	io.AddAction(conn_sock, &actionClient, EPOLLIN | EPOLLET);
}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

void ActionHTTPConnection::setNonBlocking(int fd)
{
	int flags = fcntl(fd, F_GETFL, 0);
	fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}
