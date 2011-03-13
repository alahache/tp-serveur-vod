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
#include "Action.h"
#include "IOControl.h"

//------------------------------------------------------------------------ 
// Rôle de la classe <ActionConnection>
//	- Action lancée lorsqu'un client veut se connecter au serveur
//------------------------------------------------------------------------ 

class ActionConnection : public Action
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void Execute(epoll_event event);
    // Mode d'emploi :
    //	<event>	: Évenement déclencheur de l'action
    //	
    //	- Méthode redéfinie appelée lorsqu'un évenement agit sur
    //	  la socket de connexion.

//-------------------------------------------- Constructeurs - destructeur

    ActionConnection(IOControl& _io, Action& _actionClient)
    	: io(_io), actionClient(_actionClient) { }
    // Mode d'emploi :
    //	<_io>			: Gestionnaire d'e/s
    //	<_actionClient>	: Action déclenchée lorsqu'un client se connecte
    //
    //	- Contructeur de ActionConnection

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
	IOControl& io;
	Action& actionClient;

};

#endif // ACTIONCONNECTION_H

