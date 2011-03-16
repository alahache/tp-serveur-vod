/*************************************************************************
                           ActionCommand  -  description
                             -------------------
    d�but                : ...
    copyright            : (C) 2011 par Arnaud Lahache
*************************************************************************/

//---------- R�alisation de la classe <ActionCommand> (fichier ActionCommand.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include syst�me
using namespace std;
#include <iostream>
#include <string>

//------------------------------------------------------ Include personnel
#include "ActionCommand.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- M�thodes publiques
void ActionCommand::Execute(epoll_event event)
{
	string cmd;
	
	// On r�cup�re la commande de l'utilisateur :
	cin >> cmd;
	
	if(cmd == "quit" || cmd == "exit")
	{
		// On arr�te le serveur :
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

//----------------------------------------------------- M�thodes prot�g�es

