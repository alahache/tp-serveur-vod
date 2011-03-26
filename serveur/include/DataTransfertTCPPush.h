/*************************************************************************
                           DataTransfertTCPPush  -  description
                             -------------------
    d�but                : ...
    copyright            : (C) 2011 par Pierre LUL�
*************************************************************************/

//---------- Interface de la classe <DataTransfertTCPPush> (fichier DataTransfertTCPPush.h) ------
#if ! defined ( DATATRANSFERTTCPPUSH_H )
#define DATATRANSFERTTCPPUSH_H

//--------------------------------------------------- Interfaces utilis�es

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// R�le de la classe <DataTransfertTCPPush>
//
//
//------------------------------------------------------------------------ 

class DataTransfertTCPPush : public DataTransfertTCP
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
//----------------------------------------------------- M�thodes prot�g�es

//----------------------------------------------------- Attributs prot�g�s
    int frgmt_size;
};

//--------------------------- Autres d�finitions d�pendantes de <DataTransfertTCPPush>

#endif // DATATRANSFERTTCPPUSH_H

