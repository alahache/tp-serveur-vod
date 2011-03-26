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

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

