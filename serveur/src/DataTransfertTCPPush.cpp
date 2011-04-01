/*************************************************************************
                           DataTransfertTCPPush  -  description
                             -------------------
    début                : ...
    copyright            : (C) 2011 par Arnaud Lahache
*************************************************************************/

//---------- Réalisation de la classe <DataTransfertTCPPush> (fichier DataTransfertTCPPush.cpp) -------

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
#include "DataTransfertTCPPush.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void* DataTransfertTCPPush::Begin()
{
	// On calcule l'intervale en secondes entre 2 images  :
	unsigned int interval = 1000000/stream.GetFps();
	long sleeping_time;
	timeval timestamp_before;
	timeval timestamp_after;
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
		gettimeofday(&timestamp_before, NULL);
		
		// On envoie l'image courante :
		data_send(++currentImage);
		
		// On prends le timestamp après l'envoi :
		gettimeofday(&timestamp_after, NULL);
		
		// On récupère le temps à attendre avant la prochaine image :
		sleeping_time = interval - ((timestamp_after.tv_sec - timestamp_before.tv_sec)*1000000 + (timestamp_after.tv_usec - timestamp_before.tv_usec));
		
		// on dort :
		if(sleeping_time > 0) usleep(sleeping_time);
		
	}
	data_disconnect();
	return 0;
}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

void DataTransfertTCPPush::setNonBlocking(int fd)
{
	int flags = fcntl(fd, F_GETFL, 0);
	fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

void DataTransfertTCPPush::setBlocking(int fd)
{
	int flags = fcntl(fd, F_GETFL, 0);
	fcntl(fd, F_SETFL, flags & ~O_NONBLOCK);
}
