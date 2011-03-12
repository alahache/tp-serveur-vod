/*************************************************************************
                           Action  -  description
                             -------------------
    d�but                : 12/03/2011
    copyright            : (C) 2011 par Arnaud Lahache
*************************************************************************/

//---------- Interface de la classe <Action> (fichier Action.h) ------
#if ! defined ( ACTION_H )
#define ACTION_H

//--------------------------------------------------- Interfaces utilis�es
#include <sys/epoll.h>

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// R�le de la classe <Action>
//	- Interface de handler d'�v�nement d'entr�e / sortie.
//	- Une action est d�clench�e lorsque son descripteur associ� veut
//	  effectuer une op�ration de lecture / �criture. Dans ce cas, la
//	  m�thode execute() est appel�e
//------------------------------------------------------------------------ 

class Action
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- M�thodes publiques
    virtual void execute(epoll_event event) = 0;
    // Mode d'emploi :
    //	<event>	: �venement d�clencheur de l'action
    //	
    //	- M�thode virtuelle pure appel�e lorsqu'un �venement agit sur
    //	  un descripteur associ� � l'action.
    // Contrat :
    //	- M�thode � red�finir

};

#endif // ACTION_H

