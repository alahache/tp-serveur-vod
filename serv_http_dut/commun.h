#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <signal.h>
#include <sys/socket.h>
#include <fcntl.h>
#define TBUF 1024
#define TMESS 10000
#define TFICH 50000
#define TNBMAX 20

// Methodes communes :
void mesg_snmp(int s, char *addr_ip, char *oidcode, char *res);
void nom_to_ip(char *serveur, char *res, char *adr);
void serveurs_to_html(char *messg);
int lire_fichier(char *fichier, char* contenu);

// Structure contenant un serveur :
struct serveur {
	char *nom;
	int etat;
	char *ip;
	char *addr;
	char *sysdesc;
	char *nbuser;
	char *image;
};

// Tableau de serveurs :
struct serveur liste_serveurs[20];

// Nombre de serveurs :
int nb_serveurs;

