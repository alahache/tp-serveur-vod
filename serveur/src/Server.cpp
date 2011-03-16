/*************************************************************************
                           Server  -  description
                             -------------------
    d�but                : ...
    copyright            : (C) 2011 par Arnaud Lahache
*************************************************************************/

//---------- R�alisation de la classe <Server> (fichier Server.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include syst�me
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

	// On ajoute l'entr�e standard dans le gestionnaire d'e/s :
	ActionCommand action_command(io);
	io.AddAction(0, &action_command, EPOLLIN);
	ActionCommand::DisplayPrompt();
	
	// On initialise tous les flux vid�os � partir du fichier de conf :
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

//----------------------------------------------------- M�thodes prot�g�es

void Server::loadConfig()
{
	char buffer[SIZE_BUFFER];
	string line;
	ifstream file(pathConf.c_str());
	
	// On r�cup�re le contenu du fichier de conf ligne par ligne :
	while(!file.eof())
	{
		// On r�cup�re la ligne courante :
		file.getline(buffer, sizeof(buffer));
		line = buffer;
		
		// On enl�ve les commentaires :
		unsigned int posComment = line.find_first_of('%');
		if(posComment != -1) line = line.substr(0, posComment+1);
		
		// On s�pare la d�claration de la valeur :
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
			// On va cr�er un nouveau flux vid�o :
			int port;
			Protocol protocol;
			string name;
			VideoType type;
			float ips;
			
			string prop;
			while(ss >> prop)
			{
				// On s�pare la d�claration de la valeur :
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
			
			prop.clear();
		}
	}
}
