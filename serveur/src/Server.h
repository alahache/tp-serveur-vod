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
#include <vector>
#include <string>

//------------------------------------------------------------- Constantes 
const std::string DEFAULT_PATH_CONF = "config/server.conf";
const int SIZE_BUFFER = 1024;

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// R�le de la classe <Server>
//	- Serveur de gestion et de diffusion de flux vid�os en ligne.
//
//
//
//------------------------------------------------------------------------ 

class Server
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- M�thodes publiques

//-------------------------------------------- Constructeurs - destructeur

	Server(std::string _pathConf = DEFAULT_PATH_CONF);
	// Mode d'emploi :
	//	- Constructeur du serveur
	//	- Permet d'initialiser tous les flux ainsi que toutes les
	//	  connexions.
	//	- Surveille l'entr�e standard pour y entrer des commandes
	//	- Initialise le serveur HTTP
	//	- Lance la boucle d'entr�e / sortie IOControl
	
	virtual ~Server();
	// Mode d'emploi :
	//	- Destructeur du serveur

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- M�thodes prot�g�es

	void loadConfig();
	// Mode d'emploi :
	//	- Permet de lire le fichier de configuration pour y extraire
	//	  Le port du serveur, ainsi que les flux associ�s et toutes
	//	  leurs caract�ristiques.

//----------------------------------------------------- Attributs prot�g�s
	std::string pathConf;				// Chemin vers le fichier de configuration
	std::vector<Stream*> catalogue;		// Catalogue des Flux vid�o
	IOControl io;						// Gestionnaire d'e/s
	int HTTPPort;						// Port vers le serveur HTTP
	// TODO serv HTTP
};

#endif // SERVER_H

