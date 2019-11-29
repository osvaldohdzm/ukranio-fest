#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream> 
#include <list> 
#include <iterator> 
#include "SocketDatagrama.h"
#include "PaqueteDatagrama.h"

using namespace std;
/* cliente que lee un archivo que contiene un único registro, y lo manda en un mensaje UDP hacia el servidor de base 
de datos*/
int main(int argc, char* argv[]){

	char buffer[BUFSIZ];//region de memoria para el almacenamiento temporal de datos
	int nbytes, origen;

	if(argc != 2){
		printf("Forma de uso: ./cliente nombre_del_archivo.txt\n");
		exit(-1);
	}

	if((origen = open(argv[1], O_RDONLY)) == -1){
		perror(argv[1]);
		exit(-1);
	}

	nbytes = read(origen, buffer, sizeof(buffer));
	close(origen);

	cout << buffer << endl;


	SocketDatagrama socket = SocketDatagrama(7000);
	PaqueteDatagrama datagrama = PaqueteDatagrama(buffer, 31,"127.0.0.1", 7200);
	//PaqueteDatagrama datagrama = PaqueteDatagrama(buffer, 31,"10.100.74.238", 7200);
	//socket.envia(&datagrama);
	int n = socket.envia(datagrama);

	cout << "Tamaño de envio: "<< n << endl;
	
	return 0;
}
