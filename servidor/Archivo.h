#ifndef ARCHIVO_H_
#define ARCHIVO_H_

#include <iostream>
using namespace std;
class Archivo{
	public:
		Archivo();
		Archivo( int );
		int openFile( char *, int );
		void readFile( void* );
		void writeFile( void*, int );
		void closeFiles();
		int obtieneFileDescriptor();
		int obtieneNBytes();
		char* obtieneNombre();
		void setNbytes( int );
		void setNombreArchivo( char * );
	private:
		int nbytes;
		int fileDescriptor;
		char* nombreArchivo;
};

#endif
