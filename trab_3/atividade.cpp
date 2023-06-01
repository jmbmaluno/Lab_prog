#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

//Nós da arvore de hufman e do heap
struct nohhuf{
    uint16_t esq, dir;
};

struct nohheap{
    short int indice;
    int peso;
};

//Trocar duas posições do heap
template <typename T>
void trocar(T* heap, int i, int j){
    T aux;

    aux = heap[i];
    heap[i] = heap[j];
    heap[j] = aux;
}

//Coloando o elemento de menor peso no começo do heap
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
        trocar<nohheap>(heap, i, menor);

        heapify(heap, n, menor);
    }
}

//Main
int main(){
    int* ocorrencia_bytes = new int[256];
    int n = 0;

    nohhuf* arvore;
    nohheap* heap;

    //Zerando o vetor de ocorrências dos bytes
    for(int i = 0; i < 256; i++){
        ocorrencia_bytes[i] = 0;
    }

    int byte_int;

    //Recebendo o nome do arquivo
    cout << "Nome do arquivo: ";
    string nome;
    cin >> nome;

    //Lendo os bytes e checando se já chegou no fim do arquivo
    ifstream arq (nome.data(), std::ios_base::in | std::ios_base::binary);
    unsigned char byte = arq.get();

    ofstream saida("compactado.huf", std::ios_base::binary | std::ios_base::out);

    if(arq.eof()){cout << "Fim da compactacao!\n"; return 0;}


    while(!arq.eof()) {
        byte_int = (int) byte;
        //Gravando a ocorência dos bytes
        ocorrencia_bytes[byte_int]++;
        byte = arq.get();    
    }


    //Imprimindo n
    cout << "\nContagem dos Bytes: \n";
    for(int i = 0; i < 256; i++){
        if(ocorrencia_bytes[i] > 0){
            n++;
        }
    }
    cout << "n: " << n << "\n";
    
    if(n >= 2){
        //Alocando a arvore e o heap
        arvore = new nohhuf[2*n - 1];
        heap = new nohheap[n];

        
        //Preenchendo o heap e os primeios n nós da arvore de huffman
        int j = 0;
        for(int i = 0; i < 256; i++){
            if(ocorrencia_bytes[i] > 0){
                heap[j].indice = j;
                heap[j].peso = ocorrencia_bytes[i];
                arvore[j++].esq = i;
            }
        }
        
        //Imprimindo o heap
        cout << "Heap\n";
        for(int i = 0; i < n; i++){
            cout << "indice: " << heap[i].indice;
            cout << "; peso: " << heap[i].peso;
            cout << "\n";
        }

        //Criando arvore de huffman (os nós internos)
        int cont = n;
        int i = 0;
        int ultimo = n-1;
        while(i <= n){
            heapify(heap, n-i, 0);
            arvore[cont].esq = heap[0].indice;
            trocar<nohheap>(heap, 0, ultimo--);
            
            i++;

            heapify(heap, n-i, 0);
            arvore[cont].dir = heap[0].indice;
            heap[0].peso = heap[0].peso + heap[n-1].peso;
            heap[0].indice = cont++;

            i++;
        }
        
        //Imprimindo a arvore de hufmam
        cout << "Hufmam Tree\n";
        for(int i = 0; i < 2*n-1; i++){
            if(i >= n){
                cout << "indice: " << i;
                cout << " esq: " << arvore[i].esq;
                cout << " dir: " << arvore[i].dir << "\n";
            }
            else{
                cout << "indice: " << i;
                cout << " valor: " << arvore[i].esq << "\n";
            }
        }
        

        //Desalocando os vetores
        delete[] heap;
        delete[] arvore;
    }

    else{
        saida.write((char *)&n, sizeof(int));
        
    }



    delete[] ocorrencia_bytes;
}