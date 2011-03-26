/*************************************************************************
                           DataTransfert  -  description
                             -------------------
    début                : Mars 2011
    copyright            : (C) 2011 par Pierre LULÉ
    *************************************************************************/

//---------- Interface de la classe <DataTransfert> (fichier DataTransfert.h) ------
#if ! defined ( DATATRANSFERT_H )
#define DATATRANSFERT_H

//--------------------------------------------------- Interfaces utilisées
#include "Stream.h"

//------------------------------------------------------------- Constantes
const string CRLF = "\r\n";
const unsigned int PIPE_SIZE = 100;

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <DataTransfert>
// 	- Un DataTransfert permet d'échanger un flux avec un ou plusieurs
//	  clients. le flux peut être de différent types, échangé avec un 
//	  protocole particulier.
//	- Cette classe définit une interface pouvant être implantée selon
//	  les différents protocoles désirés.
//------------------------------------------------------------------------

class DataTransfert
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

	virtual void* Begin() = 0;
	// Mode d'emploi :
	//	- Méthode utilisée pour démarrer le transfert
	//	- Redéfinie en fonction du protocole utilisé pour l'échange
	// Contrat :
	//	- Si on veut lancer le transfert dans un nouveau thread, on va
	//	  devoir lancer le thread à partir de la méthode statique
	//	  BeginThread ci-dessous.
	
	static void* BeginThread(void* transfert) { return ((DataTransfert*)transfert)->Begin(); }
	// Mode d'emploi :
	//	- Méthode utilisée comme point de départ à un nouveau Thread

//-------------------------------------------- Constructeurs - destructeur

	DataTransfert(Stream& _stream)
	: stream(_stream), currentImage(0) {};
	// Mode d'emploi :
	// 	<_stream>			: référence vers le flux associé au transfert
	//
	//	- Construit une nouvelle instance de la classe DataTransfert. Chaque
	//	  transfert est associé à un flux.
	//	- L'image courante est initialisée à 0.

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
	virtual void data_connect() = 0;
	virtual void data_send(int imageId) = 0;
	virtual void data_disconnect() = 0;
    
//----------------------------------------------------- Attributs protégés
	Stream& stream;				// Flux associé au transfert
	int currentImage;			// Image courante à envoyer

};

//--------------------------- Autres définitions dépendantes de <DataTransfert>

#endif // DATATRANSFERT_H

