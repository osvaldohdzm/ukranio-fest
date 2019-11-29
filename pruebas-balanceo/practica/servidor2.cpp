#include "Mensaje.h"
#include "Respuesta.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <sys/time.h>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

/*VECTOR CON REGISTRO DE NÚMEROS RECIBIDOS*/
vector<long> registrosRecibidos;

struct registro{
    char celular[11];
    char CURP[19];
    char partido[4];
};


/*****************************************************************/

const int ALPHABET_SIZE = 26; 
  
// trie node 
struct TrieNode 
{ 
    struct TrieNode *children[ALPHABET_SIZE]; 
  
    // isEndOfWord is true if the node represents 
    // end of a word 
    bool isEndOfWord; 
}; 
  
// Returns new trie node (initialized to NULLs) 
struct TrieNode *getNode(void) 
{ 
    struct TrieNode *pNode =  new TrieNode; 
  
    pNode->isEndOfWord = false; 
  
    for (int i = 0; i < ALPHABET_SIZE; i++) 
        pNode->children[i] = NULL; 
  
    return pNode; 
} 
  
// If not present, inserts key into trie 
// If the key is prefix of trie node, just 
// marks leaf node 
void insert(struct TrieNode *root, string key) 
{ 
    struct TrieNode *pCrawl = root; 
  
    for (int i = 0; i < key.length(); i++) 
    { 
        int index = key[i] - 'a'; 
        if (!pCrawl->children[index]) 
            pCrawl->children[index] = getNode(); 
  
        pCrawl = pCrawl->children[index]; 
    } 
  
    // mark last node as leaf 
    pCrawl->isEndOfWord = true; 
} 
  
// Returns true if key presents in trie, else 
// false 
bool search(struct TrieNode *root, string key) 
{ 
    struct TrieNode *pCrawl = root; 
  
    for (int i = 0; i < key.length(); i++) 
    { 
        int index = key[i] - 'a'; 
        if (!pCrawl->children[index]) 
            return false; 
  
        pCrawl = pCrawl->children[index]; 
    } 
  
    return (pCrawl != NULL && pCrawl->isEndOfWord); 
} 
  
 /*******************************************************************/

int main(int argc, char*argv[]) {
  Respuesta respuesta(1415);

  int dest;

  if(argc<2){
    printf("Forma de uso: ./servidor nombre_del_archivo_destino.txt\n");
    exit(-1);
  }
  if((dest = open(argv[1],  O_WRONLY | O_APPEND | O_CREAT)) == -1){
    perror(argv[1]);
    exit(-1);

  }

/*************/
 // Input keys (use only 'a' through 'z' 
    // and lower case) 
    string keys[] = {"the", "a", "there", 
                    "answer", "any", "by", 
                     "bye", "their" }; 
    int n = sizeof(keys)/sizeof(keys[0]); 
  
    struct TrieNode *root = getNode(); 
  
    // Construct trie 
    for (int i = 0; i < n; i++) 
        insert(root, keys[i]); 
  
    // Search for different keys 
    search(root, "the")? cout << "Yes\n": 
                         cout << "No\n"; 
    search(root, "these")? cout << "Yes\n" : 
                           cout << "No\n"; 

/************/



  while(true) {
    struct mensaje msg; //creamos estructura para guardar respuesta
    struct timeval tiempo; //estructuras para calcular el tiempo
    struct registro regrec; //estructura registro para guardar lo que recib
    char cadenaTiempo[20];

    gettimeofday(&tiempo, NULL);   // Instante inicial
    memcpy(&msg, respuesta.getRequest(), sizeof(struct mensaje)); //recibo el mensaje de solicitud y lo guardo en msg
    
    sprintf (cadenaTiempo, "%ld,%ld ", tiempo.tv_sec, tiempo.tv_usec);
    
    memcpy(&regrec, msg.arguments, sizeof(regrec)); //almacena los argumentos
  
    long numero = strtol(regrec.celular,NULL,10);

    printf("\n");
    printf("El registro recibido es: \n");
    write(1, &regrec, sizeof(regrec)); //imprime en pantalla
    printf("\nNumero de registro : %ld\n",numero );






    if(binary_search(registrosRecibidos.begin(), registrosRecibidos.end(), numero)){
      /*SI YA EXISTE EL NUMERO EN EL VECTOR*/
      printf("numero repetido\n");
      /*se envia la cadena en ceros*/
      memcpy(msg.arguments, "0,0", 20);//almanceno en msg la respuesta del servdor
      respuesta.sendReply(msg.arguments); //envio respuesta al cliente

    }else{
      /*SÍ AÚN NO HA SIDO REGISTRADO EL NÚMERO*/
      registrosRecibidos.push_back(numero);
      /*SE ESCRIBE EN EL ARCHIVO*/
      write(dest, &regrec, sizeof(regrec)); //imprimir en archivo

      printf("Tiempo de registro: %s\n", cadenaTiempo);
      /*SE MANDA EL TIEMPO DE GETTIMEOFDAY*/
      memcpy(msg.arguments, cadenaTiempo, 20);//almanceno en msg la respuesta del servdor
      respuesta.sendReply(msg.arguments); //envio respuesta al cliente
    }    

   
 }
  close(dest);
}

