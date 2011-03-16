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

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

void Server::loadConfig()
{
	
}
