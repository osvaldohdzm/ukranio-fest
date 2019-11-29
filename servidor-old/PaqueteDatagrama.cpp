#include "PaqueteDatagrama.h"
#include "Mensaje.h"
#include <string.h>
#include <iostream>

using namespace std;

PaqueteDatagrama::PaqueteDatagrama( Mensaje* datos, unsigned int longitud, char* ip, int puerto ){
	this->datos = datos;
	this->longitud = longitud;
	memcpy( this->ip, ip, sizeof(char)*16 );
	this->puerto = puerto;
}

PaqueteDatagrama::PaqueteDatagrama( unsigned int longitud ){
	this->datos = new Mensaje();
	this->longitud = longitud;
}

PaqueteDatagrama::~PaqueteDatagrama(){
	//delete []datos;
}

char* PaqueteDatagrama::getDireccion(){
	return ip;
}

Mensaje * PaqueteDatagrama::getDatos(){
	return datos;
}

int PaqueteDatagrama::getPuerto(){
	return puerto;
}

unsigned int PaqueteDatagrama::getLongitud(){
	return longitud;
}

void PaqueteDatagrama::setPuerto( int puerto ){
	this->puerto = puerto;
}

void PaqueteDatagrama::setLongitud( unsigned int longitud ){
	this->longitud = longitud;
}

void PaqueteDatagrama::setIp( char *ip ){
	memcpy( this->ip, ip, sizeof(char)*16 );
}

void PaqueteDatagrama::setDatos( Mensaje *datos ){
	//memcpy(datos, data, longitud);
	memcpy( this->datos, datos, this->longitud );
	//this->datos = datos;
}


