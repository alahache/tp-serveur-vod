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
#include <fstream>
#include <sstream>
#include <cstdlib>

//------------------------------------------------------ Include personnel
#include "DataTransfertTCP.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

void DataTransfertTCP::connect()
{
	sock = socket(PF_INET, SOCK_STREAM, 0);
	if(sock == -1)
	{
		cerr << "Erreur: socket" << endl;
		exit(EXIT_FAILURE);
	}

	sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_addr 	= clientAddress;
		addr.sin_port 	= htons(clientPort);

	if (connect(sock, (sockaddr *) &addr, sizeof(addr)) == -1)
	{
		cerr << "Erreur: connect" << endl;
		exit(EXIT_FAILURE);
	}
}

void DataTransfertTCP::send(int id)
{
	// Ouverture de l'image
	ifstream fs(stream.GetImagePath(id).c_str());
	if(fs.fail())
	{
		currentImage = 0;
		send(currentImage);
		return;
	}

	// Taille de l'image
	fs.seekg(0, ios::end);
	long filelength = fs.tellg();
	fs.seekg(0, ios::beg);

	// On alloue la mémoire :
	char* filebuffer = new char[filelength];

	// On lit le fichier en bloc :
	fs.read(filebuffer, length);
	fs.close();

	// Construction du header :
	stringstream msg_header;
	msg_header << id << CRLF;
	msg_header << length << CRLF;
	string str_header = header.str();

	// Assembage header + contenu fichier :
	long msglength = filelength + str_header.size();
	char* msg = new char[msglength];
	memcpy(msg, str_header.c_str(), str_header.size());
	memcpy(msg + str_header.size(), filebuffer, filelength);

	// Envoi du message :
	long total_sent = 0;
	while(total_sent < responselength)
	{
		long sent = send(sock, msg, msglength, 0);
		if(sent == -1)
		{
		    cerr << "[" fd << "] Erreur envoi de données (send)" << endl;
		    cerr << strerror(errno) << endl;
		    break;
		}
		total_sent += sent;
	}

	delete[] filebuffer;
	delete[] msg;
}

void DataTransfertTCP::disconnect()
{
	close(sock);
}
