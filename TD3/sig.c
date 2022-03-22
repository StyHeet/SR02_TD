#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <X11/Xlib.h>
 
int drawstr (int x, int y, char *str, int lng);
int drawrec (int x, int y, int larg, int hter);
int initwind(char *col1, char *col2);
int initrec();
int setbigrec (char *col);
int setlitrec (char *col);
int attendreclic();
int ecritrec (char *buf,int lng);
int rectvert(int n);
int detruitrec();


struct sigaction handler_pere, handler_fils;
pid_t pid_fils, pid_pere;
int nb_sig_pere =0, nb_sig_fils =0,i,n,showRect =0;

void captpere(int sig) {

	nb_sig_pere ++;
	printf("\nNombre de sigint reçu par le père : %d\n", nb_sig_pere);
  	
	fflush(stdout);
	
	if (nb_sig_pere >=3){
		printf("\nFin du père, 3 sigint reçus\n");
		fflush(stdout);
		exit(0);
		
	}
	
}

void captfils(int sig) {

	nb_sig_fils++;
	printf("\nNombre de sigint reçu par le fils : %d\n", nb_sig_fils);
  	fflush(stdout);
	if (nb_sig_fils ==3){
		
		printf("Sortie du fils\n");
		fflush(stdout);
		detruitrec(); // on détruit la fenetre et on termine le programme
		exit(0);
		
		
	}
	
	showRect =1;
	
	
	
}



int main(int argc, char const *argv[])
{
	//int i =0;
	pid_fils = fork();

	if (pid_fils <0) {
		printf("Erreur fork");
		exit(-1);
	}
	if (pid_fils == 0) {
		pid_pere =getppid();
		initrec(); //initialisation de l'interface
		
		handler_fils.sa_handler = captfils; // définition de la structure du handler  
		sigaction(SIGINT,&handler_fils,NULL); 
		
		
		do {
			
			i = attendreclic();
			if (i == 0){
				kill(pid_pere,SIGINT); //si le bouton 0 est pressé, envoie d'un sigint au père
			}
			if (i == 1){
				raise(SIGINT); // Rajout de la fonctionnalité pour le bouton 1 afin de montrer le bon fonctionnement du handler
			}
			if (showRect == 1) { // Si le booleen showrect est actif on affiche le rectangle vert puis on désactive le booleen. 
				rectvert(5);	// Solution mise en place car la reception d'un signal sigint sur le fils depuis un control C sur le terminal fait crasher la fenetre
				showRect =0;	// Le problème est lié au traitement de la fonction rectvert dans le handler car sans celle-ci aucun problème n'est constaté.
			}


		}while( i != -1 );
	}

	if (pid_fils >0) {
		handler_pere.sa_handler = captpere;
		sigaction(SIGINT,&handler_pere,NULL);
		
		while (1) {
			n=sleep(10);
			if(n > 0){
	        printf("Processus pere appelé : il reste %d secondes à faire lorsque cet appel a été interrompu par un SIGINT\n", n);
	        fflush(stdout);
      }
		}
	}

	return 0;
}