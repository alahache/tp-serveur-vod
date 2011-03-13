/*************************************************************************
                           IOControl  -  description
                             -------------------
    début                : ...
    copyright            : (C) 2011 par Arnaud Lahache
*************************************************************************/

//---------- Réalisation de la classe <IOControl> (fichier IOControl.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstdlib>

//------------------------------------------------------ Include personnel
#include "IOControl.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void IOControl::Run()
{
	if(running) return;

	// On met en marche le gestionnaire :
	running = true;
	
	while(running)
	{
		// On attend qu'un descripteur dans epfd veuille faire une opératon I/O :
		int nb_ready = epoll_wait(epfd, events, MAX_EPOLL_EVENTS_PER_RUN, EPOLL_RUN_TIMEOUT);
		if (nb_ready < 0)
		{
			cerr << "epoll_wait" << endl;
			exit(EXIT_FAILURE);
		}

		// On parcoure les descripteurs prêts :
		for(int i = 0; i < nb_ready; i++)
		{
			int fd = events[i].data.fd;
			
			// On appelle l'action associée au descripteur :
			actions[fd]->Execute(events[i]);
		}
	}
}

void IOControl::Stop()
{
	// On arrête le gestionnaire :
	running = false;
}

void IOControl::AddAction(int fd, Action *action, unsigned int epollEvents)
{
	// On surveille le descripteur <fd> sur les évenements <events> :
	epoll_event ev;
		ev.events = epollEvents;
		ev.data.fd = fd;
	if(epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev) < 0)
	{
		cerr << "Erreur : epoll_ctl ADD fd" << endl;
		exit(EXIT_FAILURE);
	}
	
	// On ajoute l'action <action> au dictionnaire :
	actions[fd] = action;
}

void IOControl::RemoveAction(int fd)
{
	if(epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL) < 0)
	{
		cerr << "epoll_ctl DEL client" << endl;
		exit(EXIT_FAILURE);
	}
	
	// On supprime l'action associée au descripteur du dictionnaire :
	actions.erase(fd);
}

//-------------------------------------------- Constructeurs - destructeur


IOControl::IOControl()
{
	// On crée le descripteur epfd gérant l'epoll :
	epfd = epoll_create1(0);
	if(epfd < 0)
	{
		cerr << "Erreur : epoll_create" << endl;
		exit(EXIT_FAILURE);
	}
	
	running = false;
}


IOControl::~IOControl()
{
	close(epfd);
}


