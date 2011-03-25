/*************************************************************************
                           DataTransfertUDP  -  description
                             -------------------
    d�but                : ...
    copyright            : (C) 2011 par Arnaud Lahache
*************************************************************************/

//---------- Interface de la classe <DataTransfertUDP> (fichier DataTransfertUDP.h) ------
#if ! defined ( DATATRANSFERTUDP_H )
#define DATATRANSFERTUDP_H

//--------------------------------------------------- Interfaces utilis�es
#include "DataTransfert.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// R�le de la classe <DataTransfertUDP>
//	- Impl�mentation de DataTransfert pour UDP
//	- D�finition des m�thodes utilis�es pour envoyer des images du
//	  flux avec le protocole UDP
//------------------------------------------------------------------------ 

class DataTransfertUDP : public DataTransfert
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- M�thodes publiques

	virtual void Begin() = 0;

//-------------------------------------------- Constructeurs - destructeur

	DataTransfertUDP(Stream& _stream, in_addr _clientAddress, int _clientPort, unsigned int _fragmentSize)
    	: DataTransfert(_stream), clientAddress(_clientAddress), clientPort(_clientPort), fragmentSize(_fragmentSize) {}
    // Mode d'emploi :
	// 	<_stream>			: r�f�rence vers le flux associ� au transfert
	// 	<_clientAddress>	: addresse du client
	// 	<_clientPort>		: port d'�coute du client
	// 	<_fragmentSize>		: taille des fragments de donn�es envoy�s
	//
	//	- Construit une nouvelle instance de la classe DataTransfertUDP.

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- M�thodes prot�g�es
	void connect();
	void send(int imageId);
	void disconnect();

//----------------------------------------------------- Attributs prot�g�s
	in_addr clientAddress;				// Adresse du client
	int clientPort;						// Port d'�coute du client
	int sock;							// Descripteur de la socket
	unsigned int fragmentSize;			// Taille des fragments de donn�es

};

//--------------------------- Autres d�finitions d�pendantes de <DataTransfertUDP>

#endif // DATATRANSFERTUDP_H

