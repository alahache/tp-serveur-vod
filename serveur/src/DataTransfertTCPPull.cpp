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
#include <cstdlib>

//------------------------------------------------------ Include personnel
#include "DataTransfertTCPPull.h"


//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void* DataTransfertTCPPull::Begin()
{
    bool end = false;
    while (!end)
    {
    	char[PIPE_SIZE] msg;
        read(pipe, msg, PIPE_SIZE);
        string cmd = msg;
        if (cmd == "end")
        {
            end = true;
        }
        else
        {
        	int image_id = atoi(cmd);
        	if(image_id == -1) image_id = ++currentImage;
            send(image_id);
        }
    }
    
    return 0;
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

