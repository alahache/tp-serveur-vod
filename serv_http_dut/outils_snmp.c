#include "commun.h"

void nom_to_ip(char *serveur, char *res, char *adr) {
	//Recuperer l'adresse ip :
	struct hostent *addr;
	addr=gethostbyname(serveur);
	if(addr) {
		//Le serveur existe
		struct in_addr si;
		memcpy(&si.s_addr, *(addr->h_addr_list), 4);
		strcpy(res, inet_ntoa(si));
		strcpy(adr, addr->h_name);
	} else {
		//Le serveur n'existe pas. :
		strcpy(res, "noip");
	}
}

void mesg_snmp(int s, char *addr_ip, char *oidcode, char *res) {

		//Requete SNMP :
		
		//construction du message SNMP :
		char snmp_reqdesc[TBUF];
		int snmp_reqdesc_len=build_snmp_req(snmp_reqdesc, oidcode);
		
		//construction du destinataire :
		struct sockaddr_in dest;
			dest.sin_family=AF_INET;
			dest.sin_port=htons(161);
			dest.sin_addr.s_addr=inet_addr(addr_ip);

		//envoi du message :
		int ressend;
		ressend=sendto(s, snmp_reqdesc, snmp_reqdesc_len, 0, (struct sockaddr *)&dest, sizeof(dest));
		if(ressend<0) {
			perror("sendto");
			exit(2);
		}

		//reception de la reponse :
		char rep[TBUF];
		int resrep;
		int explen;
		struct sockaddr_in exp;
		explen=sizeof(exp);
		
		// Avant tout, on empeche le programme d'attendre le message snmp a l'infini :
		fd_set fdset; // On cree un fd_set
		FD_ZERO(&fdset);  // On l'initialise a 0
		FD_SET(s,&fdset); // Ainsi que le socket s
		
		// On estime qu'il faut au plus 1 seconde pour que le serveur reponde :
		struct timeval tv;
			tv.tv_sec=1;
			tv.tv_usec=0;
		
		int reponse = select(s+1, &fdset, NULL, NULL, &tv);
		if(reponse) {
			// Une reponse a bien ete recue
			resrep=recvfrom(s, rep, TBUF, 0, (struct sockaddr *)&exp, &explen);
			if(resrep<0) {
				perror("recvfrom");
				exit(3);
			}
			
			char rep_decodee[TBUF];

			// decodage de la reponse :
			int lg = snmp_decode_rep(rep, resrep, rep_decodee);
			//rep_decodee[lg]='\0';
			
			strcpy(res, rep_decodee);
		} else {
			// Le message n'a pas ete recu.
			strcpy(res, "norep");
		}

		
}
