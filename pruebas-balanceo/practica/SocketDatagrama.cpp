#include "SocketDatagrama.h"
#include <errno.h>

SocketDatagrama::SocketDatagrama(int puerto) {
    s = socket(AF_INET, SOCK_DGRAM, 0);
    bzero((char *)&direccionLocal, sizeof(direccionLocal));
    direccionLocal.sin_family = AF_INET;
    direccionLocal.sin_addr.s_addr = INADDR_ANY;
    direccionLocal.sin_port = htons(puerto);
    bind(s, (struct sockaddr *)&direccionLocal, sizeof(direccionLocal));
}

SocketDatagrama::SocketDatagrama() {
    int puerto;
    s = socket(AF_INET, SOCK_DGRAM, 0);
    bzero((char *)&direccionLocal, sizeof(direccionLocal));
    direccionLocal.sin_family = AF_INET;
    direccionLocal.sin_addr.s_addr = INADDR_ANY;
    direccionLocal.sin_port = htons(puerto);
    bind(s, (struct sockaddr *)&direccionLocal, sizeof(direccionLocal));
}

SocketDatagrama::~SocketDatagrama() {
    printf("%s\n", "Se cerro");
    close(s);
}

int SocketDatagrama::envia(PaqueteDatagrama &p) {
    bzero((char *)&direccionForanea, sizeof(direccionForanea));
    direccionForanea.sin_family = AF_INET;
    direccionForanea.sin_addr.s_addr = inet_addr(p.obtieneDireccion());
    direccionForanea.sin_port = htons(p.obtienePuerto());
    return sendto(s, p.obtieneDatos(), p.obtieneLongitud(), 0, (struct sockaddr *)&direccionForanea, sizeof(direccionForanea)); 
}

int SocketDatagrama::recibe(PaqueteDatagrama &p) {
    char datos[p.obtieneLongitud()];
    char aux[INET_ADDRSTRLEN];
    socklen_t clilen = sizeof(direccionForanea);
    int i = recvfrom(s, datos, p.obtieneLongitud(), 0, (struct sockaddr *) &direccionForanea, &clilen);
    inet_ntop(AF_INET, &(direccionForanea.sin_addr), aux, INET_ADDRSTRLEN);
    p.inicializaPuerto(ntohs(direccionForanea.sin_port));
    p.inicializaIp(aux);
    p.inicializaDatos(datos);
    return i;
}

int SocketDatagrama::recibeTimeout(PaqueteDatagrama & p, time_t segundos, suseconds_t microsegundos){
    char datos[p.obtieneLongitud()];
    char aux[INET_ADDRSTRLEN];
    socklen_t clilen = sizeof(direccionForanea);

    struct timeval timeout;
    timeout.tv_sec = segundos;
    timeout.tv_usec = microsegundos;

    setsockopt (s, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));

    int n = recvfrom(s, datos, p.obtieneLongitud(), 0, (struct sockaddr *) &direccionForanea, &clilen);
    inet_ntop(AF_INET, &(direccionForanea.sin_addr), aux, INET_ADDRSTRLEN);
    p.inicializaPuerto(ntohs(direccionForanea.sin_port));
    p.inicializaIp(aux);
    p.inicializaDatos(datos);

    if (n < 0){
        if (errno == EWOULDBLOCK){
            fprintf (stderr, "Tiempo para recepcion transcurrido\n");
            return -1;
        }
        else
        {
            fprintf (stderr, "Error en recvfrom\n");
        }
    }
    return n;

}