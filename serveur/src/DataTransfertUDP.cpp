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
#include <cstring>
#include <errno.h>

//------------------------------------------------------ Include personnel
#include "DataTransfertUDP.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

void DataTransfertUDP::data_connect()
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

void DataTransfertUDP::data_send(int id)
{
	// Ouverture de l'image
	ifstream fs(stream.GetImagePath(id).c_str());
	if(fs.fail())
	{
		currentImage = 0;
        id = 0;
        fs.open(stream.GetImagePath(id).c_str());
        if (fs.fail())
        {
            cerr << "La vidéo " << stream.GetImagePath(id).c_str() << " est introuvable." << endl;
            exit(EXIT_FAILURE);
        }
	}
	
	// Taille de l'image
	fs.seekg(0, ios::end);
	long filelength = fs.tellg();
	fs.seekg(0, ios::beg);
	
	// Transfert des fragments :
	int fragment_pos = 0;
	long currentFragmentSize = fragmentSize;
	while(!fs.eof())
	{
	
		// Construction du header :
		stringstream msg_header;
		msg_header << id << CRLF;
		msg_header << filelength << CRLF;
		msg_header << fragment_pos << CRLF;
		msg_header << currentFragmentSize << CRLF;
		string str_header = msg_header.str();
		
		// On va lire le bon fragment d'image :
		long imgfrag_maxlength = fragmentSize - str_header.size();
		char* filebuffer = new char[imgfrag_maxlength];
		fs.read(filebuffer, imgfrag_maxlength);
		long imgfrag_readlength = fs.gcount();
		
		// Taille finale de la trame à envoyer :
		long fraglength = imgfrag_readlength + str_header.size();
		
		// Si jamais on envoie moins d'octets que prévu, on modifie le header :
		if(imgfrag_readlength < currentFragmentSize)
		{
			// On construit la chaîne fragmentSize :
			stringstream ss_currentFragmentSize;
			ss_currentFragmentSize << currentFragmentSize;
			string str_currentFragmentSize = ss_currentFragmentSize.str();
			
			// Puis la chaîne fraglength
			stringstream ss_imgfrag_readlength;
			ss_imgfrag_readlength << imgfrag_readlength;
			string str_imgfrag_readlength = ss_imgfrag_readlength.str();
			
			// On va compléter avec des zéros pour ne pas modifier la taille du header :
			stringstream newCurrentFragmentSize;
			for(int i=0; i<(str_currentFragmentSize.size() - str_imgfrag_readlength.size()); i++)
				newCurrentFragmentSize << '0';
			newCurrentFragmentSize << str_imgfrag_readlength;
			string str_newCurrentFragmentSize = newCurrentFragmentSize.str();
			
			// On va remplacer le fragmentSize dans le header par str_new_fragsize
			string str_find 	= CRLF + str_currentFragmentSize + CRLF;
			string str_replace 	= CRLF + str_newCurrentFragmentSize + CRLF;
			str_header.replace(str_header.find(str_find), str_replace.size(), str_replace);
		}
		
		// Assembage header + buffer :
		char* msg = new char[fraglength];
		memcpy(msg, str_header.c_str(), str_header.size());
		memcpy(msg + str_header.size(), filebuffer, imgfrag_readlength);
		
		//cout << msg << endl;
		
		// Envoi du message :
		long total_sent = 0;
		while(total_sent < fraglength)
		{
			long sent = sendto(sock, msg, fraglength, 0, (sockaddr*) &addr, sizeof(addr));
			if(sent == -1)
			{
				cerr << "[" << sock << "] Erreur envoi de données (sendto)" << endl;
				cerr << strerror(errno) << endl;
				break;
			}
			total_sent += sent;
		}
		
		//cout << "sent : " << total_sent << endl;
		
		delete[] msg;
		delete[] filebuffer;
		
		fragment_pos+=imgfrag_readlength;
	}

	// On ferme le fichier :
	fs.close();
	
}

void DataTransfertUDP::data_disconnect()
{
	close(sock);
}
