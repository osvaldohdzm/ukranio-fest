#include "Archivo.h"
#include "Header.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


Archivo::Archivo( int a ){
	this->nombreArchivo = new char[MAX_PATH];
    fileDescriptor = a; 
}

int Archivo::openFile( char* nombre, int op_code ){
    int r = 0;
    printf("Open %s\n",nombre);
    if(op_code == 2)
        fileDescriptor = open(nombre, O_RDONLY);
    else
        fileDescriptor = open(nombre, O_WRONLY|O_TRUNC|O_CREAT,0666);

    if(fileDescriptor == -1)
        r = -3;
    else
        nombreArchivo = nombre;
    return r;
}

void Archivo::closeFiles(){
    close(fileDescriptor);
}

void Archivo::readFile( void* buffer ){ 
    nbytes = read( fileDescriptor, buffer, BUF_SIZE );
}

void Archivo::writeFile( void* buffer, int d ){
    //printf("Data: %s %d\n", (char *)buffer, d);
    size_t bytes = write(fileDescriptor, buffer, d);
}

int Archivo::obtieneFileDescriptor(){
    return fileDescriptor;
}

int Archivo::obtieneNBytes(){
    return nbytes;
}

char* Archivo::obtieneNombre(){
    return nombreArchivo;
}

void Archivo::setNbytes( int nbytes ){
	this->nbytes = nbytes;
}

void Archivo::setNombreArchivo( char * nombreArchivo ){
	strcpy( this->nombreArchivo , nombreArchivo );
}
	



