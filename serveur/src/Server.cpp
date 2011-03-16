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
#include <sys/epoll.h>
#include <sstream>
#include <cstdlib>
#include <fstream>

//------------------------------------------------------ Include personnel
#include "Server.h"
#include "ActionCommand.h"

//----------------------------------------------------------------- PUBLIC

//-------------------------------------------- Constructeurs - destructeur

Server::Server(string _pathConf)
	: pathConf(_pathConf)
{
	// ---------------------------------------------------------------------
	// Initialisation du serveur :
	// ---------------------------------------------------------------------

	// On ajoute l'entrée standard dans le gestionnaire d'e/s :
	ActionCommand action_command(io);
	io.AddAction(0, &action_command, EPOLLIN);
	ActionCommand::DisplayPrompt();
	
	// On initialise tous les flux vidéos à partir du fichier de conf :
	loadConfig();
	
	// ---------------------------------------------------------------------
	// Boucle principale :
	// ---------------------------------------------------------------------
	
	io.Run();
	
	// ---------------------------------------------------------------------
	// Destruction :
	// ---------------------------------------------------------------------
	
	io.RemoveAction(0);
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
	
	// On récupère le contenu du fichier de conf ligne par ligne :
	while(!file.eof())
	{
		// On récupère la ligne courante :
		file.getline(buffer, sizeof(buffer));
		line = buffer;
		
		// On enlève les commentaires :
		unsigned int posComment = line.find_first_of('%');
		line = line.substr(0, posComment+1);
		
		// On sépare la déclaration de la valeur :
		unsigned int posSep = line.find_first_of('=');
		if(posSep == -1) continue;
		string name = line.substr(0, posSep);
		string val	= line.substr(posSep);
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
			
			string prop;
			while(ss >> prop)
			{
				// On sépare la déclaration de la valeur :
				unsigned int propSep = line.find_first_of(':');
				string propname = line.substr(0, posSep);
				string propval	= line.substr(posSep);
				
				if(propname == "name")
					name = propval;
				else if(propname == "type")
				{
					if(propval == "BMP") type = BMP;
					else if(propval == "JPEG") type = JPEG;
					else type = BMP;
				}
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
				{
					ips = atof(propval.c_str());
				}
			}
			
			Stream* stream = new Stream(io, port, protocol, name, type, ips);
			catalogue.push_back(stream);
		}
	}
}
