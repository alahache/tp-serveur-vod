/*************************************************************************
                           DataTransfertUDPPull  -  description
                             -------------------
    début                : ...
    copyright            : (C) 2011 par Arnaud Lahache
*************************************************************************/

//---------- Réalisation de la classe <DataTransfertUDPPull> (fichier DataTransfertUDPPull.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstdlib>

//------------------------------------------------------ Include personnel
#include "DataTransfertUDPPull.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void* DataTransfertUDPPull::Begin()
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

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

