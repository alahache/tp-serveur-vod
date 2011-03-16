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
#include <vector>
#include <string>

//------------------------------------------------------------- Constantes 
const std::string DEFAULT_PATH_CONF = "config/server.conf";
const int SIZE_BUFFER = 1024;

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Rôle de la classe <Server>
//	- Serveur de gestion et de diffusion de flux vidéos en ligne.
//
//
//
//------------------------------------------------------------------------ 

class Server
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

//-------------------------------------------- Constructeurs - destructeur

	Server(std::string _pathConf = DEFAULT_PATH_CONF);
	// Mode d'emploi :
	//	- Constructeur du serveur
	//	- Permet d'initialiser tous les flux ainsi que toutes les
	//	  connexions.
	//	- Surveille l'entrée standard pour y entrer des commandes
	//	- Initialise le serveur HTTP
	//	- Lance la boucle d'entrée / sortie IOControl
	
	virtual ~Server();
	// Mode d'emploi :
	//	- Destructeur du serveur

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées

	void loadConfig();
	// Mode d'emploi :
	//	- Permet de lire le fichier de configuration pour y extraire
	//	  Le port du serveur, ainsi que les flux associés et toutes
	//	  leurs caractéristiques.

//----------------------------------------------------- Attributs protégés
	std::string pathConf;				// Chemin vers le fichier de configuration
	std::vector<Stream*> catalogue;		// Catalogue des Flux vidéo
	IOControl io;						// Gestionnaire d'e/s
	int HTTPPort;						// Port vers le serveur HTTP
	// TODO serv HTTP
};

#endif // SERVER_H

