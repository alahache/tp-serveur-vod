/*************************************************************************
                           DataTransfertUDPPush  -  description
                             -------------------
    début                : ...
    copyright            : (C) 2011 par Arnaud Lahache
*************************************************************************/

//---------- Interface de la classe <DataTransfertUDPPush> (fichier DataTransfertUDPPush.h) ------
#if ! defined ( DATATRANSFERTUDPPUSH_H )
#define DATATRANSFERTUDPPUSH_H

//--------------------------------------------------- Interfaces utilisées
#include "DataTransfertUDP.h"

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Rôle de la classe <DataTransfertUDPPull>
//	- Implémentation de DataTransfertUDP pour le protocole Push
//	- Les images sont envoyées au client automatiquement en respectant
//	  le fps du flux.
//	- Le client peut stopper ou reprendre le transfert avec START et
//	  PAUSE
//------------------------------------------------------------------------ 

class DataTransfertUDPPush : public DataTransfertUDP
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

	void* Begin();

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

	DataTransfertUDPPush(Stream& _stream, in_addr _clientAddress, int _clientPort, unsigned int _fragmentSize, int _pipefd)
    	: DataTransfertUDP(_stream, _clientAddress, _clientPort, _fragmentSize), pipefd(_pipefd) {}
	// Mode d'emploi :
	// 	<_stream>			: référence vers le flux associé au transfert
	// 	<_clientAddress>	: addresse du client
	// 	<_clientPort>		: port d'écoute du client
	// 	<_fragmentSize>		: taille des fragments de données envoyés
	// 	<_pipefd>			: descripeur du pipe en lecture
	//
	//	- Construit une nouvelle instance de la classe DataTransfertUDP.

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées
	void setNonBlocking(int fd);
	void setBlocking(int fd);

//----------------------------------------------------- Attributs protégés
	int pipefd;					// Descripteur de lecture pour le pipe
    
};

//--------------------------- Autres définitions dépendantes de <DataTransfertUDPPush>

#endif // DataTransfertUDPPush_H

