#include "Solicitud.h"
#include "Registro.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <thread>
//fsync 13.8 segundos sin el 6.6 segundos


void hiloEnvia(int numSolicitud, char *IP, char *IP2){
	int archivo2;
	int desicion;	
	unsigned int id = 0;

	archivo2 = open("registros.txt", O_RDWR, 0666);
	if(archivo2 == -1){
		printf("No se pudo abrir el archivo...");
		exit(0);	
	}
	
	Solicitud solicitud, solicitud2;
	long int resp, resp2;
	struct registro regN;
	for(int x = 0; x < numSolicitud; x++){		
		read(archivo2, &regN, sizeof(regN));			
		desicion = atoi(&regN.celular[9]);		
		printf("Digito: %d\n", desicion);
		printf("Celular: %s\n", regN.celular);

		if(desicion % 2 == 0){
			printf("Enviando par...\n");
			memcpy(&resp,solicitud.doOperation(IP,7200,3,(char*)&regN,id),sizeof(int));
		}else{
			//printf("Enviando impar...\n");
			//memcpy(&resp2,solicitud2.doOperation(IP2,7200,3,(char*)&regN,id),sizeof(int));
			
		}
		id++;
		printf("id: %d \n", id);		
	}
	solicitud.getSocket()->~SocketDatagrama();
	solicitud2.getSocket()->~SocketDatagrama();
}


void principalT(char *direccion, char *direccion2, char *votos){
	int numVotos = atoi(votos);
	//thread server1(hiloEnvia, numVotos, direccion, direccion2), server2(hiloEnvia, numVotos, direccion, direccion2);	
	thread server[2];
	 //char ip[16] = "127.0.0.1";
    int numSolicitudes = atoi(votos);    
    int puerto = 7200;
    int nbd = 0,aux; //resp;
    long int resp = 0;
    int* num;
    int decision;
    int archivo;
	char telefono[11], curp[19], t[11], sexo;
	int i, n, destino, j, opcion, inicial, elemento;
	struct registro reg1;
	list <int> lista; 
    list<int>::iterator itr;
    unsigned int x;
    //char ip[16] = "127.0.0.1";
    //int puerto = 7200;    

    srand (time(NULL));
    
    archivo = open("registros.txt", O_WRONLY | O_TRUNC | O_CREAT, 0666);

	if( archivo == -1 ) {
		printf("Error no se puede abrir el archivo\n");
	}

	//Partidos disponibles 2018
	char const partidos[9][4] = {"PRI", "PAN", "PRD", "P_T", "VDE", "MVC", "MOR", "PES", "PNL"};

	//Entidades federativas
	char const entidad[32][3] =  {"AS", "BC", "BS", "CC", "CS", "CH", "CL", "CM", "DF", "DG", "GT", "GR", "HG", "JC", "MC", "MN", "MS", "NT", "NL", "OC", "PL", "QT", "QR", "SP", "SL", "SR", "TC", "TL", "TS", "VZ", "YN", "ZS"};
	

	//Numero de registros numSolicitudes

	//Llena una lista con numeros telefonicos de 9 digitos secuenciales creibles
	inicial = 500000000 + rand()%100000000;
	for (int i = inicial; i < inicial + numSolicitudes; i++) 
	{ 
		lista.push_back(i);
	} 
	for(int j=0; j<numSolicitudes; j++){
		//Obtiene un elemento aleatorio de la lista de telefonos y lo elimina de la lista para evitar la repeticion
		i = numSolicitudes - j;
		elemento = rand()%i;		
		itr = lista.begin();
		for(int k = 0; k < elemento; k++)
			++itr;
		elemento = *itr;
		lista.erase(itr);
		sprintf(telefono, "5%9d", elemento);
		strcpy(reg1.celular, telefono);
		

		if(rand()%2 == 0)
			sexo = 77;
		else
			sexo = 72;

		i = rand()%32;
		sprintf(curp, "%c%c%c%c%c%c%c%c%c%c%c%s%c%c%c%c%c", 65 + rand()%25 , 65 + rand()%25, 65 + rand()%25, 65 + rand()%25, rand()%10 + 48, rand()%10 + 48, rand()%10 + 48, rand()%10 + 48, rand()%10 + 48, rand()%10 + 48, 
			sexo, entidad[i], 65 + rand()%25, 65 + rand()%25, 65 + rand()%25, rand()%10 + 48, rand()%10 + 48);
		strcpy(reg1.CURP, curp);

		i = rand()%9;
		strcpy(reg1.partido, partidos[i]);

		write(archivo, &reg1, sizeof(reg1));
		//write(1, &reg1, sizeof(reg1));
		//printf("\n");

		//printf("Enviando registro...\n");

		//x = (unsigned int) j;

        // memcpy(&resp,solicitud.doOperation((char*)argv[1],puerto,3,(char*)&reg1,x),sizeof(int));

        // if(resp == 1){
        // 	std::cout << "Registro almacenado en el servidor!!" << std::endl;

        // }
		//SE TOMA DECISION A QUE SERVIDOR ENVIAR
	}
    close(archivo);
	
	for(int i = 0; i < 2; i++){
		server[i] = thread(hiloEnvia, numVotos, direccion, direccion2);
	}

	for(int j = 0; j < 2; j++){
		server[j].join();
	}
}



int main(int argc, char *argv[])
{
	thread principal(principalT, argv[1], argv[2], argv[3]);	

	if(argc != 4){
		printf("Forma de uso: programa ip1 ip2 numero_registros\n");
		exit(0);
	}
	//EJECUTAMOS LOS HILOS CON SU RESPECGIVA FUNCION
	principal.join();
   

        //memcpy(&resp,solicitud.doOperation((char*)argv[1],puerto,3,(char*)&reg1,x),sizeof(long int));

        //std::cout << "Numero de paquete: " << x << std::endl;       

    return 0;
}

