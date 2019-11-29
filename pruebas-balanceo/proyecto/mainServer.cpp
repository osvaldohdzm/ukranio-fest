#include "Respuesta.h"
#include "Registro.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <functional>
#include <array>
#include <bits/stdc++.h> 

using namespace std; 

static const int TAM_DATOS = 31;


using namespace std;

int main(int argc, char* argv[]){
    // abre el archivo con las palabras comunes
    // recibe una palabra y la checa
    // retorna un int dependiendo si la encontro o nel

    std::ifstream ifs("sortDic.txt");

    std::vector<std::string> vec;
    std::string palabra;

    while (ifs >> palabra) {
        vec.push_back(palabra);
    }

    Respuesta r(7200);
    struct mensaje m;
    char datos[TAM_DATOS];

    while(true) {
        //m = r.getRequest();

        memcpy(&m,(r.getRequest()),sizeof(mensaje));
        memset(datos, 0, TAM_DATOS);
        memcpy(datos, m.arguments, sizeof(char) * TAM_DATOS);

        printf("datos: %s\n", datos);

        bool found = std::binary_search(vec.begin(), vec.end(), datos);

        int reply = found ? 1 : 0 ;
        r.sendReply((char *)&reply);
    }   
    
    return 0;
}

// int main(){
//     struct timeval stamp;
//     //Se inicia el servidor
//     Respuesta respuesta(7200);
//     long int segundos;
//     long int usegundos;
//     std::cout << "Servidor Iniciado...\n" << std::endl;
//     int num[2], aux;
//     int* opOperation;
//     long int *op;
//     mensaje resp;
//     int nbd = 0, aux2, id = 0, idAux;   
//     char cTimeStamp[11];
//     int archivo;
//     struct registro reg1, reg2;
//     long t, t2;
//     string Snumeros;
//     int flag = 0;

//     vector<string> numeros;
//     struct TrieNode *root = getNode(); 
//     char temp[11];


//     cout << "Esperando...\n" << std::endl;

//     archivo = open("registros2.txt", O_WRONLY | O_TRUNC | O_CREAT, 0666);

//     if( archivo == -1 ) {
//         printf("Error no se puede abrir el archivo\n");
//     }


//     while(1){

//         //Recibe la respuesta del cliente
//         memcpy(&resp,(respuesta.getRequest()),sizeof(mensaje));
//         gettimeofday(&stamp, NULL);
//         segundos = static_cast<long int> (stamp.tv_sec);
//         usegundos = static_cast<long int>  (stamp.tv_usec);
//         segundos += usegundos;        
//         //std::cout << "Cliente: \n" <<  "IP:" << inet_ntoa(respuesta.getSocket()->getDirForanea().sin_addr);
//         //std::cout << ", Puerto: " << ntohs(respuesta.getSocket()->getDirForanea().sin_port) << "\n" << std::endl;

//         memcpy(&idAux,&resp.requestId,sizeof(unsigned int));
//         memcpy(&opOperation,&resp.operationId,sizeof(int));
//         memcpy(&reg1,&resp.arguments,sizeof(reg1));
//         //itoa(segundos, cTimeStamp, 10);
//         sprintf(cTimeStamp, "%ld", segundos);
//         //printf("%s\n", cTimeStamp);
//         memcpy(&reg1.timestamp, &cTimeStamp, sizeof(cTimeStamp));
//         //memcpy(&aux2,&resp.arguments,sizeof(reg1));
//         // memcpy(&reg1,paqueteRecepcion.obtieneDatos(),sizeof(reg1));
//         //printf("Numero registro: %s \t numero atoi: %d\n", reg1.celular, (int) reg1.celular);  

//         // if(id == 0){
//         //     memcpy(temp,&reg1.celular, sizeof(reg1.celular));
                       
//         // }             

//         for (int i = 0; i < numeros.size(); i++){
//             insert(root, numeros[i]); 
//         }

//         if(search(root, reg1.celular)){            
//             flag = 1;
//             segundos = 0;
//             printf("Número repetido...\n");
//         }else{               
//             numeros.push_back(reg1.celular);        
//         }
//         // if(id == 999){ //Indicar el id 
//         //     if(search(root, temp)){            
//         //         flag = 1;
//         //         segundos = 0;
//         //         printf("Número repetido...\n");
//         //     }
//         // }
//         printf("Paquete: %d\n", id);

//         if (idAux == id && flag == 0) {            
//             write(archivo, &reg1, sizeof(reg1));
//             //fsync(archivo);
//             printf("Se recibio y se escribio en la BD: \n");
//             write(1, &reg1, sizeof(reg1));        
//             printf("\n");
//             id++;
//         }
//         //nbd = 1;
//         flag = 0;
//         op = (&segundos);
//         respuesta.sendReply((char*)op);
//     }

//     close(archivo);
    
//     return 0;
// }

