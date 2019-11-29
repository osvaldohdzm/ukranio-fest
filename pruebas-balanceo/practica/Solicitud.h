#ifndef __SOLICITUD__
#define __SOLICITUD__

#include "SocketDatagrama.h"
#include "PaqueteDatagrama.h"
#include "Mensaje.h"
#include <cstdio>
#include <cstdlib>

class Solicitud {
public:
    
    char *doOperation(char *IP, int puerto, int operationId, char *arguments);
    Solicitud();
private:
	struct mensaje msj_databack;
    SocketDatagrama socketlocal;
    int modificador;
    //int rec;
};
#endif