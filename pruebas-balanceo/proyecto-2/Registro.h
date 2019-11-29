#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream> 
#include <list> 
#include <iterator> 

using namespace std; 

struct registro{
	char celular[11];
	char CURP[19];
	char partido[4];
	char timestamp[11];
};