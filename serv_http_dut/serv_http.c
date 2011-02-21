#include "commun.h"

// ------------------------------------------------------
// Initie la liste des serveurs avec le fichier de configuration
// ------------------------------------------------------
void init_liste() {
	char *fich_conf="snmpweb.conf";
	char contenu[TMESS];
	lire_fichier(fich_conf, contenu);
	
	// Nous allons lire le contenu du fichier ligne par ligne :
	char *suivant;
	suivant=strtok(contenu, "\n");
	while(suivant != NULL) {
		// On etudie la ligne courante :
		char *delim=strchr(suivant, ':');
		char *img=strdup(delim+1);
		*delim='\0';
		char *pseudo=strdup(suivant);
		
		// On ajoute le serveur a la liste :
		liste_serveurs[nb_serveurs].nom=strdup(pseudo);
		liste_serveurs[nb_serveurs].image=strdup(img);
		nb_serveurs++;
		
		// Puis on passe a la ligne suivante :
		suivant=strtok(NULL, "\n");
	}
}

// ------------------------------------------------------
// Fonction qui ajoute un nouveau serveur a la liste. Renvoie egalement sa position dans cette liste.
// ------------------------------------------------------
int maj_liste(char *ip, char *nom, char *addr) {

	int etat;
	char sysdesc[TBUF];
	char sysnb[TBUF];
	
	etat=1; // On initialise l'etat du serveur Ã  1.

	if(strcmp(ip, "noip")) {
		etat=9; // Il y a une reponse DNS.
		
		// Creation d'un nouveau socket UDP :

		int s_udp;
		s_udp=socket(PF_INET, SOCK_DGRAM, 0);
		
		// On verifie que le socket est bien ouvert :
		if(s_udp<0) {
			perror("socket");
			exit(1);
		}
	
		// description :
		char *sysoid=".1.3.6.1.2.1.1.1.0";
		mesg_snmp(s_udp, ip, sysoid, sysdesc);
		//printf("systeme d'exploitation : %s\n", sysdesc);

		if(strcmp(sysdesc, "norep")) {
			etat=4; // Il y a une reponse pour Desc.

			// nombre d'utilisateurs :
			char *sysnboid=".1.3.6.1.2.1.25.1.5.0";
			mesg_snmp(s_udp, ip, sysnboid, sysnb);
			//printf("nombre d'utilisateurs : %s\n", sysnb);
			
			if(strcmp(sysnb, "norep")) {
				etat=6; // Il y a egalement une reponse pour Users.
			} else {
				strcpy(sysnb,"");
			}
			
		} else {
			strcpy(sysdesc,"");
			strcpy(sysnb,"");
		}
	
		close(s_udp);

		// Fin du transfert UDP

	} else {
		strcpy(ip,"");
		strcpy(addr,"");
		strcpy(sysdesc,"");
		strcpy(sysnb,"");
	}
	
	// On essaye de trouver la position du serveur s'il est deja dans la liste.
	// Dans le cas contraire, pos = nb_serveurs
	int pos=get_pos(nom);

	// Maintenant, on ajoute un nouvel element (ou on en modifie un) au tableau liste_serveurs :
	liste_serveurs[pos].nom=strdup(nom);
	liste_serveurs[pos].etat=etat;
	liste_serveurs[pos].ip=strdup(ip);
	liste_serveurs[pos].addr=strdup(addr);
	liste_serveurs[pos].sysdesc=strdup(sysdesc);
	liste_serveurs[pos].nbuser=strdup(sysnb);
	
	// Dans le cas où le serveur n'est pas initialisé par snmpweb.conf :
	if(!liste_serveurs[pos].image) liste_serveurs[pos].image=strdup("img3.gif");

	if(pos==nb_serveurs) nb_serveurs=nb_serveurs+1;

	return pos;

}

// ------------------------------------------------------
// Retourne la position du serveur dont le nom est 'nom'.
// ------------------------------------------------------
int get_pos(char *nom) {
	int res;
	for(res=0; res<nb_serveurs; res=res+1) {
		if(!strcmp(liste_serveurs[res].nom, nom)) return res;
	}
	return nb_serveurs;
}

// ------------------------------------------------------
// Verifie si 'nom' est dans la liste des serveurs
// ------------------------------------------------------
int existe(char *nom) {
	int res;
	for(res=0; res<nb_serveurs; res=res+1) {
		if(!strcmp(liste_serveurs[res].nom, nom)) return 1;
	}
	return 0;
}

// ------------------------------------------------------
// Affiche sur la sortie standard la liste des serveurs
// ------------------------------------------------------
void aff_liste_serveurs() {
	int i;
	for(i=0; i<nb_serveurs; i=i+1) {
		printf(" # [ %d - %s - %s - %s - %s - %s ]\n", liste_serveurs[i].etat, liste_serveurs[i].nom, liste_serveurs[i].addr, liste_serveurs[i].ip, liste_serveurs[i].sysdesc, liste_serveurs[i].nbuser);
	}
}

