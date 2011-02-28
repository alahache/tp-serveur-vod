
// http://en.wikipedia.org/wiki/POSIX_Threads
// https://computing.llnl.gov/tutorials/pthreads/
// http://www.yolinux.com/TUTORIALS/LinuxTutorialPosixThreads.html
// http://franckh.developpez.com/tutoriels/posix/pthreads/
// http://stackoverflow.com/questions/1606400/how-to-sleep-or-pause-a-pthread-in-c-on-linux

#include <pthread.h>
#include <cstdlib>
#include <iostream>

#define MAX_TRANSFERTS 5

// Thread de transfert
void * transfert ( void * arg)
{
	int num_transfert = (int) arg;

	std::cout << "Début du transfert " << num_transfert << std::endl;
	sleep(rand() % 10 + 1);
	std::cout << "Fin du transfert " << num_transfert << std::endl;
	
	return 0;
}

// Thread principal
int main()
{
	pthread_t transferts[MAX_TRANSFERTS];
	
	// Créer les thread de transfert :
	for(int i=0; i<MAX_TRANSFERTS; i++)
	{
		std::cout << "Création Thread transfert " << i << std::endl;
		int err = pthread_create( &transferts[i], NULL, transfert, (void *) i );
		if(err)
		{
			std::cerr << "Erreur création Thread " << std::endl;
		}
	}
	
	// Attendre la fin des transferts :
	for(int i=0; i<MAX_TRANSFERTS; i++)
	{
		int err = pthread_join( transferts[i], NULL );
		if(err)
		{
			std::cerr << "Erreur attente fin Thread " << i << std::endl;
		}
	}
	
	return 0;
}
