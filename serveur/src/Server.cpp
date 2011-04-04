/*************************************************************************
                           Server  -  description
                             -------------------
    début                : ...
    copyright            : (C) 2011 par Arnaud Lahache
*************************************************************************/

//---------- Réalisation de la classe <Server> (fichier Server.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <fstream>			// ifstream
#include <sstream>			// stringstream
#include <cstdlib>			// exit
#include <sys/epoll.h>		// Gestion de multiples descripteurs (socket)
#include <sys/types.h>		// Pour plus de compatibilité
#include <sys/socket.h>		// Sockets
#include <arpa/inet.h>		// inet_ntoa
#include <netinet/in.h>

//------------------------------------------------------ Include personnel
#include "Server.h"
#include "ActionCommand.h"
#include "ActionHTTPConnection.h"
#include "ActionHTTPClient.h"

//----------------------------------------------------------------- PUBLIC

//-------------------------------------------- Constructeurs - destructeur

Server::Server(string _pathConf)
	: pathConf(_pathConf)
{
	// ---------------------------------------------------------------------
	// Initialisation du serveur :
	// ---------------------------------------------------------------------
	
	// On initialise tous les flux vidéos à partir du fichier de conf :
	loadConfig();
	
	// On va initialiser le serveur HTTP :
	int s = initHTTPServer();
	ActionHTTPClient		action_http_client(io);
	ActionHTTPConnection 	action_http_connection(io, action_http_client);
	io.AddAction(s, &action_http_connection, EPOLLIN);
	
	// On ajoute l'entrée standard dans le gestionnaire d'e/s :
	ActionCommand action_command(io);
	io.AddAction(0, &action_command, EPOLLIN);
	ActionCommand::DisplayPrompt();
	
	// ---------------------------------------------------------------------
	// Boucle principale :
	// ---------------------------------------------------------------------
	
	io.Run();
	
	// ---------------------------------------------------------------------
	// Destruction :
	// ---------------------------------------------------------------------
	
	// On va fermer tous les flux :
	for(int i=0; i<catalogue.size(); i++)
		catalogue[i]->Close();

	// On détruit le serveur HTTP et l'entrée standard :
	io.RemoveAction(s);	
	io.RemoveAction(0);
	close(s);
	
}

Server::~Server()
{
	for(int i=0; i<catalogue.size(); i++)
		delete catalogue[i];
}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

void Server::loadConfig()
{
	char buffer[SIZE_BUFFER];
	string line;
	ifstream file(pathConf.c_str());
	
	// On vérifie que le fichier existe :
	if(file.fail())
	{
		cerr << "Erreur : Fichier " << pathConf << " inexistant." << endl;
		exit(EXIT_FAILURE);
	}
	
	// On récupère le contenu du fichier de conf ligne par ligne :
	while(!file.eof())
	{
		// On récupère la ligne courante :
		file.getline(buffer, sizeof(buffer));
		line = buffer;
		
		// On enlève les commentaires :
		unsigned int posComment = line.find_first_of('%');
		if(posComment != -1) line = line.substr(0, posComment+1);
		
		// On sépare la déclaration de la valeur :
		int posSep = line.find_first_of('=');
		if(posSep == -1) continue;
		string name = line.substr(0, posSep);
		string val	= line.substr(posSep+1);
		stringstream ss(val);
		
		if(name == "httpport")
		{
			// On modifie le port HTTP du serveur :
			ss >> HTTPPort;
		}
		else if(name == "video")
		{
			// On va créer un nouveau flux vidéo :
			int port;
			Protocol protocol;
			string name;
			VideoType type;
			float ips;
			in_addr address;
				address.s_addr = htonl(INADDR_ANY);
			
			string prop;
			while(ss >> prop)
			{
				// On sépare la déclaration de la valeur :
				unsigned int propSep = prop.find_first_of(':');
				string propname = prop.substr(0, propSep);
				string propval	= prop.substr(propSep+1);
				
				if(propname == "name")
					name = propval;
				else if(propname == "type")
				{
					if(propval == "BMP") type = BMP;
					else if(propval == "JPEG") type = JPEG;
					else type = BMP;
				}
				else if(propname == "address")
					inet_aton(propval.c_str(), &address);
				else if(propname == "port")
					port = atoi(propval.c_str());
				else if(propname == "protocol")
				{
					if(propval == "TCP_PULL") protocol = TCP_PULL;
					else if(propval == "UDP_PULL") protocol = UDP_PULL;
					else if(propval == "TCP_PUSH") protocol = TCP_PUSH;
					else if(propval == "UDP_PUSH") protocol = UDP_PUSH;
					else if(propval == "MCAST_PUSH") protocol = MCAST_PUSH;
					else protocol = TCP_PULL;
				}
				else if(propname == "ips")
					ips = atof(propval.c_str());
			}
			
			Stream* stream = new Stream(io, address, port, protocol, name, type, ips);
			catalogue.push_back(stream);
			
			prop.clear();
		}
	}
}

int Server::initHTTPServer()
{
	// On va créer la socket s :
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
		addr.sin_port = htons(HTTPPort);				// htons : convertit un short vers le format réseau
		
	if(bind(s, (struct sockaddr *) &addr, sizeof(addr)) < 0)
	{
		cerr << "bind" << endl;
		exit(EXIT_FAILURE);
	}
	
	// On met en écoute la socket :
	if(listen(s, NBMAX_CLIENTS_HTTP) < 0)
	{
		cerr << "listen" << endl;
		exit(EXIT_FAILURE);
	}
	
	return s;
}
