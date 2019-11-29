#include "Respuesta.h"
#include "Mensaje.h"

Respuesta::Respuesta(int pl){
	socketlocal = new SocketDatagrama(pl);
}

void Respuesta::sendReply(char *respuesta){
    
    struct mensaje msj;
    memcpy(msj.arguments, respuesta, TAM_MAX_DATA);
    msj.messageType = 1;
    PaqueteDatagrama p((char *)&msj, sizeof(struct mensaje), ip, puerto);
    socketlocal->envia(p);
}

struct mensaje* Respuesta::getRequest(void){
    PaqueteDatagrama p(sizeof(struct mensaje));
    int tam = socketlocal->recibe(p);
    memcpy(&msg, p.obtieneDatos() ,sizeof(struct mensaje));
    //msg.requestId = 1;
    strcpy(ip, p.obtieneDireccion());
    puerto = p.obtienePuerto();
    

    return &msg;
}

