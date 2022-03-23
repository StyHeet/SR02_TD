#include "sharemem.h"
#define SHMSIZE 27


int main(int argc, char const *argv[])
{
	key_t key;
	key = 2017;
	int shmid = shmget(key,SHMSIZE,IPC_CREAT | 0660);

	if (shmid == -1) {

		printf("Erreur création segment mémoire\n");
		perror(":");
		return -1;
	}
	char * adr_mem;
	printf("L'identifiant de l'espace mémorie est %d\n",shmid);
	adr_mem = shmat(shmid,NULL,0);
	printf("ok\n");
	if (adr_mem == (char*)-1) {
		printf("Erreur mappage \n");
		perror("shmat");
		exit(1);
		return -1;
	}
	char * mem = adr_mem;

	for (char c ='a'; c < 'z'; c++) {
		//printf("%c",c);
		*mem = c;
		mem++;
	}

	shmdt(adr_mem);
	shmctl(shmid,IPC_RMID,0);



	return 0;
}