/*************************************************************************
                           DataTransfertTCP  -  description
                             -------------------
    début                : Mars 2011
    copyright            : (C) 2011 par Pierre LULÉ
*************************************************************************/

//---------- Interface de la classe <DataTransfertTCP> (fichier DataTransfertTCP.h) ------
#if ! defined ( DATATRANSFERTTCP_H )
#define DATATRANSFERTTCP_H

//--------------------------------------------------- Interfaces utilisées
#include "DataTransfert.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>

//------------------------------------------------------------- Constantes 
const unsigned int BUFFER_SIZE = 768;

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Rôle de la classe <DataTransfertTCP>
// 	- Implémentation de DataTransfert pour TCP
//	- Définition des méthodes utilisées pour envoyer des images du
//	  flux avec le protocole TCP
//------------------------------------------------------------------------ 

class DataTransfertTCP : public DataTransfert
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

	virtual void* Begin() = 0;

//-------------------------------------------- Constructeurs - destructeur

	DataTransfertTCP(Stream* _stream, in_addr _clientAddress, int _clientPort)
    	: DataTransfert(_stream), clientAddress(_clientAddress), clientPort(_clientPort) {};
	// Mode d'emploi :
	// 	<_stream>			: référence vers le flux associé au client
	// 	<_clientAddress>	: addresse du client
	// 	<_clientPort>		: port d'écoute du client
	//
	//	- Construit une nouvelle instance de la classe DataTransfertTCP.

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées
	void data_connect();
	void data_send(int imageId);
	void data_disconnect();

//----------------------------------------------------- Attributs protégés
	in_addr clientAddress;				// Adresse du client
	int clientPort;						// Port d'écoute du client
	int sock;							// Descripteur de la socket

};

//--------------------------- Autres définitions dépendantes de <DataTransfertTCP>

#endif // DATATRANSFERTTCP_H

