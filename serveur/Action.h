/*************************************************************************
                           Action  -  description
                             -------------------
    début                : 12/03/2011
    copyright            : (C) 2011 par Arnaud Lahache
*************************************************************************/

//---------- Interface de la classe <Action> (fichier Action.h) ------
#if ! defined ( ACTION_H )
#define ACTION_H

//--------------------------------------------------- Interfaces utilisées
#include <sys/epoll.h>

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Rôle de la classe <Action>
//	- Interface de handler d'évènement d'entrée / sortie.
//	- Une action est déclenchée lorsque son descripteur associé veut
//	  effectuer une opération de lecture / écriture. Dans ce cas, la
//	  méthode execute() est appelée
//------------------------------------------------------------------------ 

class Action
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    virtual void execute(epoll_event event) = 0;
    // Mode d'emploi :
    //	<event>	: Évenement déclencheur de l'action
    //	
    //	- Méthode virtuelle pure appelée lorsqu'un évenement agit sur
    //	  un descripteur associé à l'action.
    // Contrat :
    //	- Méthode à redéfinir

};

#endif // ACTION_H

