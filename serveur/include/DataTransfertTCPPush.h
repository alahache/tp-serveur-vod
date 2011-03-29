/*************************************************************************
                           DataTransfertTCPPush  -  description
                             -------------------
    début                : ...
    copyright            : (C) 2011 par Pierre LULÉ
*************************************************************************/

//---------- Interface de la classe <DataTransfertTCPPush> (fichier DataTransfertTCPPush.h) ------
#if ! defined ( DATATRANSFERTTCPPUSH_H )
#define DATATRANSFERTTCPPUSH_H

//--------------------------------------------------- Interfaces utilisées
#include "DataTransfertTCP.h"

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Rôle de la classe <DataTransfertTCPPush>
//
//
//------------------------------------------------------------------------ 

class DataTransfertTCPPush : public DataTransfertTCP
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

	void* Begin();

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

	DataTransfertTCPPush(Stream& _stream, in_addr _clientAddress, int _clientPort, int _pipefd)
    	: DataTransfertTCP(_stream, _clientAddress, _clientPort), pipefd(_pipefd) {}
	// Mode d'emploi :
	//
	// Contrat :
	//

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées
	void setNonBlocking(int fd);
	void setBlocking(int fd);

//----------------------------------------------------- Attributs protégés
	int pipefd;					// Descripteur de lecture pour le pipe
    
};

//--------------------------- Autres définitions dépendantes de <DataTransfertTCPPush>

#endif // DATATRANSFERTTCPPUSH_H

