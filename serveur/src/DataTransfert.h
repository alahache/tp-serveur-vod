/*************************************************************************
                           DataTransfert  -  description
                             -------------------
    début                : Mars 2011
    copyright            : (C) 2011 par Pierre LULÉ
    *************************************************************************/

//---------- Interface de la classe <DataTransfert> (fichier DataTransfert.h) ------
#if ! defined ( DATATRANSFERT_H )
#define DATATRANSFERT_H

//--------------------------------------------------- Interfaces utilisées
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <fstream>
#include "Stream.h"
//------------------------------------------------------------- Constantes
const int PIPE_SIZE = 100;

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <DataTransfert>
// Interface d'un thread gérant la connexion avec un client.
//
//------------------------------------------------------------------------

class DataTransfert
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

	virtual void Begin( ) = 0;
	// Routine d'execution

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

	DataTransfert ( Stream& _stream, in_addr _clientAddress, int _clientPort, int _pipefd)
	: stream(_stream), address(_address), port(_port), pipefd(_pipefd), currentPicture(0){ };
	// <stream> : référence vers le flux associé au client
	// <address> : addresse du client
	// <port> : port de communication du client

	virtual ~DataTransfert ( );
	// Mode d'emploi : Détruit l'objet et ferme la connection
	//
	// Contrat :
	//

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
	virtual void Run( ) = 0;
    
//----------------------------------------------------- Attributs protégés
	Stream& stream;
	in_addr clientAddress;
	int clientPort;
	int pipefd;
	int sock;
	int currentPicture;

};

//--------------------------- Autres définitions dépendantes de <DataTransfert>

#endif // DATATRANSFERT_H

