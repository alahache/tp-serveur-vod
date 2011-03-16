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
#include <sys/socket.h>
#include <netinet/in.h>
//#include "Stream.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
typedef struct sockaddr_in {
    uint8_t         sin_len;       /* longueur totale      */
    sa_family_t     sin_family;    /* famille : AF_INET     */
    in_port_t       sin_port;      /* le numéro de port    */
    struct in_addr  sin_addr;      /* l'adresse internet   */
    unsigned char   sin_zero[8];   /* un champ de 8 zéros  */
};
//------------------------------------------------------------------------
// Rôle de la classe <DataTransfert>
// Interface d'un thread gérant la connexion avec un client.
//
//------------------------------------------------------------------------

class DataTransfert
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual void* Run( void* args) = 0;
    // Routine d'execution

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

    //DataTransfert ( Stream& _stream, sockaddr_in _address, int _port, int& _pipe) :
    //stream(_stream), address(_address), port(_port), pipe(_pipe){ }
    // <stream> : référence vers le flux associé au client
    // <address> : addresse du client
    // <port> : port de communication du client

    DataTransfert ( sockaddr_in _address, int _port) :
    address(_address), port(_port){ }
    // TEST TODO a supprimer

    virtual ~DataTransfert ( );
    // Mode d'emploi : Détruit l'objet et ferme la connection
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

//Stream& stream;
sockadrr_in address;
int port;
int& pipe;
int sock;

};

//--------------------------- Autres définitions dépendantes de <DataTransfert>

#endif // DATATRANSFERT_H

