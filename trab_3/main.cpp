#include <iostream>
#include <fstream>
#include <limits>
#include <vector>

using namespace std;

//Nós da arvore de hufman e do heap
struct nohhuf{
    uint16_t esq, dir;
};

struct nohheap{
    short int indice;
    int peso;
};

class Heapmin{
    vector<nohheap> heap;

    public:
    
    void inserir(nohheap noh){
        int cont = 0;

        while(cont < heap.size()){
            if(heap[cont].peso >= noh.peso){heap.insert(heap.begin()+cont, noh); break;}
            cont++;
        }

        if(cont == heap.size()) heap.push_back(noh);
    }

    nohheap top(){
        return heap[0];
    }

    void pop(){
        heap.erase(heap.begin());
    }

    void imprimir(){
        for(int i = 0; i < heap.size(); i++){
            cout << "indice: " << heap[i].indice;
            cout << " peso: " << heap[i].peso << "\n";
        }
    }

    int size(){
        return heap.size();
    }

};

//Trocar duas posições do heap
void trocar(nohheap* heap, int i, int j){
    nohheap aux;

    aux.peso = heap[i].peso;
    aux.indice = heap[i].indice;

    heap[i].peso = heap[j].peso;
    heap[i].indice = heap[j].indice;

    heap[j].peso = aux.peso;
    heap[j].indice = aux.indice;
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
        trocar(heap, i, menor);

        heapify(heap, n, menor);
    }
}

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

void imprimir(vector<char> v){
    for(int i = 0; i < v.size(); i++){
        cout << v[i];
    }
    cout << "\n";
}


int decodificar(vector<char> l, vector <char> * codigos){
    for(int i = 0; i < 256; i++){
        if(codigos[i].size() > 0 && l == codigos[i]) return i;
    }

    return -1;
}

void imprimir_byte(unsigned char byte){
    unsigned char b = byte;

    for(int i = 0; i < 8; ++i){
        if(b >= 128){cout << '1';}
        else{cout << '0';}
        b = b << 1;
    }
    cout << "\n";
}

