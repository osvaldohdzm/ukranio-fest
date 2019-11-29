run: servidorWeb.cpp
	g++ -DMG_ENABLE_HTTP_STREAMING_MULTIPART servidorWeb.cpp mongoose.c -w -o servidorWeb
servidor-esclavo: servidor-esclavo.cpp
	g++ servidor-esclavo.cpp -c
clean:
	rm -r *.o
