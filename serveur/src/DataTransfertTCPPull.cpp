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
// type DataTransfertTCPPull::M�thode ( liste des param�tres )
// Algorithme :
//
//{
//} //----- Fin de M�thode


//------------------------------------------------- Surcharge d'op�rateurs

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

//----------------------------------------------------- M�thodes prot�g�es
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
