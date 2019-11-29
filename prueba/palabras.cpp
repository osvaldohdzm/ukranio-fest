#include<bits/stdc++.h>
using namespace std;

int main() {
	std::ifstream file("input.txt");
  	std::string str;
  	while (std::getline(file, str)) {
    	//std::cout << str << "\n";
    	for(int i = 0; i < str.size(); i++) {
    		if(str[i] == '.') {
    			string aux = "";
    			int j = i + 1;
    			while(str[j] != ' ') {
    				aux += str[j];
    				j++; 
    			}
    			cout << aux << endl;
    			break;
    		}
    	}
  	}
}