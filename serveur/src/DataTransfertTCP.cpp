/*************************************************************************
                           DataTransfertTCP  -  description
                             -------------------
    début                : Mars 2011
    copyright            : (C) 2011 par Pierre LULÉ
*************************************************************************/

//---------- Réalisation de la classe <DataTransfertTCP> (fichier DataTransfertTCP.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "DataTransfertTCP.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

void DataTransfertTCP::connect()
{
	sock = socket(PF_INET, SOCK_STREAM, 0);
    
    if (connect (sock, (sockaddr *) &address, sizeof address) == -1)
    {
        cerr << "Connection failed" << endl;
        exit(EXIT_FAILURE);
    }
}

void DataTransfertTCP::send(int id)
{
    if (id = -1)
    {
        id = ++currentPicture;
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
            // Taille de l'image
            img.seekg(0, ios::end);
            long length = fs.tellg();
            img.seekg(0, ios::beg);

            // Construction du message
            stringstream msg_stream;
            msg_stream << id << CRLF;
            msg_stream << length << CRLF;
            msg_stream << fs;

            // Préparation du message
            long msg_size = msg.size();
            char* msg = new char[msg_size];
            memcpy(msg, msg_stream.c_str(), msg_size);

            // Envoi du message
            long total_sent = 0;
            while(total_sent < responselength)
            {
                long sent = send(sock, msg, msg_size, 0);
                if(sent == -1)
                {
                    cerr << "[" fd << "] Erreur envoi de données (send)" << endl;
                    cerr << strerror(errno) << endl;
                    break;
                }
                total_sent += sent;
            }
        }
    }
}

void DataTransfertTCP::disconnect()
{

}
