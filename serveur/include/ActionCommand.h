/*************************************************************************
                           ActionCommand  -  description
                             -------------------
    début                : ...
    copyright            : (C) 2011 par Arnaud Lahache
*************************************************************************/

//---------- Interface de la classe <ActionCommand> (fichier ActionCommand.h) ------
#if ! defined ( ACTIONCOMMAND_H )
#define ACTIONCOMMAND_H

//--------------------------------------------------- Interfaces utilisées
#include "Action.h"
#include "IOControl.h"

//------------------------------------------------------------------------ 
// Rôle de la classe <ActionCommand>
//	- Action lancée lorsque l'utilisateur exécute une commande sur
//	  l'entrée standard.
//------------------------------------------------------------------------ 

class ActionCommand : public Action
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void Execute(epoll_event event);
    // Mode d'emploi :
    //	<event>	: Évenement déclencheur de l'action
    //	
    //	- Méthode redéfinie appelée lorsqu'un évenement agit sur
    //	  l'entrée standard.
    
    static void DisplayPrompt();
    // Mode d'emploi :
    //	- Permet d'afficher proprement un nouveau prompt sur la
    //	  sortie standard.

//-------------------------------------------- Constructeurs - destructeur

    ActionCommand(IOControl& _io)
    	: Action(_io) { }
    // Mode d'emploi :
    //	<_io>			: Gestionnaire d'e/s
    //
    //	- Contructeur de ActionCommand

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

};

#endif // ACTIONCOMMAND_H

