/*************************************************************************
                           ActionCommand  -  description
                             -------------------
    d�but                : ...
    copyright            : (C) 2011 par Arnaud Lahache
*************************************************************************/

//---------- Interface de la classe <ActionCommand> (fichier ActionCommand.h) ------
#if ! defined ( ACTIONCOMMAND_H )
#define ACTIONCOMMAND_H

//--------------------------------------------------- Interfaces utilis�es
#include "Action.h"
#include "IOControl.h"

//------------------------------------------------------------------------ 
// R�le de la classe <ActionCommand>
//	- Action lanc�e lorsque l'utilisateur ex�cute une commande sur
//	  l'entr�e standard.
//------------------------------------------------------------------------ 

class ActionCommand : public Action
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- M�thodes publiques
    void Execute(epoll_event event);
    // Mode d'emploi :
    //	<event>	: �venement d�clencheur de l'action
    //	
    //	- M�thode red�finie appel�e lorsqu'un �venement agit sur
    //	  l'entr�e standard.
    
    static void DisplayPrompt();
    // Mode d'emploi :
    //	- Permet d'afficher proprement un nouveau prompt sur la
    //	  sortie standard.

//-------------------------------------------- Constructeurs - destructeur

    ActionCommand(IOControl& _io)
    	: io(_io) { }
    // Mode d'emploi :
    //	<_io>			: Gestionnaire d'e/s
    //
    //	- Contructeur de ActionCommand

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- M�thodes prot�g�es

//----------------------------------------------------- Attributs prot�g�s
	IOControl& io;

};

#endif // ACTIONCOMMAND_H

