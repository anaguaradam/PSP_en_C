#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
	int pipe_padreHijo[2];
	int pipe_hijoPadre[2];
	char buffer [10];
	pid_t pid;
	int retorno;


	retorno = pipe(pipe_padreHijo);
	if (retorno==-1){
		fprintf(stderr, "error!no se ha podido crear el proceso hijo\n");
		exit(-1);
	}
	retorno = pipe(pipe_hijoPadre);
	if (retorno==-1){
		fprintf(stderr, "error!no se ha podido crear el proceso padre\n");
		exit(-1);
	}

	pid = fork();
	switch (pid){
		case -1://caso de error
			fprintf(stderr, "No se ha podido crear el proceso del hijo\n" );
			exit(-1);
			break;
		case 0://proceso hijo
			close (pipe_hijoPadre[0]);//cierro el canal de lectura
			close (pipe_padreHijo[1]);//cierro el canal de escritura
			fprintf(stdout, "Soy el hijo, voy a escribir en el pipe...%d\n" , pipe_hijoPadre);
			sleep (2);
			char mensaje[]= "Soy tu hijo.\0";
			int codigo =100;//char mensaje[]="hola soy sty hijo.\0"
			write(pipe_hijoPadre[1], mensaje,(strlen(mensaje)+1)*sizeof(char));//primero descriptor de escritura fd[1],&indica la posicion de memoria a partir de la cual leer
			read(pipe_padreHijo[0], buffer, sizeof(buffer));
			fprintf(stdout, "Soy el hijo. He recibido el siguiente mensaje: %s\n",buffer );
			//si no se el tamaño del mensaje pongo strlen(mensaje*s1zeof(char))
			break;
		default:
			close (pipe_padreHijo[0]);//cierro el canal de lectura
			close (pipe_hijoPadre[1]);//cierro el canal de escritura
			char mensaje[] = "Soy papa. \0";
			fprintf(stdout, "Hola soy el padre voy a leer del pipe...%d\n", pipe_padrePadre );
			write(pipe_padreHijo[1], mensaje,(strlen(mensaje)+1)*sizeof*(char));
			read(pipe_hijoPadre[0],buffer,sizeof(buffer));//aqui si pusiera strlen(mensaje)aqui ponsira sizeof(buffer)y en fprintf ences
			fprintf(stdout, "Soy el papa. He recbido el siguiente mensaje : %d\n",buffer );
			wait(NULL);
			break;

	}

}