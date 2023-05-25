#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

int main(){
    int* ocorrencia_bytes = new int[256];
    
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
            cout << "Byte " << i << ": " << ocorrencia_bytes[i] << "\n"; 
        }
    }

    delete[] ocorrencia_bytes;
}