#ifndef HEAP_HPP
#define HEAP_HPP

#include <vector>
#include <iostream>

using namespace std;

//Estrutura do heap
struct nohheap{
    short int indice;
    int peso;
};


class Heapmin{
    //O heap será guardado em um vetor
    vector<nohheap> heap;

    public:
    
    //Insiro o elemento na posição correta para manter a propriedade do heap
    void inserir(nohheap noh){
        int cont = 0;

        while(cont < (int)heap.size()){
            if(heap[cont].peso >= noh.peso){heap.insert(heap.begin()+cont, noh); break;}
            cont++;
        }

        if(cont == (int)heap.size()) heap.push_back(noh);
    }

    //Recebe o valor do top do heap
    nohheap top(){
        return heap[0];
    }

    //Apaga o elemento do top do heap
    void pop(){
        heap.erase(heap.begin());
    }

    //Imprime o heap
    void imprimir(){
        for(int i = 0; i < (int)heap.size(); i++){
            cout << "indice: " << heap[i].indice;
            cout << " peso: " << heap[i].peso << "\n";
        }
    }
    
    //Retorna o tamanho do heap
    int size(){
        return heap.size();
    }

};

#endif