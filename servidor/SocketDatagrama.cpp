#include "SocketDatagrama.h"
#include "PaqueteDatagrama.h"
#include "Mensaje.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

SocketDatagrama::SocketDatagrama( int puerto ){
	s = socket( AF_INET, SOCK_DGRAM, 0 );
	bzero( (char *)&direccionLocal, sizeof( direccionLocal ) );
	direccionLocal.sin_family = AF_INET;
	direccionLocal.sin_addr.s_addr = INADDR_ANY;
	direccionLocal.sin_port = htons( puerto );
	bind( s,(struct sockaddr *) &direccionLocal, sizeof( direccionLocal ) );
}

SocketDatagrama::SocketDatagrama() {
	s = socket( AF_INET, SOCK_DGRAM,0 );
	bzero( (char *)&direccionLocal,sizeof( direccionLocal ) );
	direccionLocal.sin_family = AF_INET;
	direccionLocal.sin_addr.s_addr = INADDR_ANY;
	direccionLocal.sin_port = htons( 0 );
	bind( s,(struct sockaddr *)&direccionLocal, sizeof( direccionLocal ) );
}

SocketDatagrama::~SocketDatagrama(){
	close( s );
}

int SocketDatagrama::recibe( PaqueteDatagrama &p ){
	socklen_t clilen = sizeof( direccionForanea );
	int r = recvfrom( s, (Mensaje *)p.getDatos(), p.getLongitud(), 0, (struct sockaddr *)&direccionForanea, &clilen );
	p.setIp( inet_ntoa( direccionForanea.sin_addr ) );
	p.setPuerto( ntohs( direccionForanea.sin_port ) );
	return r;
}

int SocketDatagrama::envia( PaqueteDatagrama &p ){
	direccionForanea.sin_family = AF_INET;
	direccionForanea.sin_addr.s_addr = inet_addr( p.getDireccion() );
	direccionForanea.sin_port = htons( p.getPuerto() );
	return sendto( s, (Mensaje *)p.getDatos(), p.getLongitud(), 0, (struct sockaddr *)&direccionForanea, 		sizeof( direccionForanea ) );
}


