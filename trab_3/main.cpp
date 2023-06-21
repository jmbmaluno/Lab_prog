#include "medir_tempo.hpp"

using namespace std;

int main(int narg, char* argv[]){
    if (narg <= 1) {cout << "Não tem argumentos suficientes pro programa rodar\n"; return 1;}
    
    //Recebendo parâmetros
    string acao = argv[1];
    string entrada = argv[2];
    string out = argv[3];

    //Criando instancia do compactador
    Compactador c = Compactador(entrada, out);

    //Medindo tempo da comptação e descomptação
    if(acao == "-c"){
        cout << "Tempo: " << medir_tempo(Compactador::comp, c) << "\n";   
    }
    else{
        cout << "Tempo: " << medir_tempo(Compactador::descomp, c) << "\n";
    }

}