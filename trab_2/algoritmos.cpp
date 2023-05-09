#include "algoritmos.hpp"

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

    for(int i = 0; i <= m-n; i++){
        
        for(j = 0; j < n; j++){
            if (t[i+j] != p[j]) break;
        }

        if(j == n) o[cont++] = i;
    }

}