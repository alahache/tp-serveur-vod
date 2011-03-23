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

    virtual void Begin() = 0;
    
//------------------------------------------------- Surcharge d'op�rateurs

//-------------------------------------------- Constructeurs - destructeur

    DataTransfertTCP ( Stream& _stream, in_addr _clientAddress, int _clientPort, int _pipefd )
    	: DataTransfert(_stream, _clientAddress, _clientPort, _pipefd) {}

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- M�thodes prot�g�es

	void connect();
	void send(int imageId);
	void disconnect();

//----------------------------------------------------- Attributs prot�g�s

};

//--------------------------- Autres d�finitions d�pendantes de <DataTransfertTCP>

#endif // DATATRANSFERTTCP_H

