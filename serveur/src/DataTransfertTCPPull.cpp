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
    data_connect();
    bool end = false;
    while (!end)
    {
        char msg[PIPE_SIZE];
        read(pipefd, msg, PIPE_SIZE);
        string cmd = msg;
        if (cmd == "END")
        {
            end = true;
        }
        else
        {
        	int image_id = atoi(cmd.c_str());
        	if(image_id == -1) image_id = ++currentImage;
            data_send(image_id);
        }
    }
    data_disconnect();
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

