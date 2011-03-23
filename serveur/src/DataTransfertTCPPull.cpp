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
// type DataTransfertTCPPull::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode


//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

DataTransfertTCPPull::~DataTransfertTCPPull ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <DataTransfertTCPPull>" << endl;
#endif
} //----- Fin de ~DataTransfertTCPPull


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
void DataTransfertTCPPull::Run()
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
