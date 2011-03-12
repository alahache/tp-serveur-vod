/*************************************************************************
                           IOControl  -  description
                             -------------------
    d�but                : ...
    copyright            : (C) 2011 par Arnaud Lahache
*************************************************************************/

//---------- R�alisation de la classe <IOControl> (fichier IOControl.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include syst�me
using namespace std;
#include <iostream>
#include <cstdlib>
#include <fcntl.h>

//------------------------------------------------------ Include personnel
#include "IOControl.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- M�thodes publiques
void IOControl::Run()
{
	// On met en marche le gestionnaire :
	running = true;
	
	while(running)
	{
		// On attends qu'un descripteur dans epfd veuille faire une op�raton I/O :
		int nb_ready = epoll_wait(epfd, events, MAX_EPOLL_EVENTS_PER_RUN, EPOLL_RUN_TIMEOUT);
		if (nb_ready < 0)
		{
			cerr << "epoll_wait" << endl;
			exit(EXIT_FAILURE);
		}

		// On parcoure les descripteurs pr�ts :
		for(int i = 0; i < nb_ready; i++)
		{
			int fd = events[i].data.fd;
			
			// On appelle l'action associ�e au descripteur :
			actions[fd]->execute(events[i]);
		}
	}
	
} //----- Fin de Run

void IOControl::Stop()
{
	// On arr�te le gestionnaire :
	running = false;
} //----- Fin de Stop

void IOControl::AddAction(int fd, Action *action, unsigned int events)
{
	// On surveille le descripteur <fd> sur les �venements <events> :
	epoll_event ev;
		ev.events = events;
		ev.data.fd = fd;
	if(epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev) < 0)
	{
		cerr << "Erreur : epoll_ctl ADD fd" << endl;
		exit(EXIT_FAILURE);
	}
	
	// On ajoute l'action <action> au dictionnaire :
	actions[fd] = action;
} //----- Fin de AddAction

void IOControl::RemoveAction(int fd)
{
	if(epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL) < 0)
	{
		cerr << "epoll_ctl DEL client" << endl;
		exit(EXIT_FAILURE);
	}
	
	// On supprime l'action associ�e au descripteur du dictionnaire :
	actions.erase(fd);
} //----- Fin de RemoveAction

//-------------------------------------------- Constructeurs - destructeur


IOControl::IOControl()
{
	// On cr�e le descripteur epfd g�rant l'epoll :
	epfd = epoll_create1(0);
	if(epfd < 0)
	{
		cerr << "Erreur : epoll_create" << endl;
		exit(EXIT_FAILURE);
	}
	
	running = false;
} //----- Fin de IOControl


IOControl::~IOControl()
{
	close(epfd);
} //----- Fin de ~IOControl


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- M�thodes prot�g�es

void setNonBlocking(int fd)
{
	int flags = fcntl(fd, F_GETFL, 0);
	fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

