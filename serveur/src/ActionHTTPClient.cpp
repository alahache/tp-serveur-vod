/*************************************************************************
                           ActionHTTPClient  -  description
                             -------------------
    début                : ...
    copyright            : (C) 2011 par Arnaud Lahache
*************************************************************************/

//---------- Réalisation de la classe <ActionHTTPClient> (fichier ActionHTTPClient.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/socket.h>
#include <ctime>
#include <cstring>
#include <errno.h>

//------------------------------------------------------ Include personnel
#include "ActionHTTPClient.h"

//----------------------------------------------------------------- PUBLIC

//------------------------------------------------------------- Constantes
const string CRLF = "\r\n";

//----------------------------------------------------- Méthodes publiques
void ActionHTTPClient::Execute(epoll_event event)
{
	char buffer[BUFFER_SIZE];
	int fd = event.data.fd;
	
	if(event.events & EPOLLHUP)
	{
		// DECONNEXION
		Disconnect(fd);
	}
	else if(event.events & EPOLLERR)
	{
		// ERREUR QUELCONQUE
		cerr << "[" << fd << "] Erreur de transfert" << endl;
	}
	else if(event.events & EPOLLIN)
	{
		// DEMANDE DE LECTURE
		//cout << "[" << fd << "] Réception d'une requête de lecture..." << endl;
		
		int received = recv(fd, buffer, BUFFER_SIZE, 0);
		//int received = read(fd, buffer, BUFFER_SIZE);
		if(received > 0)
		{
			// LECTURE D'UN MESSAGE
			buffer[received] = '\0';
			//cout << "[" << fd << "] Lecture de " << received << " octets : " << buffer << endl;
			
			stringstream ss(buffer);
			
			// On va lire la commande du protocole HTTP :
			string filename, type;
			string line;
			while(getline(ss, line))
			{
				string att, val;
				stringstream ssline(line);
				ssline >> att >> val;
				if(att == "GET")
				{
					// Le client veut récupérer un fichier :
					if(val == "/" || val == "")
						filename = WWW_DIRECTORY + "catalogue.txt";
					else
						filename = WWW_DIRECTORY + val;
					
					// On vérifie le type du fichier :
					type = "text/plain";
					string ext = filename.substr(filename.find_first_of('.') + 1);
					if(ext == "html" || ext == "htm")
						type = "text/html";
					else if(ext == "css")
						type = "text/css";
					else if(ext == "jpeg" || ext == "jpg")
						type = "image/jpeg";
					else if(ext == "gif" || ext == "png")
						type = "image/" + ext;
				}
			}
			
			// On récupère le contenu du fichier :
			char *filebuffer;
			long filelength = readFile(filename, filebuffer, type);
			if(filelength != -1)
			{
			
				// On construit le header de la réponse :
				stringstream header;
				header << "HTTP/1.1 200 OK" << CRLF;
				header << "Server: VODServer (Linux)" << CRLF;
				header << "Accept-Ranges: bytes" << CRLF;
				header << "Content-Length: " << filelength << CRLF;
				header << "Connection: close" << CRLF;
				header << "Content-Type: " << type << "; charset=UTF-8" << CRLF;
				header << CRLF;
				string str_header = header.str();
				
				// Assembage header + contenu fichier :
				long responselength = filelength + str_header.size();
				char* response = new char[responselength];
				memcpy(response, str_header.c_str(), str_header.size());
				memcpy(response + str_header.size(), filebuffer, filelength);
				
				// On envoie la réponse en une seule fois :
				// /!\ 	Attention : cet envoi peut ralentir les performances du serveur
				//		si le fichier envoyé est trop gros : L'exécution bloque tant
				//		que le fichier entier n'a pas été envoyé.
				long total_sent = 0;
				while(total_sent < responselength)
				{
					long sent = send(fd, response, responselength, 0);
					if(sent == -1)
					{
						cerr << "[" << fd << "] Erreur envoi de données (send)" << endl;
						cerr << strerror(errno) << endl;
						break;
					}
					total_sent += sent;
				}
				
				delete[] response;
				delete[] filebuffer;
			}
			
			// On se déconnecte :
			Disconnect(fd);
		}
		else
		{
			// DECONNEXION
			// Message nul ou < 0
			Disconnect(fd);
		}
	}
}

void ActionHTTPClient::Disconnect(int fd)
{
	//cout << "[" << fd << "] Déconnexion du client" << endl;
	
	// On supprime le descipteur de la connexion :
	io.RemoveAction(fd);
	close(fd);
}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

long ActionHTTPClient::readFile(string filename, char*& filebuffer, string& type)
{	
	// On va tenter de récupérer le contenu de ce fichier :
	ifstream fs(filename.c_str());
	if(fs.fail())
	{	
		// Le fichier n'existe pas : on va retourner catalogue.txt :
		type = "text/plain";
		string notfound_file = WWW_DIRECTORY + "/catalogue.txt";
		if(filename == notfound_file)
			return -1;
		else
			return readFile(notfound_file, filebuffer, type);
	}
	else
	{
		// On récupère la taille du fichier :
		fs.seekg(0, ios::end);
		long length = fs.tellg();
		fs.seekg(0, ios::beg);

		// On alloue la mémoire :
		char* buffer = new char[length];

		// On lit le fichier en bloc :
		fs.read(buffer, length);
		fs.close();
		
		filebuffer = buffer;
		return length;
	}
}

