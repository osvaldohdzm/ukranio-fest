#include "Respuesta.h"
#include "Registro.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <functional>
#include <array>
#include <bits/stdc++.h> 

using namespace std; 

static const int TAM_DATOS = 31;


using namespace std;

int main(int argc, char* argv[]){
    // abre el archivo con las palabras comunes
    // recibe una palabra y la checa
    // retorna un int dependiendo si la encontro o nel

    std::ifstream ifs("sortDic.txt");

    std::vector<std::string> vec;
    std::string palabra;

    while (ifs >> palabra) {
        vec.push_back(palabra);
    }

    Respuesta r(7200);
    struct mensaje m;
    char datos[TAM_DATOS];

    while(true) {
        //m = r.getRequest();

        memcpy(&m,(r.getRequest()),sizeof(mensaje));
        memset(datos, 0, TAM_DATOS);
        memcpy(datos, m.arguments, sizeof(char) * TAM_DATOS);

        //printf("datos: %s\n", datos);

        bool found = std::binary_search(vec.begin(), vec.end(), datos);

        int reply = found ? 1 : 0 ;
        r.sendReply((char *)&reply);
    }   
    
    return 0;
}
