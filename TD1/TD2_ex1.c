#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>

pid_t pid;
struct sigaction handler_temp, handler_fils;

void alarme(int sig) {
	kill(pid,SIGUSR1);
	
	alarm(5);
}

void thermo(int sig) {
	int temperature = random() % (40-10 +1) +10;
	printf("\nIl fait %d degrées \n",temperature);
	
}



int main(int argc, char const *argv[])
{
	
	
	handler_temp.sa_handler = &alarme;

	sigaction(SIGALRM,&handler_temp,0);
	
	pid = fork();
	if (pid == -1) {
		printf("Erreur fork, abort\n");
		return -1;
	}

	if (pid == 0) { //dans le fils 
		handler_fils.sa_handler = &thermo;

		sigaction(SIGUSR1,&handler_fils,0);	
		while(1) {
			pause();

		}	
		
		
		

	}
	if (pid >0) {
		printf("Waiting");
		alarm(5);
		while(1) {
			sleep(1);
			printf(".");
			fflush(stdout);
		}




	}
	printf("\n");
	return 0;
}