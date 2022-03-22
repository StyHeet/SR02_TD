#include "sharemem.h"

#define MAXSIZE 1024

int copiefichier(int f1, int f2) {
	char buff[MAXSIZE];
	int nb_octets= 0, total=0;
	
	do {
		nb_octets = read(f1,&buff,MAXSIZE);
		
		write(f2,&buff,nb_octets);
		total += nb_octets;

	} while ( nb_octets != 0);

	return total;
}




int main(int argc, char const *argv[])
{
	int f1 = open("f1.dat",O_CREAT|O_RDONLY);
	int f2 = open("f2.dat",O_CREAT|O_WRONLY);

	printf("%d\n", copiefichier(f1,f2));
	return 0;
}