/*************************************************************************
                           IOControl  -  description
                             -------------------
    début                : 11/03/2011
    copyright            : (C) 2011 par Arnaud Lahache
*************************************************************************/

//---------- Interface de la classe <IOControl> (fichier IOControl.h) ------
#if ! defined ( IOCONTROL_H )
#define IOCONTROL_H

//--------------------------------------------------- Interfaces utilisées
#include <map>
#include <sys/epoll.h>
#include "Action.h"

//------------------------------------------------------------- Constantes
const unsigned int MAX_EPOLL_EVENTS_PER_RUN = 10;
const int EPOLL_RUN_TIMEOUT = -1;

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------ 
// Rôle de la classe <IOControl>
//	- Contrôle les entrées sorties sur un ensemble de descripteurs
//	  liés à une instance de la classe
//	- Chaque descripteur ajoutée à l'instance permet de lancer une
//	  Action différente selon l'évenement associé au descripteur :
//	  demande de lecture, d'écriture, connexion...
//------------------------------------------------------------------------ 

class IOControl
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    void Run();
    // Mode d'emploi :
    //	- Lance ou relance le contrôle des entrées sorties. Cet appel
    //	  commence une boucle infinie.
    //	- Le retour de la fonction n'est assuré qu'après un appel à la
    //	  fonction Stop() par exemple à l'intérieur d'une Action
    // Contrat :
    //	- Au moins un descripteur a été ajouté à l'instance
    //	- Une tâche (processus ou thread) spécifique devra se
    //	  consacrer uniquement à l'exécution de cette méthode une fois
    //	  qu'elle sera appelée.
    
    void Stop();
    // Mode d'emploi :
    //	- Arrête le contrôle des entrées sorties.
    
    void AddAction(int fd, Action *action, unsigned int events);
    // Mode d'emploi :
    //	<fd>		: Descripteur à surveiller en entrée / sortie
    //	<action>	: Action associée au descripteur
    //	<events>	: évenements à surveiller
    //
    //	- Ajoute une action associée à un descripteur de fichier au
    //	gestionnaire.
    //	- L'action sera appelée dans le cas où l'un des évenements
    //	  dans <events> se déclenche.
    
    void RemoveAction(int fd);
    // Mode d'emploi :
    //	<fd>		: Descripteur à supprimer
    //
    //	- Supprime le descripteur de la liste des descripteurs à surveiller
    //	  du gestionnaire d'entrées / sorties

//-------------------------------------------- Constructeurs - destructeur

    IOControl();
    // Mode d'emploi :
    //	- Construit une nouvelle instance de la classe IOControl et
    //	  initialise directement la gestion des descripteurs.

    virtual ~IOControl();
    // Mode d'emploi :
    //	- Destructeur de la classe IOControl

//------------------------------------------------------------------ PRIVE 

protected:

//----------------------------------------------------- Attributs protégés
	int epfd;						// epoll file descriptor
	bool running;					// vrai si le gestionnaire est en marche
	std::map<int, Action*> actions;	// dictionnaire des actions
	epoll_event events[MAX_EPOLL_EVENTS_PER_RUN];

};

#endif // IOCONTROL_H

