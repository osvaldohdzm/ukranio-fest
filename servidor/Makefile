server3: server.cpp SocketDatagrama.o PaqueteDatagrama.o  Archivo.o
	g++ server.cpp SocketDatagrama.o PaqueteDatagrama.o Mensaje.h mongoose.cpp Archivo.o Mensaje.o -o server3
SocketDatagrama.o: SocketDatagrama.cpp PaqueteDatagrama.o SocketDatagrama.h
	g++ SocketDatagrama.cpp -c
PaqueteDatagrama.o: PaqueteDatagrama.cpp PaqueteDatagrama.h Mensaje.o
	g++ PaqueteDatagrama.cpp -c
Archivo.o: Archivo.cpp Archivo.h Header.h
	g++ Archivo.cpp -c
Mensaje.o: Mensaje.cpp Mensaje.h
	g++ Mensaje.cpp -c
clean:
	rm -rf *.o 
	rm -rf server
