/*************************************************************************
                           Stream  -  description
                             -------------------
    d�but                : ...
    copyright            : (C) 2011 par Arnaud Lahache
*************************************************************************/

//---------- R�alisation de la classe <Stream> (fichier Stream.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include syst�me
using namespace std;
#include <iostream>
#include <cstdlib>			// exit
#include <sys/types.h>		// Pour plus de compatibilit�
#include <sys/socket.h>		// Sockets
#include <sys/epoll.h>		// Gestion de multiples descripteurs (socket)
#include <arpa/inet.h>		// inet_ntoa
#include <sstream>			// string stream

//------------------------------------------------------ Include personnel
#include "Stream.h"
#include "ActionConnection.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- M�thodes publiques
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

	// Selon le type de la vid�o, on r�cup�re l'extension :
	string ext;
	switch(type)
	{
		case JPEG:
			ext = ".jpg";
			break;
		default:
			ext = ".bmp";
	}
	
	// Format : vid�os/nom_video/numero_image.EXT
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
	
	// On cr�e une socket en TCP/IP pour �couter des clients sur ce flux :
	s = socket(PF_INET, SOCK_STREAM, 0);
	if(s < 0)
	{
		cerr << "socket" << endl;
		exit(EXIT_FAILURE);
	}
	
	// On contourne le probleme de l'adresse et du port d�j� utilis�s :
	int opt=1;
	setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	
	// On attache le port � la socket :
	struct sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = htonl(INADDR_ANY);		// htonl : convertit un long vers le format r�seau
		addr.sin_port = htons(port);					// htons : convertit un short vers le format r�seau
		
	if(bind(s, (struct sockaddr *) &addr, sizeof(addr)) < 0)
	{
		cerr << "bind" << endl;
		exit(EXIT_FAILURE);
	}
	
	// On met en �coute la socket :
	if(listen(s, NBMAX_CLIENTS) < 0)
	{
		cerr << "listen" << endl;
		exit(EXIT_FAILURE);
	}
	
	// On va cr�er une action pour g�rer la connexion des clients :
	connection = new ActionConnection(io, *this);
	
	// On ajoute la socket et l'action au gestionnaire d'e/s :
	io.AddAction(s, connection, EPOLLIN);
	
}


Stream::~Stream()
{
	delete connection;
}


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- M�thodes prot�g�es

