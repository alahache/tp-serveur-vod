                                                                     __ 
.-----..-----..----..--.--..-----..--.--..----.    .--.--..-----..--|  |
|__ --||  -__||   _||  |  ||  -__||  |  ||   _|    |  |  ||  _  ||  _  |
|_____||_____||__|   \___/ |_____||_____||__|       \___/ |_____||_____|
                                                                        
------------------------------------------------------------------------

INSTRUCTIONS DE COMPILATION :
	Ce serveur a été conçu pour être exécuté sous une plateforme
	Linux. Votre version du kernel doit être supérieure à la
	2.5.44 pour supporter les appels systèmes utilisés (epoll)

	Pour compiler le serveur et générer l'exécutable, vous devez vous
	positionner dans le répertoire serveur/ et lancer la commande :
	> make
	
LANCEMEMENT DU SERVEUR :
	> ./serveur_vod [config.conf]
	
	Si vous souhaitez lancer un fichier de configuration différent de
	celui par défaut, précisez-le en argument juste après le nom de
	l'éxecutable.
	
CONFIGURATION DU SERVEUR :
	config/server.conf
	
CLIENTS :
	Ce serveur a été tout particulièrement testé avec les clients
	LinuxWindowsMac et VideoClient (sous wine).