// ------------------------------------------------------
// Programme principal
// ------------------------------------------------------
main(int argc, char *argv[]) {

	// On verifie le nombre d'arguments :
	if(argc == 1) {
		printf("En parametre, passez le port du service desire.\n");
		exit(1);
	}
	
	// On initialise la liste des serveurs :
	nb_serveurs=0;
	init_liste();
	
	// Creation d'un prompteur :
	printf("serveur> ");
	fflush(stdout);

	// Creation interface de communication TCP :
	int s=socket(PF_INET, SOCK_STREAM, 0);
	if(s<0) {
		perror("socket");
		exit(1);
	}
	
	// On contourne le probleme de l'adresse et du port deja utilise :
	int opt=1;
	setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	
	// Attacher le port du service :
	struct sockaddr_in nom;
		nom.sin_family = AF_INET;
		nom.sin_addr.s_addr = htonl(INADDR_ANY);
		nom.sin_port = htons(atoi(argv[1]));

	if(bind(s, (struct sockaddr *) &nom, sizeof(nom)) < 0) {
		perror("bind");
		exit(1);
	}
	
	// Met en attente les utilisateurs (TNBMAX au maximum) :
	if(listen(s, TNBMAX) < 0) {
		perror("listen");
		exit(2);
	}

	while(1) {
		
		// On cree un fd_set :
		fd_set fdset;
		FD_ZERO(&fdset);  // On l'initialise a 0
		FD_SET(0,&fdset); // On lui demande de surveiller l'entree standard
		FD_SET(s,&fdset); // Ainsi que le socket s
		
		int res = select(s+1,&fdset,NULL,NULL,NULL);
		if (res) {
		
			// C'est le socket tcp s qui interargit :
			if (FD_ISSET(s,&fdset)) {

				// Accepter un client :
				int ns;
				struct sockaddr_in client;
				int client_len = sizeof(client);
				ns = accept(s, (struct sockaddr *)&client, &client_len);
				//printf("Nouveau client !\n");
				
				// Recuperer le GET, c'est a dire le parametre de la page :
				char buff[TBUF];
				if(read(ns, buff, TBUF) < 0) {
					perror("read");
					exit(3);
				}
				
				char get_res[64];
				sscanf(buff, "GET /%s ", get_res);

				// Selon le resultat du GET, on renvoie differentes informations :
				if(!strcmp(get_res, "HTTP/1.1")) {
					
					// Nous devons renvoyer la liste des serveurs au client
					char message[TMESS];
					serveurs_to_html(message);

					if(write(ns, message, strlen(message)) < 0) {
						perror("write");
						exit(4);
					}
					
				} else {
					
					//On recupere l'adresse IP et l'adresse http du serveur 'get_res' :
					char addr_ip[512];
					char addr_serveur[512];
					nom_to_ip(get_res, addr_ip, addr_serveur);
					
					if(addr_ip) {
					
						if(!existe(get_res) && !strcmp(addr_ip, "noip")) {
							//Ce n'est pas un serveur.

							//On suppose qu'il s'agit d'un fichier :
							char message[TFICH];
							int lg=lire_fichier(get_res, message);
							
							if(write(ns, message, lg) < 0) {
								perror("write");
								exit(4);
							}
						} else {
							
							// Le serveur existe bien.

							// On l'ajoute donc a notre liste :
							int pos=maj_liste(addr_ip, get_res, addr_serveur);
							
							//Construction du message a envoyer :
							char message[TFICH];
							serveurs_to_html(message);

							if(write(ns, message, strlen(message)) < 0) {
								perror("write");
								exit(4);
							}
						}
					
					}
					
				}

				// On referme le socket
				close(ns);

			} // fd_isset(s)
			
			// Maintenant, si l'on a tape une commande au clavier :
			if(FD_ISSET(0,&fdset)) {
				
				// On stocke les informations saisies au clavier
				char cmde[128];
				scanf("%s", cmde);
				
				// Maintenant on essaye de reperer la commande ecrite au clavier :
				if(strstr(cmde, "list")) {
					// Liste tous les serveurs enregistres
					printf("Liste des serveurs :\n");
					aff_liste_serveurs();
					
				} else if (strstr(cmde, "exit")) {
					// Quitte le serveur
					printf("Arret du serveur...\n");
					close(s);
					exit(0);
					
				} else {
					// Commande non reconnue
					printf("Cette commande n'existe pas.\n");
					
				}
				
				// On recree le prompteur :
				printf("serveur> ");
			    fflush(stdout);
			} // fd_isset(0)
			
		} // select
		
	} // while(1)
}
