#define MG_ENABLE_HTTP_STREAMING_MULTIPART 1
#include "mongoose.h"
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>
#include <string>
#include <time.h> 
#include <unistd.h>
#include "Header.h"
#include "Archivo.h"
#include "Mensaje.h"
#include "SocketDatagrama.h"
#define IP_PROTOCOL 0 
#define PUERTO 7201 
#define NET_BUF_SIZE 32 
#define cipherKey 'S' 
#define sendrecvflag 0 
#define nofile "File Not Found!"
using namespace std;
char buffer[BUF_SIZE];

static const char *s_http_port = "8889";
static struct mg_serve_http_opts s_http_server_opts;
void enviaArchivos(char* ipServidor,char* archivo);
int sendFile(FILE* fp, char* buf, int s);
char Cipher(char ch);
void clearBuf(char* b);

static void ev_handler(struct mg_connection *nc, int ev, void *p) {
	char query[256];
	char cm[1000];
 	struct http_message *hm = (struct http_message *) p;
	if (ev == MG_EV_HTTP_REQUEST) {
		if (mg_vcmp(&hm->uri, "/search") == 0) { 
			mg_get_http_var(&hm->body, "query", query,sizeof(query));
			printf("Archivo introducido: %s\n",query);
			enviaArchivos("127.0.0.1",query);
		}else{
			mg_serve_http(nc, (struct http_message *) p, s_http_server_opts);
		}
	}

}

void clearBuf(char* b) 
{ 
    int i; 
    for (i = 0; i < NET_BUF_SIZE; i++) 
        b[i] = '\0'; 
} 

// funtion to encrypt 
char Cipher(char ch) 
{ 
    return ch ^ cipherKey; 
}

int main(int arg,char *argv[]) {
	struct mg_mgr mgr;
	struct mg_connection *nc;
	mg_mgr_init(&mgr, NULL);
	printf("Iniciando servidor en puerto: %s\n", s_http_port);
		nc = mg_bind(&mgr, s_http_port, ev_handler);
	if (nc == NULL) {
		printf("Hubo en error con un listener: \n");
		return 1;
	}
	// Set up HTTP server parameters
	mg_set_protocol_http_websocket(nc);
	s_http_server_opts.document_root = "www"; // Serve current directory
	s_http_server_opts.enable_directory_listing = "yes";
	for (;;) {
		mg_mgr_poll(&mgr, 1000);
	}
	mg_mgr_free(&mgr);
	return 0;
}

void enviaArchivos(char* ipServidor,char* archivoF){
	char *ip = (char *)malloc( LEN_IP*sizeof(char) );
	char *nameFile = (char *)malloc( MAX_PATH*sizeof(char) );
	cout<<archivoF<<endl;
	strcpy( ip , ipServidor );
	strcpy( nameFile, archivoF );
	Mensaje *mensajeEntrada;
	Mensaje mensajeSalida= Mensaje();
    int r;
    SocketDatagrama socketDatagrama(0);
    Archivo archivo(0);
    long position = 0;
    PaqueteDatagrama paqueteEnviar( sizeof(Mensaje) );
    paqueteEnviar.setIp( ip );
    paqueteEnviar.setPuerto( PORT_SERV );
	archivo.openFile( nameFile, 3 );
        do{/*
        	cout<<"entre"<<endl;
        	ofstream output;
        	output.open(namefile, ios::out | ios::app );
        	output.write()
*/

            if(position > 0)
                mensajeSalida.setOpcode( WRITE );
            else
                mensajeSalida.setOpcode(CREATE);

            mensajeSalida.setOffset( position );
            archivo.readFile( buffer );
            
            if( archivo.obtieneNBytes() > 0 ){
						mensajeSalida.setName( archivoF );
						mensajeSalida.setData( buffer );
            } else{
                archivo.closeFiles();
            }
            mensajeSalida.setCount( archivo.obtieneNBytes() );
            paqueteEnviar.setDatos( (Mensaje *)&mensajeSalida );    
            socketDatagrama.envia( paqueteEnviar );
            position += archivo.obtieneNBytes();
            PaqueteDatagrama paqueteRecibido( sizeof(Mensaje) );
            socketDatagrama.recibe( paqueteRecibido );
        }while( mensajeSalida.getCount() > 0 ); 
}
