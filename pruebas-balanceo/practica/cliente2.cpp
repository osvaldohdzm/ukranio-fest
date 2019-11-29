#include "Solicitud.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

struct registro{
    char celular[11];
    char CURP[19];
    char partido[4];
};

int main(int argc, char *argv[]){
    srand(time(NULL));
    Solicitud cliente;
    char buffer[BUFSIZ];//region de memoria para el almacenamiento temporal de datos
    struct registro reg;
    int nbytes, origen;
    char respuesta[20];

    if(argc<3)
        printf("USO: ./cliente2 num_registros archivo.txt\n"); 

    //Abrimos el archivo donde leeremos los registros y validamos que no tenga error
    if((origen = open(argv[2], O_RDONLY)) == -1){
        perror(argv[1]);
        exit(-1);
    }

    int numeroRegistros = atoi(argv[1]); //El argumento en consola será mi n (numero de registros a enviar)
    printf("numero de registros es: %d\n", numeroRegistros);
    int envia_registos=1; //id de operación, ahorita no importa

    //se manda "n" veces la solicitud para enviar cada registro
    for (int i = 0; i < numeroRegistros; ++i){
        nbytes = read(origen, &reg, sizeof(reg));
        printf("\n");
        write(1, &reg, sizeof(reg));
        printf("\n");
        memcpy(respuesta, cliente.doOperation("127.0.0.1", 1415,envia_registos, (char *)&reg), sizeof(respuesta));       
        printf("Acuse de recibo: %s \n", respuesta);
    }    
        close(origen); 

   // printf("Resultado: %d\n", respuesta);
    return 0;
}