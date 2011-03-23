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
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //


//------------------------------------------------- Surcharge d'opérateurs

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
//----------------------------------------------------- Méthodes protégées
    void Run();
//----------------------------------------------------- Attributs protégés

};

//--------------------------- Autres définitions dépendantes de <DataTransfertTCPPull>

#endif // DATATRANSFERTTCPPULL_H

