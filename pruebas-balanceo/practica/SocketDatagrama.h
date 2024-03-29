#ifndef __SOCKET_DATAGRAMA__
#define __SOCKET_DATAGRAMA__
#include "PaqueteDatagrama.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string>
#include <unistd.h>

using namespace std;

class SocketDatagrama {
public:
    SocketDatagrama(int);
    SocketDatagrama();
    ~SocketDatagrama();
    // Recibe un paquete tipo datagrama proveniente de este socket
    int recibe(PaqueteDatagrama &p);
    // Envia un paquete tipo datagrama desde este socket
    int envia(PaqueteDatagrama &p);
    int recibeTimeout(PaqueteDatagrama & p, time_t segundos, suseconds_t microsegundos);

private:
    struct sockaddr_in direccionLocal;
    struct sockaddr_in direccionForanea;
    int s; // ID socket

    
};
#endif
