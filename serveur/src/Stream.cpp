/*************************************************************************
                           Stream  -  description
                             -------------------
    début                : ...
    copyright            : (C) 2011 par Arnaud Lahache
*************************************************************************/

//---------- Réalisation de la classe <Stream> (fichier Stream.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstdlib>			// exit
#include <sys/types.h>		// Pour plus de compatibilité
#include <sys/socket.h>		// Sockets
#include <sys/epoll.h>		// Gestion de multiples descripteurs (socket)
#include <arpa/inet.h>		// inet_ntoa
#include <sstream>			// string stream

//------------------------------------------------------ Include personnel
#include "Stream.h"
#include "ActionConnection.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
VideoType Stream::GetType()
{
	return type;
}

float Stream::GetIps()
{
	return ips;
}

string Stream::GetImagePath(int i)
{
	stringstream oss;

	// Selon le type de la vidéo, on récupère l'extension :
	string ext;
	switch(type)
	{
		case JPEG:
			ext = ".jpg";
			break;
		default:
			ext = ".bmp";
	}
	
	// Format : vidéos/nom_video/numero_image.EXT
	oss << STREAM_DIRECTORY << name << "/" << i << ext;
	return oss.str();
}

void Stream::Close()
{
	io.RemoveAction(s);
	close(s);
}

//-------------------------------------------- Constructeurs - destructeur

Stream::Stream(IOControl& _io, int _port, Protocol _protocol, string _name, VideoType _type, float _ips)
	: io(_io), port(_port), protocol(_protocol), name(_name), type(_type), ips(_ips)
{
	// On crée une socket en TCP/IP pour écouter des clients sur ce flux :
	s = socket(PF_INET, SOCK_STREAM, 0);
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
	if(listen(s, NBMAX_CLIENTS) < 0)
	{
		cerr << "listen" << endl;
		exit(EXIT_FAILURE);
	}
	
	// On va créer une action pour gérer la connexion des clients :
	connection = new ActionConnection(io, *this);
	
	// On ajoute la socket et l'action au gestionnaire d'e/s :
	io.AddAction(s, connection, EPOLLIN);
	
}


Stream::~Stream()
{
	delete connection;
}


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

