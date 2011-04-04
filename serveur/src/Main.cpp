
/*************************************************************************
                         Main  -  programme principal
                             -------------------
    début                : 12 mars 2011
    copyright            : (C) 2011 par Arnaud Lahache
*************************************************************************/

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Server.h"

//---------------------------------------------------- PROGRAMME PRINCIPAL

int main(int argc, char* argv[])
{
	char* pathConf;
	if(argc > 1)
	{
		// On lance le serveur avec un fichier de conf :
		pathConf = argv[1];
		Server server(pathConf);
	}
	else
	{
		// On lance simplement le serveur :
		Server server;
	}
	
	return 0;
}
