/*************************************************************************
                           ActionConnection  -  description
                             -------------------
    début                : ...
    copyright            : (C) 2011 par Arnaud Lahache
*************************************************************************/

//---------- Interface de la classe <ActionConnection> (fichier ActionConnection.h) ------
#if ! defined ( ACTIONCONNECTION_H )
#define ACTIONCONNECTION_H

//--------------------------------------------------- Interfaces utilisées
#include <list>
#include "Action.h"
#include "IOControl.h"
#include "Stream.h"

//------------------------------------------------------------------------ 
// Rôle de la classe <ActionConnection>
//	- Action lancée lorsqu'un client lance une nouvelle connexion TCP/IP
//	  sur le serveur VOD.
//	- Une nouvelle instance de ActionClient est alors
//	  créée pour permettre la communication entre le ce dernier et le
//	  serveur.
//------------------------------------------------------------------------ 

class ActionConnection : public Action
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
	void Execute(epoll_event event);
	// Mode d'emploi :
	//	<event>		: Évenement déclencheur de l'action
	//	
	//	- Méthode redéfinie appelée lorsqu'un client veut se connecter
	//	  sur le serveur

	void RemoveClient(Action* client);
	// Mode d'emploi :
	//	<client>	: Client à supprimer
	//	
	//	- Permet de supprimer une action lorqu'un client se déconnecte
	//	  du serveur afin de libérer de la mémoire.

//-------------------------------------------- Constructeurs - destructeur

	ActionConnection(IOControl& _io, Stream& _stream)
		: Action(_io), stream(_stream) { }
	// Mode d'emploi :
	//	<_io>			: Gestionnaire d'e/s
	//	<_stream>		: flux associé à la connexion
	//
	//	- Contructeur de ActionConnection
	
	virtual ~ActionConnection();
	// Mode d'emploi :
	//	- Destructeur de ActionConnection

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
	std::list<Action*> clients;		// Liste des clients connectés
	Stream& stream;					// Flux associé à la connexion

};

#endif // ACTIONCONNECTION_H

