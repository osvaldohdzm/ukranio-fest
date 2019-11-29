#include "SocketDatagrama.h"
#include "PaqueteDatagrama.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>


using namespace std;

int main(int argc, char* argv[]){

	int dest;

	if(argc != 2){
		printf("Forma de uso: ./servidor nombre_del_archivo_destino.txt\n");
		exit(-1);
	}

	if((dest = open(argv[1],  O_WRONLY | O_APPEND)) == -1){
		perror(argv[1]);
		exit(-1);
	}


	SocketDatagrama socket = SocketDatagrama(7200);
	int * numeros;
	PaqueteDatagrama datagrama = PaqueteDatagrama(31);
	int n=socket.recibe(datagrama);


	cout<<"Tamaño de recibido: "<<n << endl;
	cout<<"Datos Recibidos: "<<datagrama.obtieneDatos()<<endl;

	write(dest, datagrama.obtieneDatos(), 31);
	write(dest, "\n", 1);
	close(dest);

	return 0;
}