/*************************************************************************
                           DataTransfertTCPPull  -  description
                             -------------------
    début                : ...
    copyright            : (C) 2011 par Pierre LULÉ
*************************************************************************/

//---------- Réalisation de la classe <DataTransfertTCPPull> (fichier DataTransfertTCPPull.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "DataTransfertTCPPull.h"


//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

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


//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

DataTransfertTCPPull::~DataTransfertTCPPull ( )
// Algorithme :
//
{

} //----- Fin de ~DataTransfertTCPPull


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

