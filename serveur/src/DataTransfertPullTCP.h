/*************************************************************************
                           DataTransfertPullTCP  -  description
                             -------------------
    début                : Mars 2011
    copyright            : (C) 2011 par Pierre LULÉ
*************************************************************************/

//---------- Interface de la classe <DataTransfertPullTCP> (fichier DataTransfertPullTCP.h) ------
#if ! defined ( DATATRANSFERTPULLTCP_H )
#define DATATRANSFERTPULLTCP_H

//--------------------------------------------------- Interfaces utilisées
#include "DataTransfertPull.h"
//------------------------------------------------------------- Constantes 
const BUFFER_SIZE = 1024;
//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Rôle de la classe <DataTransfertPullTCP>
// Implémentation de DataTransfertPull pour TCP
//
//------------------------------------------------------------------------ 

class DataTransfertPullTCP : public DataTransfertPull
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

    virtual ~DataTransfertPullTCP ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

};

//--------------------------- Autres définitions dépendantes de <DataTransfertPullTCP>

#endif // DATATRANSFERTPULLTCP_H

