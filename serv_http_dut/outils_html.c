#include "commun.h"

// ------------------------------------------------------
// Lit le contenu d'un fichier, retourne la taille.
// ------------------------------------------------------
int lire_fichier(char *fichier, char* res) {
	char *contenu;
	int taille;

	int f;
	f=open(fichier, O_RDONLY);

	if(f<0) {
		// Erreur 404 :
		contenu=strdup("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">\n<html>\n<head>\n<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\">\n<title>Erreur 404 !</title>\n</head>\n<body>\n<h1>Page non trouv&eacute;e !</h1>\n<img src=\"images/404.gif\" alt=\"erreur 404\" />\n</body>\n</html>");
		taille=strlen(contenu);
	} else {
		// Recuperer la taille du fichier :
		taille=lseek(f, 0, SEEK_END);
		
		// On se repositionne au debut du fichier :
		lseek(f, 0, SEEK_SET);
		
		// On lit le fichier :
		contenu=(char*) malloc((sizeof(char) * taille)+1);
		
		int t=read(f, contenu, taille);
		if(t<0) {
			// Erreur dans la lecture du fichier :
			contenu=strdup("Erreur dans la lecture du fichier");
			taille=strlen(contenu);
		}
	
		contenu[taille]='\0';
	}

	memcpy(res, contenu, taille);
	
	close(f);
	
	free(contenu);

	// On retourne la taille :
	return taille;
}

// ------------------------------------------------------
// Met en forme du code HTML contenant la liste de tous les serveurs
// ------------------------------------------------------
void serveurs_to_html(char *messg) {
	char res[TFICH];
	char html_header[TMESS];
	char html_serveur[TMESS];
	char html_footer[TMESS];

	// On va récupérer les différents templates html :
	lire_fichier("html/header.html", html_header);
	lire_fichier("html/serveur.html", html_serveur);
	lire_fichier("html/footer.html", html_footer);
	
	strcpy(res, html_header);
	int i;
	for(i=0; i<nb_serveurs; i=i+1) {
		char serv[TBUF];
		sprintf(serv, html_serveur, liste_serveurs[i].image, liste_serveurs[i].nom, liste_serveurs[i].addr, liste_serveurs[i].ip, liste_serveurs[i].sysdesc, liste_serveurs[i].nbuser, liste_serveurs[i].nom);
		strcat(res, serv);
	}
	strcat(res, html_footer);
	
	strcpy(messg, res);
}
