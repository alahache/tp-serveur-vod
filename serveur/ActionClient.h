/*************************************************************************
                           ActionClient  -  description
                             -------------------
    début                : ...
    copyright            : (C) 2011 par Arnaud Lahache
*************************************************************************/

//---------- Interface de la classe <ActionClient> (fichier ActionClient.h) ------
#if ! defined ( ACTIONCLIENT_H )
#define ACTIONCLIENT_H

//--------------------------------------------------- Interfaces utilisées
#include "Action.h"
#include "IOControl.h"

//------------------------------------------------------------- Constantes
const unsigned int BUFFER_SIZE = 100;

//------------------------------------------------------------------------ 
// Rôle de la classe <ActionClient>
//	- Action lancée lorsqu'un client execute une requête d'e/s
//------------------------------------------------------------------------ 

class ActionClient : public Action
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void Execute(epoll_event event);
    // Mode d'emploi :
    //	<event>	: Évenement déclencheur de l'action
    //	
    //	- Méthode redéfinie appelée lorsqu'un évenement agit sur
    //	  le socket de connexion du client.

//-------------------------------------------- Constructeurs - destructeur

    ActionClient(IOControl& _io)
    	: io(_io) { }
    // Mode d'emploi :
    //	<_io>			: Gestionnaire d'e/s
    //
    //	- Contructeur de ActionConnection

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées
	void disconnect(int fd);
	// Mode d'emploi :
	//	<fd>	: descripteur du client
	//
	//	- Permet de déconnecter un client <fd> du serveur

//----------------------------------------------------- Attributs protégés
	IOControl& io;

};

#endif // ACTIONCLIENT_H

