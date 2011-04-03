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
#include <sys/epoll.h>		// Gestion de multiples descripteurs (socket)
#include <sstream>			// stringstream
#include <unistd.h>			// pipe
#include <fcntl.h>			// manipulation de descripteurs

//------------------------------------------------------ Include personnel
#include "Stream.h"
#include "ActionConnection.h"
#include "ActionClient.h"
#include "DataTransfertMCASTPush.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
VideoType Stream::GetType()
{
	return type;
}

Protocol Stream::GetProtocol()
{
	return protocol;
}

float Stream::GetFps()
{
	return fps;
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
	// MCAST_PUSH :
	if(protocol == MCAST_PUSH)
	{
		string pipecmd = "END";
		write(pipefd, pipecmd.c_str(), pipecmd.size()+1);
		int err = pthread_join(transfertThread, NULL);
		if(err)
		{
			cerr << "Erreur : pthread_join" << endl;
		}
	}
	else
	{
		io.RemoveAction(s);
		close(s);
	}
}

//-------------------------------------------- Constructeurs - destructeur

Stream::Stream(IOControl& _io, in_addr _address, int _port, Protocol _protocol, string _name, VideoType _type, float _fps)
	: io(_io), address(_address), port(_port), protocol(_protocol), name(_name), type(_type), fps(_fps)
{

	if(protocol == UDP_PULL || protocol == UDP_PUSH)
		connectUDP();
	else if(protocol == TCP_PULL || protocol == TCP_PUSH)
		connectTCP();
	else if(protocol == MCAST_PUSH)
		connectMCAST();

}


Stream::~Stream()
{
	if(protocol == MCAST_PUSH) delete transfert;
	else delete connection;
}


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

void Stream::connectUDP()
{
	// On crée une socket en UDP pour écouter des clients sur ce flux :
	s = socket(PF_INET, SOCK_DGRAM, 0);
	if(s == -1)
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
		addr.sin_addr = address;			// htonl : convertit un long vers le format réseau
		addr.sin_port = htons(port);		// htons : convertit un short vers le format réseau
		
	if(bind(s, (sockaddr *) &addr, sizeof(addr)) == -1)
	{
		cerr << "bind" << endl;
		exit(EXIT_FAILURE);
	}
	
	// On va créer une action pour gérer l'envoi des messages des clients :
	connection = new ActionClient(io, this, s);
	
	// On ajoute la socket et l'action au gestionnaire d'e/s :
	io.AddAction(s, connection, EPOLLIN);
}

void Stream::connectTCP()
{
	// On crée une socket en TCP/IP pour écouter des clients sur ce flux :
	s = socket(PF_INET, SOCK_STREAM, 0);
	if(s == -1)
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
		addr.sin_addr = address;			// htonl : convertit un long vers le format réseau
		addr.sin_port = htons(port);		// htons : convertit un short vers le format réseau
		
	if(bind(s, (struct sockaddr *) &addr, sizeof(addr)) == -1)
	{
		cerr << "bind" << endl;
		exit(EXIT_FAILURE);
	}
	
	// On met en écoute la socket :
	if(listen(s, NBMAX_CLIENTS) == -1)
	{
		cerr << "listen" << endl;
		exit(EXIT_FAILURE);
	}
	
	// On va créer une action pour gérer la connexion des clients :
	connection = new ActionConnection(io, this);
	
	// On ajoute la socket et l'action au gestionnaire d'e/s :
	io.AddAction(s, connection, EPOLLIN);
}

void Stream::connectMCAST()
{
	// On va créer le pipe de communication avec le thread :
	int pipefds[2];
	pipe(pipefds);
	pipefd = pipefds[1];
	
	// On va mettre le pipe de lecture en non bloquant :
	int flags = fcntl(pipefds[0], F_GETFL, 0);
	fcntl(pipefds[0], F_SETFL, flags | O_NONBLOCK);
	
	// On va créer le transfert :
	transfert = new DataTransfertMCASTPush(this, address, port, MCAST_FRAGMENTSIZE, pipefds[0]);
	
	// On va enfin créer un nouveau thread qui partira de ce transfert :
	int err = pthread_create(&transfertThread, NULL, transfert->BeginThread, transfert);
	if(err)
	{
		cerr << "Erreur : pthread_create" << endl;
		exit(EXIT_FAILURE);
	}
}

