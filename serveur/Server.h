/*************************************************************************
                           Server  -  description
                             -------------------
    début                : ...
    copyright            : (C) 2011 par Arnaud Lahache
*************************************************************************/

//---------- Interface de la classe <Server> (fichier Server.h) ------
#if ! defined ( SERVER_H )
#define SERVER_H

//--------------------------------------------------- Interfaces utilisées
#include "IOControl.h"
#include "Stream.h"

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Rôle de la classe <Server>
//	- Serveur de gestion et de diffusion de flux vidéos en ligne.
//	- 
//------------------------------------------------------------------------ 

class Server
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

//-------------------------------------------- Constructeurs - destructeur

	Server();
	// Mode d'emploi :
	//	- Constructeur du serveur
	// Contrat :
	//

	virtual ~Server();
	// Mode d'emploi :
	//	- Destructeur du serveur
	// Contrat :
	//

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
	std::vector<Stream> catalogue;		// Catalogue des Flux vidéo
	IOControl io;						// Gestionnaire d'e/s

};

#endif // SERVER_H

