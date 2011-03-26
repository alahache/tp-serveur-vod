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
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //


//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

    DataTransfertTCPPush (  Stream& stream, sockaddr_in address, int port, int& pipe, int _frgmt_size ) :
        DataTransfertTCP(stream, address, port, &pipe), frgmt_size(_frgmt_size){}
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~DataTransfertTCPPush ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    int frgmt_size;
};

//--------------------------- Autres définitions dépendantes de <DataTransfertTCPPush>

#endif // DATATRANSFERTTCPPUSH_H

