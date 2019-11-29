//Programa para crear registros de votos [celular, CURP, partido, separador], con el campo "celular" como clave 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream> 
#include <list> 
#include <iterator> 


using namespace std; 

struct registro{
	char celular[11];
	char CURP[19];
	char partido[4];
};

int main(int argc, char *argv[]){
	char telefono[11], curp[19], t[11], sexo;
	int i, n, destino, j, opcion, inicial, elemento;;
	struct registro reg1;
    int dest;

	//Partidos disponibles 2018
	char const partidos[9][4] = {"PRI", "PAN", "PRD", "P_T", "VDE", "MVC", "MOR", "PES", "PNL"};

	//Entidades federativas
	char const entidad[32][3] =  {"AS", "BC", "BS", "CC", "CS", "CH", "CL", "CM", "DF", "DG", "GT", "GR", "HG", "JC", "MC", "MN", "MS", "NT", "NL", "OC", "PL", "QT", "QR", "SP", "SL", "SR", "TC", "TL", "TS", "VZ", "YN", "ZS"};

	if(argc != 3){
		printf("Forma de uso: programa numero_registros archivos_destino.txt\n");
		exit(0);
	}

	//Numero de registros n recibidos en la linea de comandos
	n = atoi(argv[1]);

	//Sí existe eror al intentar abrir el archivo (argv[2])
	if((dest = open(argv[2], O_WRONLY|O_TRUNC|O_CREAT, 0666)) == -1){
		perror(argv[2]);
		exit(-1);
	}

	//Genera un numeros telefonicos inicial de 9 digitos y despues se obtendran su secuenciales para evitar repeticion
	inicial = 500000000 + rand()%100000000;

	//Ciclo de los registros
	for(j=0; j<n; j++){
		sprintf(telefono, "5%9d", inicial);
		inicial++;
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
		//write(1, &reg1, sizeof(reg1));
		//printf("\n");

		write(dest, &reg1, sizeof(reg1));
		//write(dest, reg1.CURP, 18);
		//write(dest, reg1.partido, 3);
	}
	close(dest);
}
