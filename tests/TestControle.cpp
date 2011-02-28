
// http://vpj.posterous.com/tcp-echo-server-example-in-c-using-epoll


#include <iostream>
#include <string>
#include <cstdlib>			// exit
#include <sys/types.h>		// Pour plus de compatibilité
#include <sys/socket.h>		// Sockets
#include <sys/epoll.h>		// Gestion de multiples descripteurs (socket)
#include <netinet/in.h>		// support IPv4
#include <fcntl.h>			// Permet de manipuler des descripteurs
#include <arpa/inet.h>		// inet_ntoa

using namespace std;

#define NBMAX 1000
#define MAX_EPOLL_EVENTS_PER_RUN 10
#define EPOLL_RUN_TIMEOUT 5
#define BUFFER_SIZE 1024

void setnonblocking(int fd)
// Permet de modifier un descripteur afin de le rendre non bloquant
{
	int flags = fcntl(fd, F_GETFL, 0);
	fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

int main() {

	// On va simplement faire un programme tout con qui permet de récupérer des commandes
	// en TCP de plusieurs clients et qui lance éventuellement des threads pour traiter
	// chaque transfert
	
	// -----------------------
	// Création de la socket :
	// -----------------------
	
	// On itinialise le port à 1234
	int port = 1234;
	
	// On crée une socket en IPv4, TCP
	int s = socket(PF_INET, SOCK_STREAM, 0);
	if(s < 0)
	{
		cerr << "socket" << endl;
		exit(EXIT_FAILURE);
	}
	
	// On attache le port à la socket :
	struct sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = htonl(INADDR_ANY);		// htonl : convertit un long vers le format réseau
		addr.sin_port = htons(port);					// htons : convertit un short vers le format réseau
		
	if(bind(s, (struct sockaddr *) &addr, sizeof(addr)) < 0)
	{
		cerr << "bind" << endl;
		exit(EXIT_FAILURE);
	}
	
	// On met en écoute la socket :
	if(listen(s, NBMAX) < 0)
	{
		cerr << "listen" << endl;
		exit(EXIT_FAILURE);
	}
	
	// ------------------------
	// Traitement des clients :
	// ------------------------
	
	// On crée le descripteur epfd gérant l'epoll :
	int epfd = epoll_create1(0);
	if(epfd < 0)
	{
		cerr << "epoll_create" << endl;
		exit(EXIT_FAILURE);
	}
	
	// On contourne le probleme de l'adresse et du port deja utilise :
	int opt=1;
	setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	
	// On surveille la socket s dans epfd :
	struct epoll_event ev, events[MAX_EPOLL_EVENTS_PER_RUN];
		ev.events = EPOLLIN;
		ev.data.fd = s;
	if(epoll_ctl(epfd, EPOLL_CTL_ADD, s, &ev) < 0)
	{
		cerr << "epoll_ctl ADD socket" << endl;
		exit(EXIT_FAILURE);
	}
	
	for(;;)
	{
		// On attends qu'un descripteur dans epfd veuille faire une opératon I/O :
		int nfds = epoll_wait(epfd, events, MAX_EPOLL_EVENTS_PER_RUN, EPOLL_RUN_TIMEOUT);
		if (nfds < 0)
		{
			cerr << "epoll_wait" << endl;
			exit(EXIT_FAILURE);
		}

		// On parcoure les descripteurs prêts :
		for(int i = 0; i < nfds; i++)
		{
			int fd = events[i].data.fd;
			
			// TODO : gérer entrée standard pour quitter le serveur proprement
			
			if(fd == s)
			{
				// Demande de connexion sur le socket s :
				struct sockaddr_in client_addr;
				socklen_t client_addr_len = sizeof(client_addr);
				int conn_sock = accept(s, (struct sockaddr *) &client_addr, &client_addr_len);
				if(conn_sock < 0)
				{
					cerr << "accept" << endl;
					exit(EXIT_FAILURE);
				}
				setnonblocking(conn_sock);	// on met le descripteur en "non bloquant" (cf. man epoll)
			
				cout << "[" << conn_sock << "] Nouveau client : " << inet_ntoa(client_addr.sin_addr) << endl;
				
				// On s'apprête à recevoir des commandes du client :
				ev.events = EPOLLIN | EPOLLET;
				ev.data.fd = conn_sock;
				if(epoll_ctl(epfd, EPOLL_CTL_ADD, conn_sock, &ev) < 0)
				{
					cerr << "epoll_ctl ADD client" << endl;
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				// On utilise ici un autre descripteur que la socket s : il s'agit donc d'un conn_sock.
				// On va donc traiter ici la requête.
				
				char buffer[BUFFER_SIZE];
				
				if(events[i].events & EPOLLHUP) {
					
					// DECONNEXION
					
					cout << "[" << fd << "] Déconnexion du client" << endl;
					
					if(epoll_ctl(epfd, EPOLL_CTL_DEL, fd, &ev) < 0)
					{
						cerr << "epoll_ctl DEL client" << endl;
						exit(EXIT_FAILURE);
					}
					
					close(fd);
					
				}
				else if(events[i].events & EPOLLERR) {
				
					// ERREUR QUELCONQUE
				
					cerr << "EPOLLERR" << endl;
					
				}
				else if(events[i].events & EPOLLIN) {
				
					// DEMANDE DE LECTURE
					
					cout << "[" << fd << "] Réception d'une requête de lecture..." << endl;
					
					int received = recv(fd, buffer, BUFFER_SIZE, 0);
					//int received = read(fd, buffer, BUFFER_SIZE);
					if(received > 0)
					{
						
						// LECTURE D'UN MESSAGE
						
						buffer[received] = '\0';
						cout << "Lecture de " << received << " octets : " << buffer << endl;
						
						string message = buffer;
						message.resize(message.length()-2);	// Enlever CRLF
						
						if(message == "end" || message == "END" || message == "close" || message == "CLOSE")
						{
							// DECONNEXION
					
							cout << "[" << fd << "] Déconnexion du client" << endl;
					
							if(epoll_ctl(epfd, EPOLL_CTL_DEL, fd, &ev) < 0)
							{
								cerr << "epoll_ctl DEL client" << endl;
								exit(EXIT_FAILURE);
							}
					
							close(fd);
						}
						
					}
					else
					{
						
						// DECONNEXION
						// Message nul ou < 0
						
						cout << "[" << fd << "] Déconnexion du client" << endl;
					
						if(epoll_ctl(epfd, EPOLL_CTL_DEL, fd, &ev) < 0)
						{
							cerr << "epoll_ctl DEL client" << endl;
							exit(EXIT_FAILURE);
						}
						
						close(fd);
						
					}
				}
			}
		}
	}
	
	close(epfd);
	close(s);
	
	return 0;

}
