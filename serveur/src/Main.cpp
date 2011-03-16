
/*************************************************************************
                         Main  -  programme principal
                             -------------------
    début                : 12 mars 2011
    copyright            : (C) 2011 par Arnaud Lahache
*************************************************************************/

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstdlib>			// exit
#include <sys/types.h>		// Pour plus de compatibilité
#include <sys/socket.h>		// Sockets
#include <sys/epoll.h>		// Gestion de multiples descripteurs (socket)
#include <netinet/in.h>		// support IPv4
#include <arpa/inet.h>		// inet_ntoa

//------------------------------------------------------ Include personnel
#include "IOControl.h"
#include "ActionConnection.h"
#include "ActionClient.h"
#include "ActionCommand.h"

#define NBMAX 1000

//---------------------------------------------------- PROGRAMME PRINCIPAL

int main()
{
	IOControl io;
	ActionCommand		action_command(io);
	ActionClient		action_client(io);
	ActionConnection 	action_connect(io, action_client);
	
	// On ajoute l'entrée standard dans le gestionnaire d'e/s :
	io.AddAction(0, &action_command, EPOLLIN);
	ActionCommand::DisplayPrompt();
	
	// ---------------------------------------------------------------------
	// Initialisation de la connexion :
	// ---------------------------------------------------------------------
	
	// On itinialise le port à 1234
	int port = 1234;
	
	// On crée une socket en TCP/IP
	int s = socket(PF_INET, SOCK_STREAM, 0);
	if(s < 0)
	{
		cerr << "socket" << endl;
		exit(EXIT_FAILURE);
	}
	
	// On contourne le probleme de l'adresse et du port déjà utilisés :
	int opt=1;
	setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	
	// On attache le port à la socket :
	struct sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = htonl(INADDR_ANY);		// htonl : convertit un long vers le format réseau
		addr.sin_port = htons(port);					// htons : convertit un short vers le format réseau
		
	if(bind(s, (struct sockaddr *) &addr, sizeof(addr)) < 0)
	{
		cerr << "bind" << endl;
		exit(EXIT_FAILURE);
	}
	
	// On met en écoute la socket :
	if(listen(s, NBMAX) < 0)
	{
		cerr << "listen" << endl;
		exit(EXIT_FAILURE);
	}
	
	// On ajoute la socket au gestionnaire d'e/s :
	io.AddAction(s, &action_connect, EPOLLIN);
	
	// ---------------------------------------------------------------------
	// Boucle principale :
	// ---------------------------------------------------------------------
	
	io.Run();
	
	// ---------------------------------------------------------------------
	// Destruction :
	// ---------------------------------------------------------------------
	
	io.RemoveAction(s);
	close(s);
	
	return 0;
}
