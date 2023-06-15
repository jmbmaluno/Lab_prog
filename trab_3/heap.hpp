#ifndef HEAP_HPP
#define HEAP_HPP

#include <vector>
#include <iostream>

using namespace std;

struct nohheap{
    short int indice;
    int peso;
};

class Heapmin{
    vector<nohheap> heap;

    public:
    
    void inserir(nohheap noh){
        int cont = 0;

        while(cont < (int)heap.size()){
            if(heap[cont].peso >= noh.peso){heap.insert(heap.begin()+cont, noh); break;}
            cont++;
        }

        if(cont == (int)heap.size()) heap.push_back(noh);
    }

    nohheap top(){
        return heap[0];
    }

    void pop(){
        heap.erase(heap.begin());
    }

    void imprimir(){
        for(int i = 0; i < (int)heap.size(); i++){
            cout << "indice: " << heap[i].indice;
            cout << " peso: " << heap[i].peso << "\n";
        }
    }

    int size(){
        return heap.size();
    }

};

#endif