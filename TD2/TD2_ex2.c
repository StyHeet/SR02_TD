#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>


struct sigaction handler_pere, handler_fils;
pid_t pid_fils = 0, pid_pere = 0;
char min = 'a', maj ='A';
void ecrire_maj(int sig) {
	printf("%c",maj);
	fflush(stdout);
	if (maj == 'Z') {
		kill(getppid(),SIGINT);
		return;
	}
	maj ++;
	kill(getppid(),SIGUSR1);
}

void ecrire_min(int sig) {
	printf("%c",min);
	fflush(stdout);
	kill(pid_fils,SIGUSR1);
	if (min == 'z') {
		
		return;
	}
	min ++;
}

int main(int argc, char const *argv[])
{
	
	pid_fils = fork();

	if (pid_fils < 0){
		printf("Erreur fork");
		return -1;
	}
	if (pid_fils ==0 ) { //cas du fils
		handler_fils.sa_handler = &ecrire_maj;
		sigaction(SIGUSR1,&handler_fils,0);
		while(1){
			pause();
		}
	}
	if (pid_fils >0) { //cas du pere
		handler_pere.sa_handler = &ecrire_min;
		sigaction(SIGUSR1,&handler_pere,0);
		raise(SIGUSR1);
		while(1){
			pause();
		}
	}



	return 0;
}