#include "algoritmos_busca.hpp"
#include <iostream>

using namespace std;

int tamanho_string(const char* t){
    int n = 0;
    while(t[n] != '\0') n++;

    return n;
}


void forca_bruta(const char* p, const char* t, int* o){ 
    int j;
    int cont = 0;
    
    int n = tamanho_string(t);
    int m = tamanho_string(p);

    
    for(int i = 0; i <= n-m; i++){
        
        for(j = 0; j < n; j++){
            if (t[i+j] != p[j]) break;
        }

       if(j == m) o[cont++] = i;
    }

    o[cont] = -1;
}