#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{

	int fd[2];
	char buffer [10];
	pid_t pid;
	int retorno;

	retorno = pipe(fd);
	if (retorno==-1){
		fprintf(stderr, "error!\n");
		exit(-1);
	}
	pid = fork();
	switch (pid){
		case -1://caso de error
			fprintf(stderr, "No se ha podido crear el proceso del hijo\n" );
			exit(-1);
			break;
		case 0://proceso hijo
			close [1];//cierro el canal de lectura
			fprintf(stdout, "Soy el hijo, voy a escribir en el pipe..." );//este proceso sólo lo ejecutará el  hijo
			//write(fd[1],"Hola soy tu hijo",17*sizeof(char));//primero descriptor de escritura fd[1],
			// lo que queremos escribir, cuantos caracteres quiero envir de la cadena(esta tiene 18 pero envio 17)
			sleep (2);
			int codigo =100;//char mensaje[]="hola soy sty hijo.\0"
			write(fd[1],&codigo,1*sizeof(int));//primero descriptor de escritura fd[1],&indica la posicion de memoria a partir de la cual leer
			//si no se el tamaño del mensaje pongo strlen(mensaje*s1zeof(char))
			break;
		default:
			close[0];
			fprintf(stdout, "Hola soy el padre voy a leer del pipe...\n" );
			//read(fd[0],buffer,17*sizeof(char));//leo de fd[0], lectura primera posiscion escritura fd[1]segunda posicion, lo leo de buffer y leo 17
			//fprintf(stdout, "Mensaje leído: %s\n", buffer);
			int codigo_leido;
			read(fd[0],&codigo_leido,1*sizeof(int));//aqui si pusiera strlen(mensaje)aqui ponsira sizeof(buffer)y en fprintf ences
			//de codigo leido pondría buffer....strlen esta dentro de lalibreria string.h
			fprintf(stdout, "Mensaje leído: %d\n",codigo_leido );
			wait(NULL);
			break;

	}

}