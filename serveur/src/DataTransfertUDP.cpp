/*************************************************************************
                           DataTransfertUDP  -  description
                             -------------------
    début                : ...
    copyright            : (C) 2011 par Arnaud Lahache
*************************************************************************/

//---------- Réalisation de la classe <DataTransfertUDP> (fichier DataTransfertUDP.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

//------------------------------------------------------ Include personnel
#include "DataTransfertUDP.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

void DataTransfertUDP::connect()
{
	sock = socket(PF_INET, SOCK_DGRAM, 0);
	if(sock == -1)
	{
		cerr << "Erreur: socket" << endl;
		exit(EXIT_FAILURE);
	}
	
	addr.sin_family = AF_INET;
	addr.sin_addr 	= clientAddress;
	addr.sin_port 	= htons(clientPort);
}

void DataTransfertUDP::send(int id)
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
	
	// Transfert des fragments :
	int fragment_pos = 0;
	while(!fs.eof())
	{
		// Construction du header :
		stringstream msg_header;
		msg_header << id << CRLF;
		msg_header << filelength << CRLF;
		msg_header << fragment_pos << CRLF;
		msg_header << fragmentSize << CRLF;
		string str_header = msg_header.str();
		
		// On va lire le bon fragment d'image :
		long imgfraglength = fragmentSize - str_header.size();
		char* filebuffer = new char[imgfraglength];
		fs.read(filebuffer, imgfraglength);
		
		// Assembage header + buffer :
		long msglength = imgfraglength + str_header.size();
		char* msg = new char[msglength];
		memcpy(msg, str_header.c_str(), str_header.size());
		memcpy(msg + str_header.size(), filebuffer, imgfraglength);
		
		// Envoi du message :
		long total_sent = 0;
		while(total_sent < msglength)
		{
			long sent = sendto(sock, msg, msglength, &addr, sizeof(addr));
			if(sent == -1)
			{
				cerr << "[" fd << "] Erreur envoi de données (sendto)" << endl;
				cerr << strerror(errno) << endl;
				break;
			}
			total_sent += sent;
		}
		
		delete[] msg;
		delete[] filebuffer;
	}

	// On ferme le fichier :
	fs.close();
	
}

void DataTransfertUDP::disconnect()
{
	close(sock);
}
