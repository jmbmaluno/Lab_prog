#include <iostream>
#include "instancias.hpp"
#include "algoritmos_busca.hpp"
#include "medir_tempo.hpp"

using namespace std;

template <typename T>
void imprimir_vetor(T* v, int n){
    cout << "Vetor -> ";
    
    for(int i = 0; i < n; i++){
        cout << v[i] << " ";
    }
    cout << "\n";
}

int main(int narg, char* argv[]){
    char tipo_instancia; 

    //Caso de tipo_instancia == A
    char letra_limite_aleatoria; int m; int n; int qtde_iteracoes;

    //Caso de tipo_instancia == R
    int x; int y;  

    const char* p;
    const char* t;
    //adicioanr o outro vetor de inteiros quando o outro algoritmo estiver pronto
    int* o;


    double tempo_forca_bruta = 0.0;

    if (narg == 6){
        tipo_instancia = 'A';
        letra_limite_aleatoria = argv[2][0];
        m = atoi(argv[3]);
        n = atoi(argv[4]);
        qtde_iteracoes = atoi(argv[5]);


        o = new int[n];

        while(qtde_iteracoes != 0){
            p = string_aleatoria(m, letra_limite_aleatoria);
            t = string_aleatoria(n, letra_limite_aleatoria);

            imprimir_vetor(p, m);
            imprimir_vetor(t, n);

            tempo_forca_bruta += medir_tempo(forca_bruta, p, t, o);

            int c = 0;
            while(c != m and o[c] != -1) cout << o[c++] << " ";
            if(c == 0) cout << -1;
            cout << "\n";
            
            qtde_iteracoes--;
        }
    }

    if (narg == 4){
        tipo_instancia = 'R';
        x = atoi(argv[2]);
        y = atoi(argv[3]);
    }

    cout << "TRABALHO 2\n";
    cout << "Tempo do algoritmo de forca bruta = " << tempo_forca_bruta << "\n";


    delete[] o; 
}