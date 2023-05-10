#include "instancias.hpp"
#include "auxiliares.hpp"

const char letra_aleatoria(const char l){
    MeuGerador g;
    int x = l - 'a';

    return 'a' + g(0,x);
}

char* string_aleatoria(int n, const char l){
    char* t = new char [n];

    for(int i = 0; i < n; i++){
        t[i] = letra_aleatoria(l);
    }
    t[n] = '\0';

    return t;
}