//Main
int main(int narg, char* argv[]){
    int* ocorrencia_bytes = new int[256];
    int n = 0;
    int qtde_bytes = 0;
    
    string acao = argv[1];
    string entrada = argv[2];
    string out = argv[3];

    nohhuf* arvore;
    //nohheap* heap;
    
    vector<int> sequencia;

    //Zerando o vetor de ocorrências dos bytes
    for(int i = 0; i < 256; i++){
        ocorrencia_bytes[i] = 0;
    }

    int byte_int;

    ifstream arq (entrada.data(), std::ios_base::in | std::ios_base::binary);
    ofstream saida(out, std::ios_base::binary | std::ios_base::out);

    if(acao == "-c"){
        //Lendo os bytes e checando se já chegou no fim do arquivo
        
        unsigned char byte = arq.get();

        if(arq.eof()){cout << "Compactacao finalizada!\n"; return 0;}


        while(!arq.eof()) {
            byte_int = (int) byte;
            //Gravando a ocorência dos bytes
            sequencia.push_back(byte_int);
            ocorrencia_bytes[byte_int]++;
            byte = arq.get();    
        }

        //Calculando n
        cout << "\nContagem dos Bytes: \n";
        for(int i = 0; i < 256; i++){
            if(ocorrencia_bytes[i] > 0){
                qtde_bytes = qtde_bytes + ocorrencia_bytes[i];
                n++;
            }
        }
        //Imprimindo n
        cout << "n: " << n << "\n";
        
        //Escrevendo n no arquivo compactado
        saida.write((char *)&n, sizeof(int));

        if(n >= 2){
            //Alocando a arvore e o heap
            arvore = new nohhuf[2*n - 1];
            //heap = new nohheap[n];
            Heapmin heap = Heapmin();

            
            //Preenchendo o heap e os primeios n nós da arvore de huffman
            int j = 0;
            for(int i = 0; i < 256; i++){
                if(ocorrencia_bytes[i] > 0){

                    //heap[j].indice = j;
                    //heap[j].peso = ocorrencia_bytes[i];
                    heap.inserir({(short)j, ocorrencia_bytes[i]});
                    arvore[j++].esq = i;
                }
            }
            
            
            //Imprimindo o heap
            cout << "Heap\n";
            /*
            for(int i = 0; i < n; i++){
                cout << "indice: " << heap[i].indice;
                cout << "; peso: " << heap[i].peso;
                cout << "\n";
            }*/
            heap.imprimir();

            //Criando arvore de huffman (os nós internos)
            int cont = n;
            int i = 0;
            int ultimo = n-1;
            /*
            while(i <= n){
                heapify(heap, n-i, 0);
                arvore[cont].esq = heap[0].indice;
                trocar(heap, 0, ultimo);
                
                i++;

                heapify(heap, n-i, 0);
                arvore[cont].dir = heap[0].indice;
                heap[0].peso = heap[0].peso + heap[ultimo--].peso;
                heap[0].indice = cont++;

                i++;
            }*/
            
            while(heap.size() > 1){
                nohheap esq = heap.top(); heap.pop();
                nohheap dir = heap.top(); heap.pop();

                arvore[cont].esq = esq.indice;
                arvore[cont].dir = dir.indice;

                heap.inserir({(short)cont++, esq.peso + dir.peso});
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

            //falta criar os códigos de hufmam
            //Percurso em ordem na árvore de hufmman
            vector<char>* codigos = new vector<char>[256];
            vector<char> c;

            gerar_codigo(codigos, arvore, 2*n-2, n, c);

            //Imprimindo o código dos caracteres
            cout << "codigo dos caracteres: \n";
            for(int i = 0; i < 256; i++){
                int n = codigos[i].size();
                if(n > 0){
                    for(int j = 0; j < n; j++){
                        cout << codigos[i][j];
                    }
                    cout << "\n";
                }
            }
            
            //ESCREVENDO NO ARQUIVO COMPACTADO
            //Arvore
            for(int i = 0; i < 2*n-1; i++){
                saida.write((char*)&arvore[i].esq, sizeof(uint16_t));
                if(i >= n){
                    saida.write((char*)&arvore[i].dir, sizeof(uint16_t));
                }
            }
        
            //Quantidade de bytes
            saida.write((char *)&qtde_bytes, sizeof(int));
        
            unsigned char x;
            int bits_preenchidos = 0;

            //Copiando texto codificado
            //não tá gravando, eu acho -> Criar o descompactador primeiro
            for(int i = 0; i < qtde_bytes; i++){
                
                int n = codigos[sequencia[i]].size();
    
                
                for(int j = 0; j < n; j++){
                    
                    x = x << 1 | (codigos[sequencia[i]][j] == '1');

                    bits_preenchidos++;

                    if(bits_preenchidos == 8){
                        saida.put(x);
                        bits_preenchidos = 0;
                    }
                
                }
            }

            if(bits_preenchidos != 0){
                for(int i = 0; i < 8-bits_preenchidos; i++){x = x << 1;}
                saida.put(x);
            }

            


            //Desalocando os vetores
            delete[] codigos;
            //delete[] heap;
            delete[] arvore;
        }

        else{
            int i = 0;
            
            while(ocorrencia_bytes[i] == 0){
                i++;
            }
            cout << ocorrencia_bytes[i] << "\n";

            //qtde de ocorrências
            saida.write((char *)&ocorrencia_bytes[i], sizeof(int));
            
            //Caractere
            saida.put((unsigned char)i);
            
            cout << "Compactacao finalizada!\n";
        }

        delete[] ocorrencia_bytes;

    }

    //Descompactar
    else{ //TESSTAR PARA ARQUIVO VAZIO
        int n;
        int qtde_ocorrencias;

        arq.read((char *)&n, sizeof(int));

        if(arq.eof()){cout << "Descompactacao finalizada!\n"; return 0;}
        
        if (n == 1){
            arq.read((char*)&qtde_ocorrencias, sizeof(int));
            unsigned char letra = arq.get();

            for(int i = 0; i < qtde_ocorrencias; ++i){
                saida.put(letra);
            }

            cout << "Descompactacao finalizada\n";
        }

        //N maio que 1
        else{
            arvore = new nohhuf[2*n - 1];
            
            for(int i = 0; i < 2*n-1; i++){
                arq.read((char*)&arvore[i].esq, sizeof(uint16_t));
                if(i >= n){
                    arq.read((char*)&arvore[i].dir, sizeof(uint16_t));;
                }
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

            vector<char>* codigos = new vector<char>[256];
            vector<char> c;

            gerar_codigo(codigos, arvore, 2*n-2, n, c);

            //Imprimindo o código dos caracteres
            cout << "codigos dos caracteres:\n";
            for(int i = 0; i < 256; i++){
                int n = codigos[i].size();
                if(n > 0){
                    for(int j = 0; j < n; j++){
                        cout << codigos[i][j];
                    }
                    cout << "\n";
                }
            }

            int qtde_letras;

            arq.read((char *)&qtde_letras, sizeof(int));

            cout << "qtde: " << qtde_letras << "\n";
            
            unsigned char byte = arq.get();
            vector <char> letra;
            int bits_lidos = 0;
            int x;

            while(!arq.eof() && qtde_letras > 0){
                
                if(byte >= 128) letra.push_back('1');
                else letra.push_back('0');
                bits_lidos++;

                if(bits_lidos == 8){
                    bits_lidos = 0;
                    byte = arq.get();
                }
                
                else {byte = byte << 1;}
                
                x = decodificar(letra,codigos);

                if(x != -1){
                    saida.put((char)x);
                    qtde_letras--;
                    letra = {};
                }

            }

            delete[] arvore;
        }

    }

        

}