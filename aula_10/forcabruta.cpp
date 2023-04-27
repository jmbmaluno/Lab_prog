#include <iostream>

using namespace std;


void forca_bruta(char* t,int m, char* p, int n){
    
    bool igual;
    int x = 0;

    for(int i = 0; i < m; i++){
        igual = true;

        while(igual){
            if(t[i+x] == p[x]){
                ++x;
            }
            else{
                igual = false;
                x = 0;
            }

            if (x == n){
                cout << "Padrao esta no testo a partir da posicao " << i << "\n";
                igual = false;
                x = 0;
            }
        }
        
    }

}

void forca_bruta_2(char* t, int m, char* p, int n){
    int j;
    
    for(int i = 0; i <= m-n; i++){
        
        for(j = 0; j < n; j++){
            if (t[i+j] != p[j]) break;
        }

        if(j == n) cout << "Padrao encontrado a partir da posicao " << i << "\n";
    }

}

void imprimir_string(char* t, int n){
    for(int i = 0; i < n; i++){
        cout << t[i];
    }

    cout << "\n";
}

int main(){
    char t[] = {'a', 'n', 'a', ' ', 'c', 'o', 'm', 'e', ' ', 'b', 'a', 'n', 'a', 'n', 'a'};
    char p[] = {'a', 'n', 'a'};

    imprimir_string(t,15);
    imprimir_string(p,3);
    forca_bruta_2(t,15, p, 3);
}