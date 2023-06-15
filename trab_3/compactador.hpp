#ifndef COMPACTADOR_HUF
#define COMPACTADOR_HUF

#include <fstream>
#include "arvore.hpp"

using namespace std;

class Compactador{
    string entrada;
    string out;

    public:
        Compactador(string e, string o){
            
            entrada = e;
            out = o;
        }

        void comp(){
            int* ocorrencia_bytes = new int[256];
            
            for(int i = 0; i < 256; i++){
                ocorrencia_bytes[i] = 0;
            }

            ifstream arq (entrada.data(), std::ios_base::in | std::ios_base::binary);
            ofstream saida(out, std::ios_base::binary | std::ios_base::out);

            nohhuf* arvore;
            int n = 0;
            int qtde_bytes = 0;
            vector<int> sequencia;
            unsigned char byte = arq.get();
            

            if(arq.eof()){cout << "Compactacao finalizada!\n"; return;}

            while(!arq.eof()) {
                //Gravando a ocorência dos bytes
                sequencia.push_back((int)byte);
                ocorrencia_bytes[(int)byte]++;
                byte = arq.get();    
            }

            //Calculando n
            for(int i = 0; i < 256; i++){
                if(ocorrencia_bytes[i] > 0){
                    qtde_bytes = qtde_bytes + ocorrencia_bytes[i];
                    n++;
                }
            }
            
            //Escrevendo n no arquivo compactado
            saida.write((char *)&n, sizeof(int));

            if(n >= 2){
                //Alocando a arvore
                arvore = new nohhuf[2*n - 1];
                Heapmin heap = Heapmin();

                
                //Preenchendo o heap e os primeios n nós da arvore de huffman
                int j = 0;
                for(int i = 0; i < 256; i++){
                    if(ocorrencia_bytes[i] > 0){
                        heap.inserir({(short)j, ocorrencia_bytes[i]});
                        arvore[j++].esq = i;
                    }
                }

                //Criando arvore de huffman (os nós internos)
                int cont = n;
                
                while(heap.size() > 1){
                    nohheap esq = heap.top(); heap.pop();
                    nohheap dir = heap.top(); heap.pop();

                    arvore[cont].esq = esq.indice;
                    arvore[cont].dir = dir.indice;

                    heap.inserir({(short)cont++, esq.peso + dir.peso});
                }

                //falta criar os códigos de hufmam
                //Percurso em ordem na árvore de hufmman
                vector<char>* codigos = new vector<char>[256];
                vector<char> c;

                gerar_codigo(codigos, arvore, 2*n-2, n, c);
                
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
                delete[] arvore;

                cout << "Compatacao Finalizada\n";
            }

            else{
                int i = 0;
                
                while(ocorrencia_bytes[i] == 0){
                    i++;
                }

                //qtde de ocorrências
                saida.write((char *)&ocorrencia_bytes[i], sizeof(int));
                
                //Caractere
                saida.put((unsigned char)i);
                
                cout << "Compactacao finalizada!\n";
            }

            delete[] ocorrencia_bytes;
        }



        void descomp(){
            int n;
            int qtde_ocorrencias;
            
            ifstream arq (entrada.data(), std::ios_base::in | std::ios_base::binary);
            ofstream saida(out, std::ios_base::binary | std::ios_base::out);

            arq.read((char *)&n, sizeof(int));

            if(arq.eof()){cout << "Descompactacao finalizada!\n"; return;}
            
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

                nohhuf* arvore = new nohhuf[2*n - 1];
                
                for(int i = 0; i < 2*n-1; i++){
                    arq.read((char*)&arvore[i].esq, sizeof(uint16_t));
                    if(i >= n){
                        arq.read((char*)&arvore[i].dir, sizeof(uint16_t));;
                    }
                }

                vector<char> c;

                int qtde_letras;

                arq.read((char *)&qtde_letras, sizeof(int));
                
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
                    x = decodificar2(letra, arvore, 2*n-2);

                    if(x != -1){
                        saida.put((char)x);
                        qtde_letras--;
                        letra = {};
                    }

                }

                /*
                for(int i = 0; i < qtde_letras; i++){
                    x = decodificar2(letra, arvore, 2*n-2);
                   
                    while(x == -1){

                        if(byte >= 128) letra.push_back('1');
                        else letra.push_back('0');

                        bits_lidos++;
                        if(bits_lidos == 8){
                            bits_lidos = 0;
                            byte = arq.get();
                        }
                        else byte = byte << 1;

                        x = decodificar2(letra,arvore, 2*n-2);

                    }

                    saida.put((char)x);
                    letra = {};

                }*/

                delete[] arvore;
                cout << "Descompactacao finalizada\n";

            }
        }
};


#endif