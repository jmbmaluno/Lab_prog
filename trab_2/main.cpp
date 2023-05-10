#include <iostream>
#include "instancias.hpp"
#include "algoritmos_busca.hpp"
#include "medir_tempo.hpp"
#include "instancia_real.hpp"

using namespace std;

template <typename T>
void imprimir_vetor(T* v, int n){
    cout << "Vetor -> ";
    
    for(int i = 0; i < n; i++){
        cout << v[i] << " ";
    }
    cout << "\n";
}

template <typename T>
bool vetores_iguas(T* v, T* u, int n){
    for(int i = 0; i < n; i++) 
        if(v[i] != u[i])    
            return false;

    return true;
}



int main(int narg, char* argv[]){
    char tipo_instancia; 

    //Caso de tipo_instancia == A
    char letra_limite_aleatoria; int m; int n; int qtde_iteracoes;

    //Caso de tipo_instancia == R
    int x; int y;  

    const char* p;
    const char* t;


    double tempo_forca_bruta = 0.0;
    double tempo_kmp = 0.0;

    if (narg == 6){
        tipo_instancia = 'A';
        letra_limite_aleatoria = argv[2][0];
        m = atoi(argv[3]);
        n = atoi(argv[4]);
        qtde_iteracoes = atoi(argv[5]);


        int* vetor_forca_bruta = new int[n];
        int* vetor_kmp = new int[n];

        while(qtde_iteracoes != 0){
            p = string_aleatoria(m, letra_limite_aleatoria);
            t = string_aleatoria(n, letra_limite_aleatoria);

            tempo_forca_bruta += medir_tempo(forca_bruta, p, t, vetor_forca_bruta);
            
            qtde_iteracoes--;
        }

        delete[] vetor_forca_bruta;
    }

    if (narg == 4){
        tipo_instancia = 'R';
        x = atoi(argv[2]);
        y = atoi(argv[3]);

        for(int i = x; i <= y; i++){
            int* vetor_forca_bruta = new int[tamanho_string(Padroes_Palavras[i])];
       
            cout << Padroes_Palavras[i] << "\n";
            tempo_forca_bruta += medir_tempo(forca_bruta, Padroes_Palavras[i], Texto_Livros, vetor_forca_bruta);
             
            delete[] vetor_forca_bruta;
        }
    }

    cout << "TRABALHO 2\n";
    cout << "Tempo do algoritmo de forca bruta = " << tempo_forca_bruta << "\n";

}