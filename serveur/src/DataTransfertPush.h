/*************************************************************************
 *                           DataTransfertPush  -  description
 *                             -------------------
 *    début                : Mars 2011
 *    copyright            : (C) 2011 par Pierre LULÉ
 *    e-mail               : pierre.lule@insa-lyon.fr
 *************************************************************************/

//---------- Interface de la classe <DataTransfertPush> (fichier DataTransfertPush.h) ------
#if ! defined ( DATATRANSFERTPUSH_H )
#define DATATRANSFERTPUSH_H

//--------------------------------------------------- Interfaces utilisées
#include "DataTransfert.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <DataTransfertPush>
// Interface d'un DataTransfert adapté au mode de diffusion type 'push'
// (start, pause, end)
//------------------------------------------------------------------------

class DataTransfertPush : public DataTransfert
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
    
    virtual ~DataTransfertPush ( );
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    //------------------------------------------------------------------ PRIVE
    
protected:
    //----------------------------------------------------- Méthodes protégées
    
    //----------------------------------------------------- Attributs protégés

};

//--------------------------- Autres définitions dépendantes de <DataTransfertPush>

#endif // DATATRANSFERTPUSH_H

