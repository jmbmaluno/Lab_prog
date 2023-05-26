#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

struct nohhuf{
    uint16_t esq, dir;
};

struct nohheap{
    short int indice;
    int peso;
};

int main(){
    int* ocorrencia_bytes = new int[256];
    int n = 0;

    nohhuf* arvore;

    nohheap* heap;

    for(int i = 0; i < 256; i++){
        ocorrencia_bytes[i] = 0;
    }

    int byte_int;
    cout << "Nome do arquivo: ";
    string nome;
    cin >> nome;

    ifstream arq (nome.data(), std::ios_base::in | std::ios_base::binary);

    unsigned char byte = arq.get();

    if(arq.eof()){cout << "Vazio!\n"; return 0;}

    while(!arq.eof()) {
        byte_int = (int) byte;
        ocorrencia_bytes[byte_int]++;
        byte = arq.get();    
    }

    cout << "\nContagem dos Bytes: \n";

    for(int i = 0; i < 256; i++){
        if(ocorrencia_bytes[i] > 0){
            n++;
        }
    }
    
    cout << n << " caracteres\n";
    
    arvore = new nohhuf[2*n - 1];
    heap = new nohheap[n];

    int j = 0;
    
    for(int i = 0; i < 256; i++){
        if(ocorrencia_bytes[i] > 0){
            heap[j].indice = j;
            heap[j].peso = ocorrencia_bytes[i];
            arvore[j++].esq = i;
        }
    }

    cout << "Heap\n";

    for(int i = 0; i < n; i++){
        cout << "indice: " << heap[i].indice;
        cout << "; peso: " << heap[i].peso;
        cout << "\n";
    }

    delete[] ocorrencia_bytes;
    delete[] heap;
    delete[] arvore;
}