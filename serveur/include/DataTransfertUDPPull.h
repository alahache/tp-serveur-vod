/*************************************************************************
                           DataTransfertUDPPull  -  description
                             -------------------
    début                : ...
    copyright            : (C) 2011 par Arnaud Lahache
*************************************************************************/

//---------- Interface de la classe <DataTransfertUDPPull> (fichier DataTransfertUDPPull.h) ------
#if ! defined ( DATATRANSFERTUDPPULL_H )
#define DATATRANSFERTUDPPULL_H

//--------------------------------------------------- Interfaces utilisées
#include "DataTransfertUDP.h"

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Rôle de la classe <DataTransfertUDPPull>
//	- Implémentation de DataTransfertUDP pour le protocole Pull
//	- Les images sont envoyées au client seulement lorsqu'on envoie
//	  un numéro au pipe <pipefd>, qui représente la position de l'image
//	  dans le flux.
//------------------------------------------------------------------------ 

class DataTransfertUDPPull : public DataTransfertUDP
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
	
	void* Begin();

//-------------------------------------------- Constructeurs - destructeur

    DataTransfertUDPPull(Stream& _stream, in_addr _clientAddress, int _clientPort, unsigned int _fragmentSize, int _pipefd)
    	: DataTransfertUDP(_stream, _clientAddress, _clientPort, _fragmentSize), pipefd(_pipefd) {}
	// Mode d'emploi :
	// 	<_stream>			: référence vers le flux associé au transfert
	// 	<_clientAddress>	: addresse du client
	// 	<_clientPort>		: port d'écoute du client
	// 	<_fragmentSize>		: taille des fragments de données envoyés
	// 	<_pipefd>			: descripeur du pipe en lecture
	//
	//	- Construit une nouvelle instance de la classe DataTransfertUDP.

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
	int pipefd;					// Descripteur du pipe en lecture

};

//--------------------------- Autres définitions dépendantes de <DataTransfertUDPPull>

#endif // DATATRANSFERTUDPPULL_H

