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

//------------------------------------------------------------- Constantes 
const int BUFFER_SIZE = 1024;

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Rôle de la classe <DataTransfertTCP>
// Implémentation de DataTransfert pour TCP
//
//------------------------------------------------------------------------ 

class DataTransfertTCP : public DataTransfert
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    virtual void Begin() = 0;
    
//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

    DataTransfertTCP ( Stream& _stream, in_addr _clientAddress, int _clientPort, int _pipefd )
    	: DataTransfert(_stream, _clientAddress, _clientPort, _pipefd) {}

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées

	void connect();
	void send(int imageId);
	void disconnect();

//----------------------------------------------------- Attributs protégés

};

//--------------------------- Autres définitions dépendantes de <DataTransfertTCP>

#endif // DATATRANSFERTTCP_H

