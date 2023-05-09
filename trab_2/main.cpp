#include <iostream>
#include "algoritmos_busca.hpp"

using namespace std;

template <typename T>
void imprimir_vetor(T* v, int n){
    cout << "Vetor -> ";
    
    for(int i = 0; i < n; i++){
        cout << v[i] << " ";
    }
    cout << "\n";
}

int main(){
    const char* p = "ana";
    const char* t = "ana come banana";
    int n = tamanho_string(t);
    int* o = new int[n+1];

    imprimir_vetor(t, n);
    imprimir_vetor(p, tamanho_string(p));

    cout << "Resultado do forca bruta:\n";
    forca_bruta(p,t,o);

    cout << "Vetor O -> ";
    int cont = 0;
    while(cont != n and o[cont] != -1) cout << o[cont++] << " ";
    if (cont == 0) cout << "-1";  
    cout << "\n";

    delete[] o; 
}