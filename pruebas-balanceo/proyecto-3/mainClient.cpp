#define MG_ENABLE_HTTP_STREAMING_MULTIPART 1

#include "Solicitud.h"
#include "Registro.h"
#include "mongoose.h"

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <thread>
#include <vector>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sys/time.h>
#include <regex>
#include <bits/stdc++.h>





using namespace std;

static const char *s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;

struct file_writer_data {
  FILE *fp;
  size_t bytes_written;
};





//-------------------------------------------------- GRAMATICA----------------------------------------------------
static void removeAccented( std::string & str ) {
    std::stringstream result;
    std::regex filter("(á)+");
    std::regex_replace(std::ostream_iterator<char>(result), str.begin(), str.end(), filter, "a");
    str = result.str();

    std::stringstream result1;
    filter = std::regex("(é)+");
    std::regex_replace(std::ostream_iterator<char>(result1), str.begin(), str.end(), filter, "e");
    str = result1.str();

    std::stringstream result2;
    filter = std::regex("(í)+");
    std::regex_replace(std::ostream_iterator<char>(result2), str.begin(), str.end(), filter, "i");
    str = result2.str();

    std::stringstream result3;
    filter = std::regex("(ó)+");
    std::regex_replace(std::ostream_iterator<char>(result3), str.begin(), str.end(), filter, "o");
    str = result3.str();

    std::stringstream result4;
    filter = std::regex("(ú)+");
    std::regex_replace(std::ostream_iterator<char>(result4), str.begin(), str.end(), filter, "u");
    str = result4.str();

    std::stringstream result5;
    filter = std::regex("(Á)+");
    std::regex_replace(std::ostream_iterator<char>(result5), str.begin(), str.end(), filter, "a");
    str = result5.str();

    std::stringstream result6;
    filter = std::regex("(É)+");
    std::regex_replace(std::ostream_iterator<char>(result6), str.begin(), str.end(), filter, "e");
    str = result6.str();

    std::stringstream result7;
    filter = std::regex("(Í)+");
    std::regex_replace(std::ostream_iterator<char>(result7), str.begin(), str.end(), filter, "i");
    str = result7.str();

    std::stringstream result8;
    filter = std::regex("(Ó)+");
    std::regex_replace(std::ostream_iterator<char>(result8), str.begin(), str.end(), filter, "o");
    str = result8.str();

    std::stringstream result9;
    filter = std::regex("(Ú)+");
    std::regex_replace(std::ostream_iterator<char>(result9), str.begin(), str.end(), filter, "u");
    str = result9.str();

    std::stringstream result10;
    filter = std::regex("(ñ)+");
    std::regex_replace(std::ostream_iterator<char>(result10), str.begin(), str.end(), filter, "n");
    str = result10.str();

    std::stringstream result11;
    filter = std::regex("(Ñ)+");
    std::regex_replace(std::ostream_iterator<char>(result11), str.begin(), str.end(), filter, "n");
    str = result11.str();
}










//---------------------------------------------------------- HILOS --------------------------------------------
//fsync 13.8 segundos sin el 6.6 segundos
int check_malas[3];
void hilo1(string cad){
	char texto[cad.length() + 1]; 
	strcpy(texto, cad.c_str());
	int malas;
	Solicitud a;
	//struct mensaje * m =(struct mensaje *)a.doOperation("10.100.67.218", 7200, i, (char *)texto);
	//memcpy(&malas,m->arguments,sizeof(int));
	memcpy(&malas,a.doOperation("192.168.43.183",7200,3,(char*)&texto,1),sizeof(int));
	//cout << "regresa 1 " << malas << endl;
	check_malas[0] = malas;
	//cout << "regresa 1 " << check_malas[0] << endl;
	a.getSocket()->~SocketDatagrama();
	//pthread_exit(0);
}
void hilo2(string cad){
	char texto[cad.length() + 1]; 
	strcpy(texto, cad.c_str());
	int malas;
	Solicitud a;
	//struct mensaje * m =(struct mensaje *)a.doOperation("10.100.67.218", 7200, i, (char *)texto);
	//memcpy(&malas,m->arguments,sizeof(int));
	memcpy(&malas,a.doOperation("192.168.43.15",7200,3,(char*)&texto,1),sizeof(int));
	
	check_malas[1] = malas;
	//cout << "regresa 2 " << check_malas[1] << endl;
	a.getSocket()->~SocketDatagrama();
	//pthread_exit(0);
}

