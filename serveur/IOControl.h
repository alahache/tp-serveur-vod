/*************************************************************************
                           IOControl  -  description
                             -------------------
    d�but                : 11/03/2011
    copyright            : (C) 2011 par Arnaud Lahache
*************************************************************************/

//---------- Interface de la classe <IOControl> (fichier IOControl.h) ------
#if ! defined ( IOCONTROL_H )
#define IOCONTROL_H

//--------------------------------------------------- Interfaces utilis�es
#include <map>
#include <sys/epoll.h>
#include "Action.h"

//------------------------------------------------------------- Constantes
const unsigned int MAX_EPOLL_EVENTS_PER_RUN = 100;
const unsigned int EPOLL_RUN_TIMEOUT = 5;

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------ 
// R�le de la classe <IOControl>
//	- Contr�le les entr�es sorties sur un ensemble de descripteurs
//	  li�s � une instance de la classe
//	- Chaque descripteur ajout�e � l'instance permet de lancer une
//	  Action diff�rente selon l'�venement associ� au descripteur :
//	  demande de lecture, d'�criture, connexion...
//------------------------------------------------------------------------ 

class IOControl
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- M�thodes publiques

    void Run();
    // Mode d'emploi :
    //	- Lance ou relance le contr�le des entr�es sorties. Cet appel
    //	  commence une boucle infinie.
    //	- Le retour de la fonction n'est assur� qu'apr�s un appel � la
    //	  fonction Stop() par exemple � l'int�rieur d'une Action
    // Contrat :
    //	- Au moins un descripteur a �t� ajout� � l'instance
    //	- Une t�che (processus ou thread) sp�cifique devra se
    //	  consacrer uniquement � l'ex�cution de cette m�thode une fois
    //	  qu'elle sera appel�e.
    
    void Stop();
    // Mode d'emploi :
    //	- Arr�te le contr�le des entr�es sorties.
    
    void AddAction(int fd, Action *action, unsigned int events);
    // Mode d'emploi :
    //	<fd>		: Descripteur � surveiller en entr�e / sortie
    //	<action>	: Action associ�e au descripteur
    //	<events>	: �venements � surveiller
    //
    //	- Ajoute une action associ�e � un descripteur de fichier au
    //	gestionnaire.
    //	- L'action sera appel�e dans le cas o� l'un des �venements
    //	  dans <events> se d�clenche.
    
    void RemoveAction(int fd);
    // Mode d'emploi :
    //	<fd>		: Descripteur � supprimer
    //
    //	- Supprime le descripteur de la liste des descripteurs � surveiller
    //	  du gestionnaire d'entr�es / sorties

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
//----------------------------------------------------- M�thodes prot�g�es

	void setNonBlocking(int fd);
	// Mode d'emploi :
	//	<fd>	: descripteur cible
	//
	//	- Permet de modifier un descripteur afin de le rendre non
	//	  bloquant.

//----------------------------------------------------- Attributs prot�g�s
	int epfd;						// epoll file descriptor
	bool running;					// vrai si le gestionnaire est en marche
	std::map<int, Action*> actions;	// dictionnaire des actions
	epoll_event events[MAX_EPOLL_EVENTS_PER_RUN];

};

#endif // IOCONTROL_H

