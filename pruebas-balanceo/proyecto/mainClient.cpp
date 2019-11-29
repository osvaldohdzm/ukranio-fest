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
#include <vector>
#include <bits/stdc++.h>
//fsync 13.8 segundos sin el 6.6 segundos
int check_malas[3];
void hilo1(string cad){
	char texto[cad.length() + 1]; 
	strcpy(texto, cad.c_str());
	int malas;
	Solicitud a;
	//struct mensaje * m =(struct mensaje *)a.doOperation("10.100.67.218", 7200, i, (char *)texto);
	//memcpy(&malas,m->arguments,sizeof(int));
	memcpy(&malas,a.doOperation("127.0.0.1",7200,3,(char*)&texto,1),sizeof(int));
	check_malas[0] = malas;
	a.getSocket()->~SocketDatagrama();
	//pthread_exit(0);
}
void hilo2(string cad){
	char texto[cad.length() + 1]; 
	strcpy(texto, cad.c_str());
	int malas;
	Solicitud a;
	//struct mensaje * m =(struct mensaje *)a.doOperation("10.100.67.218", 7200, i, (char *)texto);
	//memcpy(&malas,m->arguments,sizeof(int));
	memcpy(&malas,a.doOperation("127.0.0.1",7200,3,(char*)&texto,1),sizeof(int));
	check_malas[1] = malas;
	a.getSocket()->~SocketDatagrama();
	//pthread_exit(0);
}

void hilo3(string cad){
	char texto[cad.length() + 1]; 
	strcpy(texto, cad.c_str());
	int malas;
	Solicitud a;
	//struct mensaje * m =(struct mensaje *)a.doOperation("10.100.67.218", 7200, i, (char *)texto);
	//memcpy(&malas,m->arguments,sizeof(int));
	
	//memcpy(&malas,a.doOperation("127.0.0.1",7200,3,(char*)&texto,1),sizeof(int));
	memcpy(&malas,a.doOperation("127.0.0.1",7200,3,(char*)&texto,1),sizeof(int));
	check_malas[2] = malas;
	a.getSocket()->~SocketDatagrama();
	//pthread_exit(0);
}


int main(int argc, char *argv[])
{
	//principalT(argv[1], argv[2], argv[3]);	

	// if(argc != 4){
	// 	printf("Forma de uso: programa ip1 ip2 numero_registros\n");
	// 	exit(0);
	// }

	int no_comprendidas=0;
	vector<string> palabras;
	vector<thread> hilos;
	int indice = 0;
string words[] = {"abandona", "abandonada", "anticonstitucionalmente"};

	//string words[] = {"hola", "casa", "parangrti"};
	for(string s : words){
		palabras.push_back(s);
		if(indice == 0)
			hilos.push_back(thread(hilo1, palabras[0]));
		else if(indice == 1)
			hilos.push_back(thread(hilo2, palabras[1]));
		else
			hilos.push_back(thread(hilo3, palabras[2]));
		if(palabras.size() == 3){
			//correr los tres hilos
			for(int i =0; i < 3; i++){
				hilos[i].join();
			}
			vector<string> pendientes;
			for(int i =0; i < 3;i++){
				if(check_malas[i] != -1){
					no_comprendidas += (check_malas[i]) ? 1 : 0;
				}
				pendientes.push_back(palabras[i]);
			}
			palabras.clear();
			for(string xx: pendientes){
				palabras.push_back(xx);
			}
		}
		indice++;
		indice%=3;
	}
	cout << "Comprendidas: " << no_comprendidas << endl;

	// string s;
	// while(cin >> s){
	// 	cout << "La palabra es: " << s << endl;
	// 	char texto[s.length() + 1]; 
  
	//     // copying the contents of the 
	//     // string to char array 
	//     strcpy(texto, s.c_str());
	// 	int malas;
	// 	Solicitud solicitud;
	// 	memcpy(&malas,solicitud.doOperation("10.100.77.14",7200,3,(char*)&texto,0),sizeof(int));
	// 	//struct mensaje * m =(struct mensaje *)a.doOperation("10.100.66.206", 7200, i, (char *)texto);
	// 	//memcpy(&malas,m->arguments,sizeof(int));
	// 	printf("Se encontro o no %d\n",malas);

	// }

	//EJECUTAMOS LOS HILOS CON SU RESPECGIVA FUNCION
	//principal.join();
   

        //memcpy(&resp,solicitud.doOperation((char*)argv[1],puerto,3,(char*)&reg1,x),sizeof(long int));

        //std::cout << "Numero de paquete: " << x << std::endl;       

    return 0;
}