void hilo3(string cad){
	char texto[cad.length() + 1]; 
	strcpy(texto, cad.c_str());
	int malas;
	Solicitud a;
	//struct mensaje * m =(struct mensaje *)a.doOperation("10.100.67.218", 7200, i, (char *)texto);
	//memcpy(&malas,m->arguments,sizeof(int));
	memcpy(&malas,a.doOperation("192.168.43.30",7200,3,(char*)&texto,1),sizeof(int));
	
	check_malas[2] = malas;
	//cout << "regresa 3 " << check_malas[2] << endl;
	a.getSocket()->~SocketDatagrama();
	//pthread_exit(0);
}

void hilo_m(){
  std::ifstream ifs;
    // std::vector<std::string> vec;
    std::string word;
    timeval actual{}, final{};
    vector<string> archivo;
    ifs.open("file.txt");
    int cont =0;
    while (ifs >> word) {
        // filtrar puntuacines y numeros
        const std::regex filter("([^A-zÁÉÍÓÚÑáéíóúñ])+");
        //std::cout << "word antes es " << word << endl;
        std::stringstream result;
        std::regex_replace(std::ostream_iterator<char>(result), word.begin(), word.end(), filter, "");

        word = result.str();

        // Transformar tildes a normales
        removeAccented(word);

        // tranforma a minusculas
        std::transform(word.begin(), word.end(), word.begin(),
                       [](unsigned char c) { return std::tolower(c); });


        //std::cout << word << std::endl;
        archivo.push_back(word);
        cont++;
        //if(cont == 1000) break;
        if(word=="theend")break;
    }
    cout << archivo.size() << endl;

	int no_comprendidas=0;
	vector<string> palabras;
	vector<thread> hilos;
	int indice = 0;
	//string words[] = {"hola", "casa","nada","perro","hola"};
	for(string s : archivo){
		palabras.push_back(s);
		// if(indice == 0)
		// 	hilos.push_back(thread(hilo1, palabras[0]));
		// else if(indice == 1)
		// 	hilos.push_back(thread(hilo2, palabras[1]));
		// else
		// 	hilos.push_back(thread(hilo3, palabras[2]));
		if(palabras.size() == 3){
			//correr los tres hilos      
			hilos.push_back(thread(hilo1, palabras[0]));
			hilos.push_back(thread(hilo2, palabras[1]));
			hilos.push_back(thread(hilo3, palabras[2]));
			for(int i =0; i < 3; i++){
				hilos[i].join();
			}
			vector<string> pendientes;
			for(int i =0; i < 3;i++){
				//cout << "check_malas para " << i+1 << " es de  " << check_malas[i] << endl;
				if(check_malas[i] != -1){
					no_comprendidas += (check_malas[i] == 0) ? 1 : 0;
				}
				else
					pendientes.push_back(palabras[i]);
			}
			palabras.clear();
			for(string xx: pendientes){
				palabras.push_back(xx);
			}
			hilos.clear();
		}
		indice++;
		indice%=3;
	}
	if(palabras.size() > 0){
		cout << "Comprension: " << palabras.size() << endl;
	}

}

static void handle_upload(struct mg_connection *nc, int ev, void *p) {
  struct file_writer_data *data = (struct file_writer_data *) nc->user_data;
  struct mg_http_multipart_part *mp = (struct mg_http_multipart_part *) p;

  switch (ev) {
    case MG_EV_HTTP_PART_BEGIN: {
      if (data == NULL) {
        data = (struct file_writer_data *)calloc(1, sizeof(struct file_writer_data));
        data->fp = fopen("file.txt","wb");
        data->bytes_written = 0;

        if (data->fp == NULL) {
          mg_printf(nc, "%s",
                    "HTTP/1.1 500 Failed to open a file\r\n"
                    "Content-Length: 0\r\n\r\n");
          nc->flags |= MG_F_SEND_AND_CLOSE;
          free(data);
          return;
        }
        nc->user_data = (void *) data;
        cout << "Iniciando carga..." << endl;
      }
      break;
    }
    case MG_EV_HTTP_PART_DATA: {
    	//FILE * fp = fopen("file.txt","wb");
      	if (fwrite(mp->data.p, 1, mp->data.len, data->fp) != mp->data.len) {
       	 	mg_printf(nc, "%s",
                  "HTTP/1.1 500 Failed to write to a file\r\n"
                  "Content-Length: 0\r\n\r\n");
        	nc->flags |= MG_F_SEND_AND_CLOSE;
        	return;
      	}
      	data->bytes_written += mp->data.len;
        cout << "Subiendo archivo..." << endl;
      break;
    }
    case MG_EV_HTTP_PART_END: {
      mg_printf(nc,
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/plain\r\n"
                "Connection: close\r\n\r\n"
                "Written %ld of POST data to a temp file\n\n",
                (long) ftell(data->fp));
      nc->flags |= MG_F_SEND_AND_CLOSE;
      fclose(data->fp);
      free(data);
      nc->user_data = NULL;
      cout << "Archivo recibido. Escrito en file.txt" << endl;
      hilo_m();
      break;
      //std::thread t1{std::bind(hilo_m)};
      
    }
  }

  
}

