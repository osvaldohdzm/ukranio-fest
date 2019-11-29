#include "Solicitud.h"
#include <cstdlib>
#include <cstring>


Solicitud::Solicitud(){
    modificador=0; //Variable que aumenta por cada solicitud del mismo cliente
    //socketlocal;
}
char * Solicitud::doOperation(char *IP, int puerto, int operationId, char *arguments) {
    int res, contador;
    struct mensaje msj;
    msj.messageType = 0;
    msj.requestId = modificador;//MANDO UN IDENTIFICADOR EN CERO
    

    msj.operationId = operationId;
    memcpy(msj.arguments, arguments, TAM_MAX_DATA);

    //size_t tam2 = 2*sizeof(int);
    PaqueteDatagrama datagrama((char *)&msj, sizeof(struct mensaje), IP, puerto);
    socketlocal.envia(datagrama);

    PaqueteDatagrama databack(sizeof(struct mensaje));

    for (int i = 0; i < 7; i++){    
        int rec = socketlocal.recibeTimeout(databack, 3, 0); //recibe la respuesta 
        if ( rec > 0){ //Sí se recibió la respuesta correcta
          //  printf("RECIBIDO CON EXITO\n");    
            memcpy(&msj_databack, databack.obtieneDatos(), sizeof(struct mensaje));

            if(msj.requestId != msj_databack.requestId){
                socketlocal.envia(datagrama);
                return msj_databack.arguments;
            }else{
                break;
            }
            
       }else if (rec == -1){ 
            if(i==6){
                exit(0);
            }
            socketlocal.envia(datagrama); 
        }
    }        
    return msj_databack.arguments;
}
