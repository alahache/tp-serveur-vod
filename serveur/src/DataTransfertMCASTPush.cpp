/*************************************************************************
                           DataTransfertMCASTPush  -  description
                             -------------------
    début                : ...
    copyright            : (C) 2011 par Arnaud Lahache
*************************************************************************/

//---------- Réalisation de la classe <DataTransfertMCASTPush> (fichier DataTransfertMCASTPush.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstdlib>
#include <sys/time.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>

//------------------------------------------------------ Include personnel
#include "DataTransfertMCASTPush.h"

//----------------------------------------------------- Méthodes publiques

void* DataTransfertMCASTPush::Begin()
{
	// On calcule l'intervale en secondes entre 2 images  :
	long interval = 1000000/stream->GetFps();
	long sleeping_time;
	timeval timestamp_before, timestamp_after;
	char msg[PIPE_SIZE];
	string cmd;

	data_connect();
	unsigned char ttl = 1;
    setsockopt(sock, IPPROTO_IP, IP_MULTICAST_TTL, &ttl, sizeof(ttl));
	
	bool end	= false;
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
		}
		
		if(end == true) continue;
		
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
	
	close(pipefd);
	return 0;
}

