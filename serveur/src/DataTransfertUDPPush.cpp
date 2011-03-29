/*************************************************************************
                           DataTransfertUDPPush  -  description
                             -------------------
    début                : ...
    copyright            : (C) 2011 par Arnaud Lahache
*************************************************************************/

//---------- Réalisation de la classe <DataTransfertUDPPush> (fichier DataTransfertUDPPush.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstdlib>
#include <sys/time.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

//------------------------------------------------------ Include personnel
#include "DataTransfertUDPPush.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void* DataTransfertUDPPush::Begin()
{
	// On calcule l'intervale en secondes entre 2 images  :
	unsigned int interval = 1000000/stream.GetFps();
	unsigned int sleeping_time;
	unsigned int timestamp_before;
	unsigned int timestamp_after;
	timeval time;
	char msg[PIPE_SIZE];
	string cmd;

	data_connect();
	bool end = false;
	while (!end)
	{
		// On va lire un message dans le pipe :
		if(read(pipefd, msg, PIPE_SIZE) == -1)
		{
			if(errno != EAGAIN)
			{
				cerr << "Erreur : read pipe" << endl;
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			cmd = msg;
			if (cmd == "END")
			{
				end = true;
				continue;
			}
			else if(cmd == "PAUSE")
			{
				setBlocking(pipefd);
				continue;
			}
			else if(cmd == "START")
			{
				setNonBlocking(pipefd);
			}
		}
		
		// On prends le timestamp avant l'envoi :
		gettimeofday(&time, NULL);
		timestamp_before = time.tv_usec;
		
		// On envoie l'image courante :
		data_send(++currentImage);
		
		// On prends le timestamp après l'envoi :
		gettimeofday(&time, NULL);
		timestamp_after = time.tv_usec;
		
		// On récupère le temps à attendre avant la prochaine image :
		sleeping_time = interval - (timestamp_after - timestamp_before);
		
		// on dort :
		usleep(sleeping_time);
		
	}
	data_disconnect();
	return 0;
}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

void DataTransfertUDPPush::setNonBlocking(int fd)
{
	int flags = fcntl(fd, F_GETFL, 0);
	fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

void DataTransfertUDPPush::setBlocking(int fd)
{
	int flags = fcntl(fd, F_GETFL, 0);
	fcntl(fd, F_SETFL, flags & ~O_NONBLOCK);
}
