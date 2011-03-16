/*************************************************************************
                           Stream  -  description
                             -------------------
    début                : ...
    copyright            : (C) 2011 par Arnaud Lahache
*************************************************************************/

//---------- Interface de la classe <Stream> (fichier Stream.h) ------
#if ! defined ( STREAM_H )
#define STREAM_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include "IOControl.h"
#include "Action.h"

//------------------------------------------------------------- Constantes
const std::string STREAM_DIRECTORY = "videos/";

//------------------------------------------------------------------ Types 
enum VideoType { BMP, JPEG };
enum Protocol { TCP_PULL, TCP_PUSH, UDP_PULL, UDP_PUSH, MCAST_PUSH };

//------------------------------------------------------------------------ 
// Rôle de la classe <Stream>
//	- Représente un flux vidéo à disposition du serveur. Un flux est
//	  rattaché à un seul port dans le serveur, il permet de décrire une
//	  vidéo et les méthodes permettant d'y accéder pour y récupérer les
//	  images.
//	- Un flux est également rattaché à une connexion TCP/IP gérée par le
//	  gestionnaire d'e/s IOControl. Les actions ActionConnection et
//	  ActionClient utilisent ce flux.
//------------------------------------------------------------------------ 

class Stream
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
	VideoType GetType();
	// Mode d'emploi :
	//	- Retourne le type vidéo du flux
	
	float GetIps();
	// Mode d'emploi :
	//	- Retourne le nombre d'images par secondes de la vidéo
	
	std::string GetImagePath(int i);
	// Mode d'emploi :
	//	<i>		: position de l'image dans la vidéo
	//
	//	- Retourne le chemin d'accès relatif à l'image numéro <i> de la
	//	  vidéo du flux.

//-------------------------------------------- Constructeurs - destructeur

	Stream(IOControl& _io, int _port, Protocol _protocol, std::string _name, VideoType _type, float _ips);
	// Mode d'emploi :
	//	- Construit un nouveau flux

	virtual ~Stream();
	// Mode d'emploi :
	//	- Détruit un flux

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
	// Paramètres du serveur :
	IOControl& io;				// Gestionnaire d'e/s
	Action* connection;			// Action de connexion des clients
	
	// Paramètres de la vidéo :
	int port;					// port utilisé par le flux
	Protocol protocol;			// Protocole utilisé pour les échanges
	std::string name;			// Nom de la vidéo
	VideoType type;				// Type d'images de la vidéo
	float ips;					// Nombre d'images par secondes

};

//--------------------------- Autres définitions dépendantes de <Stream>

#endif // STREAM_H

