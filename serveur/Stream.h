/*************************************************************************
                           Stream  -  description
                             -------------------
    d�but                : ...
    copyright            : (C) 2011 par Arnaud Lahache
*************************************************************************/

//---------- Interface de la classe <Stream> (fichier Stream.h) ------
#if ! defined ( STREAM_H )
#define STREAM_H

//--------------------------------------------------- Interfaces utilis�es
#include <string>
#include "IOControl.h"
#include "Action.h"

//------------------------------------------------------------- Constantes
const std::string STREAM_DIRECTORY = "videos/";

//------------------------------------------------------------------ Types 
enum VideoType { BMP, JPEG };
enum Protocol { TCP_PULL, TCP_PUSH, UDP_PULL, UDP_PUSH, MCAST_PUSH };

//------------------------------------------------------------------------ 
// R�le de la classe <Stream>
//	- Repr�sente un flux vid�o � disposition du serveur. Un flux est
//	  rattach� � un seul port dans le serveur, il permet de d�crire une
//	  vid�o et les m�thodes permettant d'y acc�der pour y r�cup�rer les
//	  images.
//	- Un flux est �galement rattach� � une connexion TCP/IP g�r�e par le
//	  gestionnaire d'e/s IOControl. Les actions ActionConnection et
//	  ActionClient utilisent ce flux.
//------------------------------------------------------------------------ 

class Stream
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- M�thodes publiques
	VideoType GetType();
	// Mode d'emploi :
	//	- Retourne le type vid�o du flux
	
	float GetIps();
	// Mode d'emploi :
	//	- Retourne le nombre d'images par secondes de la vid�o
	
	std::string GetImagePath(int i);
	// Mode d'emploi :
	//	<i>		: position de l'image dans la vid�o
	//
	//	- Retourne le chemin d'acc�s relatif � l'image num�ro <i> de la
	//	  vid�o du flux.

//-------------------------------------------- Constructeurs - destructeur

	Stream(IOControl& _io)
		: io(_io) { }
	// Mode d'emploi :
	//	- Construit un nouveau flux

	virtual ~Stream();
	// Mode d'emploi :
	//	- D�truit un flux

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- M�thodes prot�g�es

//----------------------------------------------------- Attributs prot�g�s
	// Param�tres du serveur :
	IOControl& io;				// Gestionnaire d'e/s
	Action* connection;			// Action de connexion des clients
	
	// Param�tres de la vid�o :
	int port;					// port utilis� par le flux
	Protocol protocol;			// Protocole utilis� pour les �changes
	std::string name;			// Nom de la vid�o
	VideoType type;				// Type d'images de la vid�o
	float ips;					// Nombre d'images par secondes

};

//--------------------------- Autres d�finitions d�pendantes de <Stream>

#endif // STREAM_H

