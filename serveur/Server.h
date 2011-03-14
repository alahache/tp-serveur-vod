/*************************************************************************
                           Server  -  description
                             -------------------
    d�but                : ...
    copyright            : (C) 2011 par Arnaud Lahache
*************************************************************************/

//---------- Interface de la classe <Server> (fichier Server.h) ------
#if ! defined ( SERVER_H )
#define SERVER_H

//--------------------------------------------------- Interfaces utilis�es
#include "IOControl.h"
#include "Stream.h"

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// R�le de la classe <Server>
//	- Serveur de gestion et de diffusion de flux vid�os en ligne. Cette
//	  classe contient le programme principal permettant de lancer le
//	  serveur en ligne de commande.
//	- 
//------------------------------------------------------------------------ 

class Server
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- M�thodes publiques

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
//----------------------------------------------------- M�thodes prot�g�es

//----------------------------------------------------- Attributs prot�g�s
	std::vector<Stream> catalogue;		// Catalogue des Flux vid�o
	IOControl io;						// Gestionnaire d'e/s

};

#endif // SERVER_H

