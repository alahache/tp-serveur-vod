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
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //
    void Begin( );

    void Send(int id);
    

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    DataTransfertTCP ( Stream& stream, sockaddr_in address, int port, int& pipe ) : DataTransfert(stream, address, port, &pipe){}


    virtual ~DataTransfertTCP ( ){}
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

};

//--------------------------- Autres définitions dépendantes de <DataTransfertTCP>

#endif // DATATRANSFERTTCP_H

