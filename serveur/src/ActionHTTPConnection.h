/*************************************************************************
                           ActionHTTPConnection  -  description
                             -------------------
    début                : ...
    copyright            : (C) 2011 par Arnaud Lahache
*************************************************************************/

//---------- Interface de la classe <ActionHTTPConnection> (fichier ActionHTTPConnection.h) ------
#if ! defined ( ACTIONHTTPCONNECTION_H )
#define ACTIONHTTPCONNECTION_H

//--------------------------------------------------- Interfaces utilisées
#include <list>
#include "Action.h"
#include "IOControl.h"

//------------------------------------------------------------------------ 
// Rôle de la classe <ActionHTTPConnection>
//	- Action lancée lorsqu'un client lance une nouvelle connexion TCP/IP
//	  sur le serveur HTTP.
//	- Une nouvelle instance de ActionHTTPClient est alors
//	  créée pour permettre la communication entre le ce dernier et le
//	  serveur HTTP.
//------------------------------------------------------------------------ 

class ActionHTTPConnection : public Action
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
	void Execute(epoll_event event);
	// Mode d'emploi :
	//	<event>		: Évenement déclencheur de l'action
	//	
	//	- Méthode redéfinie appelée lorsqu'un client veut se connecter
	//	  sur le serveur HTTP

//-------------------------------------------- Constructeurs - destructeur

	ActionHTTPConnection(IOControl& _io, Action& _actionClient)
		: Action(_io), actionClient(_actionClient) { }
	// Mode d'emploi :
	//	<_io>				: Gestionnaire d'e/s
	//	<_actionClient>		: action clients
	//
	//	- Contructeur de ActionHTTPConnection

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées

	void setNonBlocking(int fd);
	// Mode d'emploi :
	//	<fd>	: descripteur cible
	//
	//	- Permet de modifier un descripteur afin de le rendre non
	//	  bloquant.

//----------------------------------------------------- Attributs protégés
	Action& actionClient;			// Action clients

};

#endif // ACTIONHTTPCONNECTION_H