static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
  if (ev == MG_EV_HTTP_REQUEST) {
    mg_serve_http(nc, (struct http_message *)ev_data, s_http_server_opts);
  }
}



int main(int argc, char *argv[]){

  struct mg_mgr mgr;
  struct mg_connection *c;

  mg_mgr_init(&mgr, NULL);
  c = mg_bind(&mgr, s_http_port, ev_handler);
  if (c == NULL) {
    fprintf(stderr, "Cannot start server on port %s\n", s_http_port);
    exit(EXIT_FAILURE);
  }

  s_http_server_opts.document_root = "www/";  // Serve current directory
  mg_register_http_endpoint(c, "/upload", handle_upload MG_UD_ARG(NULL));

  // Set up HTTP server parameters
  mg_set_protocol_http_websocket(c);

  printf("Servidor web iniciado en http://localhost:%s\n", s_http_port);
  for (;;) {
    mg_mgr_poll(&mgr, 1000);
  }
  mg_mgr_free(&mgr);



/*
	std::ifstream ifs;
    // std::vector<std::string> vec;
    std::string word;
    timeval actual{}, final{};
    vector<string> archivo;
    ifs.open("file.txt");
    int cont =0;
    while (ifs >> word) {
        // filtrar puntuacines y numeros
        const std::regex filter("([^A-zÁÉÍÓÚÑáéíóúñ])+");
        //std::cout << "word antes es " << word << endl;
        std::stringstream result;
        std::regex_replace(std::ostream_iterator<char>(result), word.begin(), word.end(), filter, "");

        word = result.str();

        // Transformar tildes a normales
        removeAccented(word);

        // tranforma a minusculas
        std::transform(word.begin(), word.end(), word.begin(),
                       [](unsigned char c) { return std::tolower(c); });


        //std::cout << word << std::endl;
        archivo.push_back(word);
        cont++;
        //if(cont == 1000) break;
        if(word=="theend")break;
    }
    cout << archivo.size() << endl;

	int no_comprendidas=0;
	vector<string> palabras;
	vector<thread> hilos;
	int indice = 0;
	//string words[] = {"hola", "casa","nada","perro","hola"};
	for(string s : archivo){
		palabras.push_back(s);
		// if(indice == 0)
		// 	hilos.push_back(thread(hilo1, palabras[0]));
		// else if(indice == 1)
		// 	hilos.push_back(thread(hilo2, palabras[1]));
		// else
		// 	hilos.push_back(thread(hilo3, palabras[2]));
		if(palabras.size() == 3){
			//correr los tres hilos      
			hilos.push_back(thread(hilo1, palabras[0]));
			hilos.push_back(thread(hilo2, palabras[1]));
			hilos.push_back(thread(hilo3, palabras[2]));
			for(int i =0; i < 3; i++){
				hilos[i].join();
			}
			vector<string> pendientes;
			for(int i =0; i < 3;i++){
				//cout << "check_malas para " << i+1 << " es de  " << check_malas[i] << endl;
				if(check_malas[i] != -1){
					no_comprendidas += (check_malas[i] == 0) ? 1 : 0;
				}
				else
					pendientes.push_back(palabras[i]);
			}
			palabras.clear();
			for(string xx: pendientes){
				palabras.push_back(xx);
			}
			hilos.clear();
		}
		indice++;
		indice%=3;
	}
	if(palabras.size() > 0){
		cout << "quedaron " << palabras.size() << endl;
	}
*/
    return 0;
}

