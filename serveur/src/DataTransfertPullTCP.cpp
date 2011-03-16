/*************************************************************************
                           DataTransfertPullTCP  -  description
                             -------------------
    début                : Mars 2011
    copyright            : (C) 2011 par Pierre LULÉ
*************************************************************************/

//---------- Réalisation de la classe <DataTransfertPullTCP> (fichier DataTransfertPullTCP.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "DataTransfertPullTCP.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type DataTransfertPullTCP::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode
virtual void* Run( void* args)
{
    
    for(;;)
    {
        
    }
}


//------------------------------------------------- Surcharge d'opérateurs

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

//----------------------------------------------------- Méthodes protégées

