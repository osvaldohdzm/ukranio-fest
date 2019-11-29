run: compile
compile: cliente2.o servidor2.o Paquetedatagrama.o SocketDatagrama.o Solicitud.o Respuesta.o
	g++ SocketDatagrama.o Solicitud.o PaqueteDatagrama.o cliente2.o -o cliente2 -std=c++11
	g++ SocketDatagrama.o Respuesta.o PaqueteDatagrama.o servidor2.o -o servidor2 -std=c++11
servidor2.o: 
	g++ -c servidor2.cpp -Wall
cliente2.o: 
	g++ -c cliente2.cpp 
Paquetedatagrama.o: 
	g++ -c PaqueteDatagrama.cpp 
SocketDatagrama.o: 
	g++ -c SocketDatagrama.cpp 
Solicitud.o: 
	gcc -c Solicitud.cpp
Respuesta.o: 
	gcc -c Respuesta.cpp
clean:
	rm -rf *.o 
	rm -rf servidor2
	rm -rf cliente2
