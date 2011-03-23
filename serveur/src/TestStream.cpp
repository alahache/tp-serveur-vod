using namespace std;

#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
//#include "Stream.h"
#include <sys/types.h>
#include <iostream>
#include "DataTransfertTCP.h"
#define SOCKET_ERROR -1
int main()
{
    int PORT = 1234;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        cerr << "socket()" << endl;
        exit(EXIT_FAILURE);
    }

    sockaddr_in sin;

    sin.sin_addr.s_addr = htonl(INADDR_ANY); /* nous sommes un serveur, nous acceptons n'importe quelle adresse */

    sin.sin_family = AF_INET;

    sin.sin_port = htons(PORT);

    // On contourne le probleme de l'adresse et du port déjà utilisés :
    int opt=1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    if(bind (sock, (sockaddr *) &sin, sizeof sin) < 0)
    {
        cerr << "bind()" << endl;
        exit(EXIT_FAILURE);
    }

    /*if (connect (sock, (sockaddr *) &sin, sizeof sin) == -1)
     {
        cerr << "Connection failed" << endl;
        exit(EXIT_FAILURE);
     }*/

    if(listen(sock, 5) < 0)
    {
        cerr << "listen()" << endl;
        exit(EXIT_FAILURE);
    }

    sockaddr_in csin;
    int csock;

    socklen_t sinsize = sizeof(csin);

    
    csock = accept(sock, (sockaddr *)&csin, &sinsize);

    if(csock < 0 )
    {
        cerr << "accept()" << endl;
        exit(EXIT_FAILURE);
    }

    DataTransfertTCP stream = DataTransfertTCP(csin, PORT);

    stream.Begin();

    close(sock);
    //close(csock);
}