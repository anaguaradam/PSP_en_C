#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>


int main(int argc, char const *argv[])
{
	int fp;
	char buffer [100];
	
	fp = open("./pipe1", O_RDWR);

	if (fp==-1){

		fprintf(stderr, "El fichero no se ha podido abrir" );
		exit(-1);// si hay error sale del programa
	}
	fprintf(stderr, "Enviando mensaje...\n" );
	read(fp,buffer,strlen(buffer));
	fprintf(stderr, "Mensaje enviado...%s\n", buffer );

	close(fp);
	return 0;
}