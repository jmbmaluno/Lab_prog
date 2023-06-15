#ifndef ARVORE_CPP
#define ARVORE_CPP

#include "heap.hpp"
#include <vector>

struct nohhuf{
    uint16_t esq, dir;
};

void gerar_codigo(vector<char>* codigos, nohhuf* arvore, int pos, int n, vector<char> c){
    if(pos >= n){
        c.push_back('0');
        gerar_codigo(codigos, arvore, arvore[pos].esq, n, c);
        c.pop_back();
        c.push_back('1');
        gerar_codigo(codigos, arvore, arvore[pos].dir, n, c);
    }
    else{
        codigos[arvore[pos].esq] = c;
    }
}

vector<char> decodificar(nohhuf* arvore, int n, vector<char> texto, int qtde_letras){
    vector<char> saida;
    int i = n*2 - 2;

    for(int j = 0; j < (int)texto.size(); ++j){
        if(qtde_letras > 0){
            if(texto[j] == '0') i = arvore[i].esq;
            else i = arvore[i].dir;

            if(i < n){
                saida.push_back(arvore[i].esq);
                i = n*2-2;
                qtde_letras--;
            }
        }
    }

    return saida;
}

#endif