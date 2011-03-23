/*************************************************************************
                           ActionHTTPClient  -  description
                             -------------------
    début                : ...
    copyright            : (C) 2011 par Arnaud Lahache
*************************************************************************/

//---------- Interface de la classe <ActionHTTPClient> (fichier ActionHTTPClient.h) ------
#if ! defined ( ACTIONHTTPCLIENT_H )
#define ACTIONHTTPCLIENT_H

//--------------------------------------------------- Interfaces utilisées
#include <netinet/in.h>		// support IPv4
#include <string>

#include "Action.h"
#include "ActionHTTPConnection.h"
#include "IOControl.h"

//------------------------------------------------------------- Constantes
const unsigned int BUFFER_SIZE = 1024;
const std::string WWW_DIRECTORY = "www";

//------------------------------------------------------------------------ 
// Rôle de la classe <ActionHTTPClient>
//	- Action lancée lorsqu'un client execute une requête d'e/s sur une
//	  connexion HTTP
//------------------------------------------------------------------------ 

class ActionHTTPClient : public Action
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void Execute(epoll_event event);
    // Mode d'emploi :
    //	<event>	: Évenement déclencheur de l'action
    //	
    //	- Méthode redéfinie appelée lorsqu'un client effectue une
    //	  opération de lecture / écriture sur le descripteur <fd>.
    
    void Disconnect(int fd);
	// Mode d'emploi :
	//	- Permet de déconnecter un client du serveur.

//-------------------------------------------- Constructeurs - destructeur

    ActionHTTPClient(IOControl& _io)
    	: Action(_io) { }
    // Mode d'emploi :
    //	<_io>			: Gestionnaire d'e/s
    //
    //	- Construit une nouvelle instance de ActionHTTPClient.

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées

	long readFile(string filename, char*& buffer, string& type);

//----------------------------------------------------- Attributs protégés

};

#endif // ACTIONHTTPCLIENT_H

