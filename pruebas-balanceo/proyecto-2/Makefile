all: Servidor Cliente

Servidor: SocketDatagrama.o PaqueteDatagrama.o Respuesta.o mainServer.cpp Registro.h
		g++ -std=c++11 mainServer.cpp SocketDatagrama.o PaqueteDatagrama.o Respuesta.o -o mainServer

Cliente: SocketDatagrama.o PaqueteDatagrama.o Respuesta.o Solicitud.o mainClient.cpp Registro.h
		g++ -DMG_ENABLE_HTTP_STREAMING_MULTIPART -std=c++11 mainClient.cpp mongoose.c SocketDatagrama.o PaqueteDatagrama.o Solicitud.o Respuesta.o -w -o mainClient -lpthread

SocketDatagrama.o: SocketDatagrama.cpp SocketDatagrama.h
		g++ SocketDatagrama.cpp -c

PaqueteDatagrama.o: PaqueteDatagrama.cpp PaqueteDatagrama.h
		g++ PaqueteDatagrama.cpp -c

Respuesta.o: Respuesta.cpp Respuesta.h
		g++ Respuesta.cpp -c

Solicitud.o: Solicitud.cpp Solicitud.h
		g++ Solicitud.cpp -c
clean:
	rm -rf *.o 
	rm -rf mainClient
	rm -rf mainServer
