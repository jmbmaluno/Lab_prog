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

void trocar(nohheap* heap, int i, int j){
    nohheap aux;

    aux = heap[i];
    heap[i] = heap[j];
    heap[j] = aux;
}

void heapify(nohheap* heap, int n, int i){
    int menor = i;

    int esq = 2 * i + 1;
    int dir = 2 * i + 2;

    if(esq < n && heap[esq].peso < heap[menor].peso){
        menor = esq;
    }

    if(dir < n && heap[dir].peso < heap[menor].peso){
        menor = dir;
    }

    if(menor != i){
        trocar(heap, i, menor);

        heapify(heap, n, menor);
    }
}

void criar_heap_minimo(nohheap* heap, int n){
    for(int i = (n/2) - 1; i >=0; i--){
        heapify(heap, n, i);
    }
}

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

    criar_heap_minimo(heap,n);
    
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