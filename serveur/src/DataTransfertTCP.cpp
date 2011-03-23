/*************************************************************************
                           DataTransfertTCP  -  description
                             -------------------
    d�but                : Mars 2011
    copyright            : (C) 2011 par Pierre LUL�
*************************************************************************/

//---------- R�alisation de la classe <DataTransfertTCP> (fichier DataTransfertTCP.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include syst�me
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "DataTransfertTCP.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- M�thodes publiques
// type DataTransfertTCP::M�thode ( liste des param�tres )
// Algorithme :
//
//{
//} //----- Fin de M�thode
void DataTransfertTCP::Begin( )
{

    sock = socket(PF_INET, SOCK_STREAM, 0);
    
    if (connect (sock, (sockaddr *) &address, sizeof address) == -1)
    {
        cerr << "Connection failed" << endl;
        exit(EXIT_FAILURE);
    }

    Run();
}

void DataTransfertTCP::Send(int id)
{
    if (id = -1)
    {
        id = currentPicture;
    }
    else
    {
        // Ouverture de l'image
        ifstream img(stream.GetImagePath(i).c_str());
        if (img.fail())
        {
            cerr << "Could not open file " << stream.GetImagePath << endl;
            exit (EXIT_FAILURE);
        }
        else
        {
            // Taille
            img.seekg(0, ios::end);
            long length = fs.tellg();
            img.seekg(0, ios::beg);

            // Construction du message
            stringstream msg_stream;
            msg_stream << id << CRLF;
            msg_stream << length << CRLF;
            msg_stream << fs;

            // Pr�paration du message
            long msg_size = msg.size();
            char* msg = new char[msg_size];
            memcpy(msg, msg_stream.c_str(), msg_size);

            // Envoie du message
            long total_sent = 0;
            while(total_sent < responselength)
            {
                long sent = send(sock, msg, msg_size, 0);
                if(sent == -1)
                {
                    cerr << "[" fd << "] Erreur envoi de donn�es (send)" << endl;
                    cerr << strerror(errno) << endl;
                    break;
                }
                total_sent += sent;
            }
        }
    }
}

//------------------------------------------------- Surcharge d'op�rateurs

//-------------------------------------------- Constructeurs - destructeur

DataTransfertTCP::~DataTransfertTCP ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <DataTransfertTCP>" << endl;
#endif
    close(sock);
} //----- Fin de ~DataTransfertTCP

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- M�thodes prot�g�es

