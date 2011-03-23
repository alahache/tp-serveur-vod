/*************************************************************************
                           ActionClient  -  description
                             -------------------
    début                : ...
    copyright            : (C) 2011 par Arnaud Lahache
*************************************************************************/

//---------- Interface de la classe <ActionClient> (fichier ActionClient.h) ------
#if ! defined ( ACTIONCLIENT_H )
#define ACTIONCLIENT_H

//--------------------------------------------------- Interfaces utilisées
#include <netinet/in.h>
#include <arpa/inet.h>			// sockaddr_in

#include "Action.h"
#include "ActionConnection.h"
#include "IOControl.h"
#include "Stream.h"

//------------------------------------------------------------- Constantes
const unsigned int BUFFER_SIZE = 768;

//------------------------------------------------------------------------ 
// Rôle de la classe <ActionClient>
//	- Action lancée lorsqu'un client execute une requête d'e/s
//------------------------------------------------------------------------ 

class ActionClient : public Action
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void Execute(epoll_event event);
    // Mode d'emploi :
    //	<event>	: Évenement déclencheur de l'action
    //	
    //	- Méthode redéfinie appelée lorsqu'un client effectue une
    //	  opération de lecture / écriture sur le descripteur <fd>.
    
    void Disconnect();
	// Mode d'emploi :
	//	- Permet de déconnecter un client du serveur.

//-------------------------------------------- Constructeurs - destructeur

    ActionClient(IOControl& _io, ActionConnection& _connection, Stream& _stream, int _fd, in_addr _clientAddress)
    	: Action(_io), connection(_connection), stream(_stream), fd(_fd), clientAddress(_clientAddress), transfertStarted(false) {}
    // Mode d'emploi :
    //	<_io>			: Gestionnaire d'e/s
    //	<_connection>	: Action gérant la connexion des clients
    //	<_stream>		: Flux associé à la connexion
    //	<_fd>			: Descripteur de la connexion du client
    //
    //	- Construit une nouvelle instance de ActionClient.

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
	bool transfertStarted;			// Vrai si le transfert a commencé
	ActionConnection& connection;	// Action de connexion des clients
	Stream& stream;					// Flux associé à la connexion
	int fd;							// Descripteur de la connexion du client
	int videoId;					// ID de la vidéo à envoyer
	unsigned long fragmentSize;		// Taille du fragment pour un transfert UDP
	unsigned int listenPort;		// Port utilisé
	in_addr clientAddress;			// Adresse du client

};

#endif // ACTIONCLIENT_H

