cliente: server.cpp PaqueteDatagrama.o
	g++ server.cpp mongoose.c PaqueteDatagrama.o SocketDatagrama.o -o servidor
PaqueteDatagrama.o: PaqueteDatagrama.cpp SocketDatagrama.o PaqueteDatagrama.h
	g++ PaqueteDatagrama.cpp -c
SocketDatagrama.o: SocketDatagrama.cpp SocketDatagrama.h
	g++ SocketDatagrama.cpp -c
clean:
	rm -rf *.o 
	rm -rf server
