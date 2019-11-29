#ifndef HEADER_H
#define HEADER_H

   #define MAX_PATH      255        //Longitud maxima del nombre del archivo
	#define BUF_SIZE      1024 		//Cantidad de datos que se transmiten a la vez
	#define FILE_SERVER   243  		//Direccion en la red del servidor de archivos 
	#define CREATE 	    1    		//Crea un nuevo archivo
	#define READ 	       2	  			//Lee una parte del archivo y la regresa
	#define WRITE 	       3	  			//Escribe una parte de un archivo
	#define DELETE 	    4 	  		//Elimina un archivo existente
	#define RENAME			 5				//Renombra un archivo existente
	#define LIST			 6				//Lista los archivos de un Path
	#define OK 	          0	  			//Operacion desarrollada en forma correcta
	#define E_BAD_OPCODE  -1   		//Solicitud de una operacion desconocida
	#define E_BAD_PARAM 	 -2   		//Error en un parametro
	#define E_IO     	    -3	      //Error en disco u error en E/S
 	#define BAD_OPERATION -4	      //Operacion desarrollada en forma incorrecta
	#define PORT_CLIENT 7200			//Puerto del cliente
	#define PORT_SERV 7300				//Puerto del servidor
	#define PORT_MAX 65535				//Numero limite de puerto
	#define PORT_MIN 1024				//Numero minimo de puerto
	#define LOCALHOST "127.0.0.1"		//IP del servidor cuando esta en la misma maquina
	#define IP_SERV "10.100.68.213"  //IP del servidor cuando esta en otra maquina
	#define LEN_IP 16						//Longitud de la IP	
	#define SOL    5

#endif
