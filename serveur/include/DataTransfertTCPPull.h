/*************************************************************************
                           DataTransfertTCPPull  -  description
                             -------------------
    d�but                : ...
    copyright            : (C) 2011 par Pierre LUL�
*************************************************************************/

//---------- Interface de la classe <DataTransfertTCPPull> (fichier DataTransfertTCPPull.h) ------
#if ! defined ( DATATRANSFERTTCPPULL_H )
#define DATATRANSFERTTCPPULL_H

//--------------------------------------------------- Interfaces utilis�es
#include "DataTransfertTCP.h"
//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// R�le de la classe <DataTransfertTCPPull>
//
//
//------------------------------------------------------------------------ 

class DataTransfertTCPPull : public DataTransfertTCP
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- M�thodes publiques
    
    void Begin();

//------------------------------------------------- Surcharge d'op�rateurs

//-------------------------------------------- Constructeurs - destructeur

    DataTransfertTCPPull (Stream& _stream, in_addr _clientAddress, int _clientPort, int _pipefd)
    	: DataTransfertTCP(_stream, _clientAddress, _clientPort, _pipefd){}
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
//----------------------------------------------------- M�thodes prot�g�es

//----------------------------------------------------- Attributs prot�g�s

};

//--------------------------- Autres d�finitions d�pendantes de <DataTransfertTCPPull>

#endif // DATATRANSFERTTCPPULL_H

