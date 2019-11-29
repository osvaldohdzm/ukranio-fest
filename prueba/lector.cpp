
//#include "Solicitud.h"
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include<locale.h>


using namespace std;


struct Node{
    string data;
    Node* left;
    Node* right;
};

Node* GetNewNode(string data){
    Node* newNode = new Node();
    newNode->data=data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* Insert(Node* rootPtr,string data){
    if(rootPtr == NULL){
        rootPtr = GetNewNode(data);
        return rootPtr;
    }
    else if(data<= rootPtr->data){
        rootPtr->left = Insert(rootPtr->left,data);
    }
    else {
        rootPtr->right = Insert(rootPtr->right,data);
    }
    return rootPtr;
}

int isSubstring(string s1, string s2) 
{ 
    int M = s1.length(); 
    int N = s2.length(); 
  
    /* A loop to slide pat[] one by one */
    for (int i = 0; i <= N - M; i++) { 
        int j; 
  
        /* For current index i, check for pattern match */
        for (j = 0; j < M; j++) 
            if (s2[i + j] != s1[j]) 
                break; 
  
        if (j == M) 
            return i; 
    } 
  
    return -1; 
} 

string removeSpecialCharacter(string s) 
{ 
    for (int i = 0; i < s.size(); i++) { 
         if (s[i] >= '!' && s[i] <= '?')  
        {
            s.erase(i,1);
            i--; 
        }else if (s[i]=='HT'){
            s.erase(i,1);
            i--; 
        }else if (s[i]==168){
            s.erase(i,1);
            i--; 
        }

    } 
    return s; 
} 

int compare(Node *p, string word, int start)
    {
        if (p->right != NULL)
        {
            start=compare(p->right,word, start);
        }
        if(p->data=="él"){
        	int cont=1;
        	return cont;
        }
        /*
        ofstream output;
        output.open("registros.txt", ios::out | ios::app );
        output.write(p->data.c_str(), p->data.length());
        output.write("\n",1);
        output.flush();
        if(isSubstring(word,p->data)!=-1){
        	cout<<"encontre una palabra"<<endl;
        	start++;
        }*/
        if (p->left != NULL)
        {
            start=compare(p->left,word, start);
        }
        return start;
    }



int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "spanish");
	if (argc != 3)
	{
		printf("Forma de uso: %s ip_servidor nombre_de_archivo\n");
		exit(0);
	}
	int cont = 0;
	Node* rootPtr = NULL;
	string line;
	string line2;
	std::ifstream infile("formas.txt");
	std::ifstream infile2("prueba.txt");
	while (getline(infile, line))
	{
		//Solicitud s;
		line=removeSpecialCharacter(line);
		rootPtr = Insert(rootPtr, line);
		char *cstr = new char[line.length() + 1];
		strcpy(cstr, line.c_str());
		//cout<<cstr<<endl;
		//memcpy(&res, s.doOperation(argv[1], 7200, 1,cstr),4);
		//if(res==1){
		//	cout<<"Acuse recibido"<<endl;
		//}else{
		//	cout<<"Error en recepcion"<<endl;
		//}
	}
	
	cout<<compare(rootPtr,line,cont)<<endl;

    /*
	while (getline(infile2, line2))
	{
		compare(rootPtr,line2,cont);
		//Solicitud s;
		
		//cout<<cstr<<endl;
		//memcpy(&res, s.doOperation(argv[1], 7200, 1,cstr),4);
		//if(res==1){
		//	cout<<"Acuse recibido"<<endl;
		//}else{
		//	cout<<"Error en recepcion"<<endl;
		//}
	}
	cout<<cont<<endl;*/
	return 0;
}