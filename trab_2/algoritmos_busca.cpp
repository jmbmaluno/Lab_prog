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

void preprocessamento_kmp(const char* p, int* prefix_padrao){
    int m = tamanho_string(p);
    int tamanho = 0;
    prefix_padrao[0] = 0;
    int i = 1;

    while( i < m){
        if(p[i] == p[tamanho]){
            tamanho++;
            prefix_padrao[i] = tamanho;
            i++;
        }
        else{
            if(tamanho != 0){
                tamanho = prefix_padrao[tamanho-1];
            }
            else{
                prefix_padrao[i] = 0;
                i++;
            }
        }
    }
}

void kmp(const char* p, const char* t){
    int m = tamanho_string(p);
    int n = tamanho_string(t);

    int prefix_padrao[m];

    preprocessamento_kmp(p,prefix_padrao);

    int i = 0; int j = 0;

    while (i < n){
        if(p[j] == t[i]){
            j++; i++;
        }

        if(j == m){
            cout << "achei uma aqui " << i-j << "\n";
            j = prefix_padrao[j-1];
        }

        else{
            if(i < n && p[j] != t[i]){
                if( j != 0) j = prefix_padrao[j-1];
                else i = i + 1;
            }
        }
    }
}