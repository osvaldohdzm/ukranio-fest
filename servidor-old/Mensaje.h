#ifndef MENSAJE_H
#define MENSAJE_H

	#include "Header.h"
	#include <stdlib.h>

	class Mensaje{
		private:
			long source;			//Identidad del emisor
			long dest;				//Identidad del receptor
			long opcode;			//Operacion a realizar
			long count;				//Numero de bytes por transmitir
			long offset;			//Lugar del archivo donde comienza la lectura o escritura
			long extra1;			//Campo adicional 1
			long extra2;			//Campo adicional 2
			long result;			//Resultado de la operacion
			char name[MAX_PATH];	//Nombre del archivo en el cual se opera
			char data[BUF_SIZE];	//Datos por leer o escribir
		public:
			Mensaje();
			Mensaje( long, long, long, long, long, char *, char *);
			void setSource( long );
			void setDest( long );
			void setOpcode( long );
			void setCount( long );
			void setOffset( long );
			void setExtra1( long );
			void setExtra2( long );
			void setResult( long );
			void setName( char * );
			void setData( char * );
			long getSource();
			long getDest();
			long getOpcode();
			long getCount();
			long getOffset();
			long getExtra1();
			long getExtra2();
			long getResult();
			char *getName();
			char *getData();
			void imprimeMensaje();
						
	};

#endif
