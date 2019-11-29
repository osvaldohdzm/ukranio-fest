server3: server.cpp SocketDatagrama.o PaqueteDatagrama.o  Archivo.o
	g++ -std=c++11 server.cpp SocketDatagrama.o PaqueteDatagrama.o Mensaje.h mongoose.cpp Archivo.o Mensaje.o -o server3
SocketDatagrama.o: SocketDatagrama.cpp PaqueteDatagrama.o SocketDatagrama.h
	g++  -std=c++11 SocketDatagrama.cpp -c
PaqueteDatagrama.o: PaqueteDatagrama.cpp PaqueteDatagrama.h Mensaje.o
	g++ -std=c++11 PaqueteDatagrama.cpp -c
Archivo.o: Archivo.cpp Archivo.h Header.h
	g++ -std=c++11 Archivo.cpp -c
Mensaje.o: Mensaje.cpp Mensaje.h
	g++ -std=c++11 Mensaje.cpp -c
clean:
	rm -rf *.o 
	rm -rf server
