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

int decodificar(vector<char> l, vector <char>* codigos){
    for(int i = 0; i < 256; i++){
        if(codigos[i].size() > 0 && l == codigos[i]) return i;
    }

    return -1;
}

int decodificar2(vector<char> l, nohhuf* arvore, int x){
    int n = (x+2)/2 - 1;
    int i = 0;

    while(x > n && i < (int)l.size()){
        if(l[i] == '0') x = arvore[x].esq;
        else x = arvore[x].dir;
        i++;
    }

    if(i == (int)l.size()) return -1;

    return arvore[x].esq;
}

#endif