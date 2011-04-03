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
const unsigned int ALIVE_LIMIT = 60;

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void* DataTransfertUDPPush::Begin()
{
	// On calcule l'intervale en secondes entre 2 images  :ALIVE_LIMIT
	long interval = 1000000/stream->GetFps();
	long sleeping_time;
	timeval timestamp_before, timestamp_after, timestamp_alive;
	char msg[PIPE_SIZE];
	string cmd;

	data_connect();
	bool end	= false;
	bool pause	= false;
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
			}
			else if(cmd == "PAUSE")
			{
				setBlocking(pipefd);
				pause = true;
			}
			else if(cmd == "START")
			{
				setNonBlocking(pipefd);
				gettimeofday(&timestamp_alive, NULL);
				pause = false;
			}
			else if(cmd == "ALIVE")
			{
				gettimeofday(&timestamp_alive, NULL);
			}
		}
		
		if(pause == true || end == true) continue;
		
		// On prends le timestamp avant l'envoi :
		gettimeofday(&timestamp_before, NULL);
		
		// On vérifie avant d'envoyer que le client est encore en vie :
		if((timestamp_before.tv_sec - timestamp_alive.tv_sec) > ALIVE_LIMIT)
		{
			end = true;
		}
		else
		{
			// On envoie l'image courante :
			data_send(++currentImage);
		
			// On prends le timestamp après l'envoi :
			gettimeofday(&timestamp_after, NULL);
		
			// On récupère le temps à attendre avant la prochaine image :
			sleeping_time = interval - ((timestamp_after.tv_sec - timestamp_before.tv_sec)*1000000 + (timestamp_after.tv_usec - timestamp_before.tv_usec));
		
			// on dort :
			if(sleeping_time > 0) usleep(sleeping_time);
		}
		
	}
	data_disconnect();
	
	close(pipefd);
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
