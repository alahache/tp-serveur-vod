/*************************************************************************
                           DataTransfertMCASTPush  -  description
                             -------------------
    début                : ...
    copyright            : (C) 2011 par Arnaud Lahache
*************************************************************************/

//---------- Interface de la classe <DataTransfertMCASTPush> (fichier DataTransfertMCASTPush.h) ------
#if ! defined ( DATATRANSFERTMCASTPUSH_H )
#define DATATRANSFERTMCASTPUSH_H

//--------------------------------------------------- Interfaces utilisées
#include "DataTransfertUDP.h"

//------------------------------------------------------------------------ 
// Rôle de la classe <DataTransfertMCASTPush>
//	- Implémentation de DataTransfertUDP pour MCAST
//	- Réutilisation des méthodes UDP pour envoyer un message avec le
//	  protocole MCAST_PUSH
//------------------------------------------------------------------------ 

class DataTransfertMCASTPush : public DataTransfertUDP
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

	void* Begin();

//-------------------------------------------- Constructeurs - destructeur

    DataTransfertMCASTPush(Stream* _stream, in_addr _groupAddress, int _groupPort, unsigned int _fragmentSize, int _pipefd)
    	: DataTransfertUDP(_stream, _groupAddress, _groupPort, _fragmentSize), pipefd(_pipefd) {}
    // Mode d'emploi :
	// 	<_stream>			: référence vers le flux associé au transfert
	// 	<_groupAddress>		: addresse du groupe
	// 	<_groupPort>		: port d'écoute du groupe
	// 	<_fragmentSize>		: taille des fragments de données envoyés
	// 	<_pipefd>			: descripeur du pipe en lecture
	//
	//	- Construit une nouvelle instance de la classe DataTransfertMCASTPush.

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
	int pipefd;					// Descripteur de lecture pour le pipe

};

//--------------------------- Autres définitions dépendantes de <DataTransfertMCASTPush>

#endif // DATATRANSFERTMCASTPUSH_H

