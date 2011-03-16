/*************************************************************************
                           ActionCommand  -  description
                             -------------------
    début                : ...
    copyright            : (C) 2011 par Arnaud Lahache
*************************************************************************/

//---------- Réalisation de la classe <ActionCommand> (fichier ActionCommand.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <string>

//------------------------------------------------------ Include personnel
#include "ActionCommand.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void ActionCommand::Execute(epoll_event event)
{
	string cmd;
	
	// On récupère la commande de l'utilisateur :
	cin >> cmd;
	
	if(cmd == "quit" || cmd == "exit")
	{
		// On arrête le serveur :
		io.Stop();
	}
	else
	{
		cout << "Erreur : Commande '" << cmd << "' inconnue." << endl;
		DisplayPrompt();
	}
}

void ActionCommand::DisplayPrompt()
{
	cout << endl << "server> ";
	cout.flush();

}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

