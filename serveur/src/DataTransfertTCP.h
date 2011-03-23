/*************************************************************************
                           DataTransfertTCP  -  description
                             -------------------
    d�but                : Mars 2011
    copyright            : (C) 2011 par Pierre LUL�
*************************************************************************/

//---------- Interface de la classe <DataTransfertTCP> (fichier DataTransfertTCP.h) ------
#if ! defined ( DATATRANSFERTTCP_H )
#define DATATRANSFERTTCP_H

//--------------------------------------------------- Interfaces utilis�es
#include "DataTransfert.h"
//------------------------------------------------------------- Constantes 
const int BUFFER_SIZE = 1024;
//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// R�le de la classe <DataTransfertTCP>
// Impl�mentation de DataTransfert pour TCP
//
//------------------------------------------------------------------------ 

class DataTransfertTCP : public DataTransfert
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- M�thodes publiques
    // type M�thode ( liste des param�tres );
    // Mode d'emploi :
    //
    // Contrat :
    //
    void Begin( );

    void Send(int id);
    

//------------------------------------------------- Surcharge d'op�rateurs

//-------------------------------------------- Constructeurs - destructeur
    DataTransfertTCP ( Stream& stream, sockaddr_in address, int port, int& pipe ) : DataTransfert(stream, address, port, &pipe){}


    virtual ~DataTransfertTCP ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- M�thodes prot�g�es

//----------------------------------------------------- Attributs prot�g�s

};

//--------------------------- Autres d�finitions d�pendantes de <DataTransfertTCP>

#endif // DATATRANSFERTTCP_H

