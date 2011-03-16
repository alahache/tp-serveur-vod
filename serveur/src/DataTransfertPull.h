/*************************************************************************
 *                           DataTransfertPull  -  description
 *                             -------------------
 *    début                : Mars 2011
 *    copyright            : (C) 2011 par Pierre LULÉ
 *    e-mail               : pierre.lule@insa-lyon.fr
 *************************************************************************/

//---------- Interface de la classe <DataTransfertPull> (fichier DataTransfertPull.h) ------
#if ! defined ( DATATRANSFERTPULL_H )
#define DATATRANSFERTPULL_H

//--------------------------------------------------- Interfaces utilisées
#include "DataTransfert.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <DataTransfertPull>
// Interface de DataTransfert adaptée à un serveur de type pull (image par
// image)
//
//------------------------------------------------------------------------

class DataTransfertPull : public DataTransfert
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
    
    virtual ~DataTransfertPull ( );
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    //------------------------------------------------------------------ PRIVE
    
protected:
    //----------------------------------------------------- Méthodes protégées
    virtual void Send ( int id ) = 0;
    // Envoie au client l'image repérée par <id>
    
    //----------------------------------------------------- Attributs protégés
    
};

//--------------------------- Autres définitions dépendantes de <DataTransfertPull>

#endif // DATATRANSFERTPULL_H

