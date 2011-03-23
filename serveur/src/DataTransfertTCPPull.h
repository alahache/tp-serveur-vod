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
    // type M�thode ( liste des param�tres );
    // Mode d'emploi :
    //
    // Contrat :
    //


//------------------------------------------------- Surcharge d'op�rateurs

//-------------------------------------------- Constructeurs - destructeur

    DataTransfertTCPPull (  Stream& stream, sockaddr_in address, int port, int& pipe ) : DataTransfertTCP(stream, address, port, &pipe){}
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
    void Run();
//----------------------------------------------------- Attributs prot�g�s

};

//--------------------------- Autres d�finitions d�pendantes de <DataTransfertTCPPull>

#endif // DATATRANSFERTTCPPULL_H

