using namespace std;

#include <sys/socket.h>
#include <netinet/in.h>
//#include "Stream.h"
#include <sys/types.h>
#include <iostream>
#include "DataTransfertPullTCP.h"

int main()
{
    int PORT = 1234;
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == INVALID_SOCKET)
    {
        perror("socket()");
        exit(errno);
    }

    SOCKADDR_IN sin = { 0 };

    sin.sin_addr.s_addr = htonl(INADDR_ANY); /* nous sommes un serveur, nous acceptons n'importe quelle adresse */

    sin.sin_family = AF_INET;

    sin.sin_port = htons(PORT);

    if(bind (sock, (SOCKADDR *) &sin, sizeof sin) == SOCKET_ERROR)
    {
        perror("bind()");
        exit(errno);
    }

    if(listen(sock, 5) == SOCKET_ERROR)
    {
        perror("listen()");
        exit(errno);
    }

    SOCKADDR_IN csin = { 0 };
    SOCKET csock;

    int sinsize = sizeof csin;

    csock = accept(sock, (SOCKADDR *)&csin, &sinsize);

    if(csock == INVALID_SOCKET)
    {
        perror("accept()");
        exit(errno);
    }
    
    DataTransfertPullTCP stream = DataTransfertPullTCP(csin, PORT);

    closesocket(sock);
    closesocket(csock);
}