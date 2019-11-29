#ifndef PAQUETE_DATAGRAMA_H_
#define PAQUETE_DATAGRAMA_H_

	#include "Mensaje.h"

class PaqueteDatagrama{
	public:
		PaqueteDatagrama( Mensaje *, unsigned int, char * , int );
		PaqueteDatagrama( unsigned int );
		~PaqueteDatagrama();

		char* getDireccion();
		Mensaje* getDatos();
		int getPuerto();
		unsigned int getLongitud();
		void setLongitud( unsigned int );
		void setPuerto( int );
		void setIp( char * );
		void setDatos(Mensaje *);

	private:
		//char* datos;
		Mensaje *datos;
		char ip[16];
		unsigned int longitud;
		int puerto;
};

#endif
