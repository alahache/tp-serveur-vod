/*************************************************************************
                           DataTransfertPullTCP  -  description
                             -------------------
    d�but                : Mars 2011
    copyright            : (C) 2011 par Pierre LUL�
*************************************************************************/

//---------- R�alisation de la classe <DataTransfertPullTCP> (fichier DataTransfertPullTCP.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include syst�me
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "DataTransfertPullTCP.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- M�thodes publiques
// type DataTransfertPullTCP::M�thode ( liste des param�tres )
// Algorithme :
//
//{
//} //----- Fin de M�thode
virtual void* Run( void* args)
{
    
    for(;;)
    {
        
    }
}


//------------------------------------------------- Surcharge d'op�rateurs

//-------------------------------------------- Constructeurs - destructeur
DataTransfertPullTCP::DataTransfertPullTCP ( )
// Construction de l'objet et ouverture de la connection
{
    char buffer[BUFFER_SIZE] = "test";/*
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == INVALID_SOCKET)
    {
        cerr << "Socket creation failure" << endl;
        exit(EXIT_FAILURE);
    }*/
/*
    if(bind (sock, (SOCKADDR *) &addresse, sizeof addresse) == SOCKET_ERROR)
    {
        cerr << "Socket binding failure" << endl;
        exit(EXIT_FAILURE);
    }
*/
    if (connect (sock, (SOCKADDR *) &adrresse, sizeof addresse) == SOCKET_ERROR)
    {
        cerr << "Connection failed" << endl;
        exit(EXIT_FAILURE);
    }
    if(send(sock, buffer, strlen(buffer), 0) < 0)
    {
        perror("send()");
        exit(errno);
    }
}


DataTransfertPullTCP::~DataTransfertPullTCP ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <DataTransfertPullTCP>" << endl;
#endif
    closesocket(sock);
} //----- Fin de ~DataTransfertPullTCP


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- M�thodes prot�g�es

