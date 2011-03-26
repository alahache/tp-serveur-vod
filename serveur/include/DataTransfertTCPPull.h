/*************************************************************************
                           DataTransfertTCPPull  -  description
                             -------------------
    début                : ...
    copyright            : (C) 2011 par Pierre LULÉ
*************************************************************************/

//---------- Interface de la classe <DataTransfertTCPPull> (fichier DataTransfertTCPPull.h) ------
#if ! defined ( DATATRANSFERTTCPPULL_H )
#define DATATRANSFERTTCPPULL_H

//--------------------------------------------------- Interfaces utilisées
#include "DataTransfertTCP.h"

//------------------------------------------------------------- Constantes
const unsigned int PIPE_SIZE = 100;

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Rôle de la classe <DataTransfertTCPPull>
//
//
//------------------------------------------------------------------------ 

class DataTransfertTCPPull : public DataTransfertTCP
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    
    void* Begin();

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

    DataTransfertTCPPull (Stream& _stream, in_addr _clientAddress, int _clientPort, int _pipefd)
    	: DataTransfertTCP(_stream, _clientAddress, _clientPort), pipefd(_pipefd) {}
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~DataTransfertTCPPull ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
	int pipefd;					// Descripteur de lecture pour le pipe

};

//--------------------------- Autres définitions dépendantes de <DataTransfertTCPPull>

#endif // DATATRANSFERTTCPPULL_H

