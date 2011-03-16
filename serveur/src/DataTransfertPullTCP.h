/*************************************************************************
                           DataTransfertPullTCP  -  description
                             -------------------
    d�but                : Mars 2011
    copyright            : (C) 2011 par Pierre LUL�
*************************************************************************/

//---------- Interface de la classe <DataTransfertPullTCP> (fichier DataTransfertPullTCP.h) ------
#if ! defined ( DATATRANSFERTPULLTCP_H )
#define DATATRANSFERTPULLTCP_H

//--------------------------------------------------- Interfaces utilis�es
#include "DataTransfertPull.h"
//------------------------------------------------------------- Constantes 
const BUFFER_SIZE = 1024;
//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// R�le de la classe <DataTransfertPullTCP>
// Impl�mentation de DataTransfertPull pour TCP
//
//------------------------------------------------------------------------ 

class DataTransfertPullTCP : public DataTransfertPull
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

    virtual ~DataTransfertPullTCP ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- M�thodes prot�g�es

//----------------------------------------------------- Attributs prot�g�s

};

//--------------------------- Autres d�finitions d�pendantes de <DataTransfertPullTCP>

#endif // DATATRANSFERTPULLTCP_H

