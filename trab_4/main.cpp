// Este arquivo deve ser compil´avel atrav´es de um comando como:
//
// g++ -Wall -Wextra -std=c++17 -pedantic teste.cpp
#include <exception>
#include <iostream>
using namespace std;
// Ao fazer a implementa¸c~ao, renomeie o arquivo para "solucao.hpp".
#include "solucao.hpp"

int main (){
    try{
        DicioAVL<int,char> D;
        DicioAVL<int,char>::Iterador its[10], it;
        int i;

        for (i = 48; i < 58; ++i){
            it = D.inserir(i, (char) i); if (it == D.end()) return 2;
            its[i-48] = it;
        }

        for (it = D.begin(); it != D.end(); ++it){
            cout << "O codigo de ’" << it.valor() << '’ é ' << it.chave() << '\n';
        }

        for (i = 48; i < 58; ++i){
            it = D.buscar(i); if (it != its[i-48]) return 2;
            D.remover(it);
        }

        cout << "Executou o teste b´asico conforme esperado.\n";
    }

    catch (const exception &e){
            cerr << "Exce¸c~ao: " << e.what() << '\n'; return 1;
        }

} // main