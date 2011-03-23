/*************************************************************************
                           DataTransfertTCPPull  -  description
                             -------------------
    d�but                : ...
    copyright            : (C) 2011 par Pierre LUL�
*************************************************************************/

//---------- R�alisation de la classe <DataTransfertTCPPull> (fichier DataTransfertTCPPull.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include syst�me
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "DataTransfertTCPPull.h"


//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- M�thodes publiques

void  DataTransfertTCPPull::Begin()
{
	char[PIPE_SIZE] cmd;
    bool fin = false;
    while (!fin)
    {
        read(pipe, cmd, PIPE_SIZE);
        if (cmd == "end")
        {
            fin = false;
        }
        else
        {
            Send(atoi(cmd));
        }
    }
}


//------------------------------------------------- Surcharge d'op�rateurs

//-------------------------------------------- Constructeurs - destructeur

DataTransfertTCPPull::~DataTransfertTCPPull ( )
// Algorithme :
//
{

} //----- Fin de ~DataTransfertTCPPull


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- M�thodes prot�g�es

