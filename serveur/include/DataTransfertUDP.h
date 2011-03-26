/*************************************************************************
                           DataTransfertUDP  -  description
                             -------------------
    début                : ...
    copyright            : (C) 2011 par Arnaud Lahache
*************************************************************************/

//---------- Interface de la classe <DataTransfertUDP> (fichier DataTransfertUDP.h) ------
#if ! defined ( DATATRANSFERTUDP_H )
#define DATATRANSFERTUDP_H

//--------------------------------------------------- Interfaces utilisées
#include "DataTransfert.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Rôle de la classe <DataTransfertUDP>
//	- Implémentation de DataTransfert pour UDP
//	- Définition des méthodes utilisées pour envoyer des images du
//	  flux avec le protocole UDP
//------------------------------------------------------------------------ 

class DataTransfertUDP : public DataTransfert
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

	virtual void* Begin() = 0;

//-------------------------------------------- Constructeurs - destructeur

	DataTransfertUDP(Stream& _stream, in_addr _clientAddress, int _clientPort, unsigned int _fragmentSize)
    	: DataTransfert(_stream), clientAddress(_clientAddress), clientPort(_clientPort), fragmentSize(_fragmentSize) {}
    // Mode d'emploi :
	// 	<_stream>			: référence vers le flux associé au transfert
	// 	<_clientAddress>	: addresse du client
	// 	<_clientPort>		: port d'écoute du client
	// 	<_fragmentSize>		: taille des fragments de données envoyés
	//
	//	- Construit une nouvelle instance de la classe DataTransfertUDP.

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées
	void data_connect();
	void data_send(int imageId);
	void data_disconnect();

//----------------------------------------------------- Attributs protégés
	sockaddr_in addr;					// Client
	in_addr clientAddress;				// Adresse du client
	int clientPort;						// Port d'écoute du client
	int sock;							// Descripteur de la socket
	unsigned int fragmentSize;			// Taille des fragments de données

};

//--------------------------- Autres définitions dépendantes de <DataTransfertUDP>

#endif // DATATRANSFERTUDP_H

