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
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "IOControl.h"
#include "Action.h"
class DataTransfert;

//------------------------------------------------------------- Constantes
const std::string STREAM_DIRECTORY = "videos/";
const int NBMAX_CLIENTS = 100;
const unsigned int MCAST_FRAGMENTSIZE = 512;

//------------------------------------------------------------------ Types 
enum VideoType { BMP, JPEG };
enum Protocol { TCP_PULL, TCP_PUSH, UDP_PULL, UDP_PUSH, MCAST_PUSH };

//------------------------------------------------------------------------ 
// Rôle de la classe <Stream>
//	- Représente un flux vidéo à disposition du serveur. Un flux est
//	  rattaché à un seul port dans le serveur, il permet de décrire une
//	  vidéo et les méthodes permettant d'y accéder pour y récupérer les
//	  images.
//	- Un flux est éventuellement rattaché à une connexion de contrôle 
//	  gérée par le gestionnaire d'e/s IOControl. Les actions
//	  ActionConnection et ActionClient utilisent ce flux.
//------------------------------------------------------------------------ 

class Stream
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
	VideoType GetType();
	// Mode d'emploi :
	//	- Retourne le type vidéo du flux
	
	Protocol GetProtocol();
	// Mode d'emploi :
	//	- Retourne le protocole du flux
	
	float GetFps();
	// Mode d'emploi :
	//	- Retourne le nombre d'images par secondes de la vidéo
	
	std::string GetImagePath(int i);
	// Mode d'emploi :
	//	<i>		: position de l'image dans la vidéo
	//
	//	- Retourne le chemin d'accès relatif à l'image numéro <i> de la
	//	  vidéo du flux.
	
	void Close();
	// Mode d'emploi :
	//	- Permet d'arrêter un flux

//-------------------------------------------- Constructeurs - destructeur

	Stream(IOControl& _io, in_addr _address, int _port, Protocol _protocol, std::string _name, VideoType _type, float _fps);
	// Mode d'emploi :
	//	<_io>		: gestionnaire d'entrée/sortie
	//	<_address>	: adresse de connexion du client
	//	<_port>		: port de connexion du client
	//	<_protocol>	: protocole géré par le flux
	//	<_name>		: nom de la vidéo
	//	<_type>		: type des images envoyées
	//	<_fps>		: nombre d'images par seconde
	//
	//	- Construit un nouveau flux
	//	Dans le cas d'un flux UDP / TCP :
	//	- Ouvre une nouvelle connexion de contrôle
	//	- Ajoute une action pour gérer les connexions des clients
	//	  au gestionnaire d'e/s
	//	Dans le cas d'un flux MCAST :
	//	- Lance directement le Transfert des données et son thread

	virtual ~Stream();
	// Mode d'emploi :
	//	- Détruit un flux

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées
	void connectUDP();
	void connectTCP();
	void connectMCAST();

//----------------------------------------------------- Attributs protégés
	// Connection de contrôle :
	IOControl& io;					// Gestionnaire d'e/s
	int s;							// Socket de connexion des clients
	Action* connection;				// Action de connexion des clients
	
	// Transfert MCAST :
	DataTransfert *transfert;		// Transfert du flux MCAST_PUSH
	pthread_t transfertThread;		// Thread utilisé lors de MCAST_PUSH
	int pipefd;						// Canal de communication avec MCAST_PUSH
	
	// Paramètres de la vidéo :
	in_addr address;				// adresse du flux
	int port;						// port utilisé par le flux
	Protocol protocol;				// Protocole utilisé pour les échanges
	std::string name;				// Nom de la vidéo
	VideoType type;					// Type d'images de la vidéo
	float fps;						// Nombre d'images par secondes

};

//--------------------------- Autres définitions dépendantes de <Stream>

#endif // STREAM_H

