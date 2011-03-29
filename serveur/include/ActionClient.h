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
#include <string>
#include <map>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>			// in_addr
#include <sys/socket.h>
#include <pthread.h>

#include "Action.h"
#include "ActionConnection.h"
#include "IOControl.h"
#include "Stream.h"
#include "DataTransfert.h"

//------------------------------------------------------------- Constantes
const unsigned int MSG_BUFFER_SIZE = 768;

//------------------------------------------------------------------ Types 
struct Client
{
	// Adresse :
	in_addr clientAddress;			// Adresse du client
	unsigned int clientPort;		// Port d'écoute du client
	
	// Transfert :
	bool transfertStarted;			// Vrai si le transfert a commencé
	DataTransfert *transfert;		// Transfert du flux
	pthread_t transfertThread;		// Thread utilisé lors du transfert
	int pipefd;						// Descripteur en écriture du pipe
	unsigned long fragmentSize;		// Taille du fragment pour un transfert UDP
	
	Client() : transfertStarted(false) { }
};

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
    
	void Disconnect(std::string client_addr);
	// Mode d'emploi :
	//	- Permet de déconnecter un client du serveur.
	
	void SetTCPClient(sockaddr_in _tcpClientAddr, ActionConnection* _connection);
	// Mode d'emploi :
	//	- Permet de d'initaliser le client TCP

//-------------------------------------------- Constructeurs - destructeur

	ActionClient(IOControl& _io, Stream* _stream, int _fd)
		: Action(_io), stream(_stream), fd(_fd) { }
    // Mode d'emploi :
    //	<_io>				: Gestionnaire d'e/s
    //	<_stream>			: Flux associé à la connexion
    //	<_fd>				: Descripteur de la connexion du client
    //
    //	- Construit une nouvelle instance de ActionClient.

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées
	std::string addrToKey(sockaddr_in addr);
	void setNonBlocking(int fd);

//----------------------------------------------------- Attributs protégés
	// Flux :
	Stream* stream;							// Flux associé à la connexion
	int videoId;							// ID de la vidéo à envoyer

	// Connexion :
	int fd;									// socket associée à la connexion
	std::map<std::string, Client> clients;	// Liste des clients connectés à la socket
	
	// Connexion TCP :
	ActionConnection* connection;			// Action de connexion des clients
	std::string tcp_client;					// Adresse du client TCP
};

#endif // ACTIONCLIENT_H

