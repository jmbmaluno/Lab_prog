#include <iostream>

using std::cout;
using std::cin;

void insertion_sort(int v[5]){
	int j;
	int chave;

	for(int i = 0; i < 5; i++){
		chave = v[i];
		j = i - 1;

		while(j >= 0 and v[j] > chave){
			v[j+1] = v[j];
			j = j - 1;
		}

		v[j+1] = chave;
	}
}

int main(){
	int v[5];

	cout << "Entre os valorer: \n";

	for(int i = 0; i < 5; i++){
		cout << "Valor " << i+1 << ": ";
		cin >> v[i];	
	}
	
	insertion_sort(v);

	for(int i = 0; i < 5; i++){
		cout << v[i] << "\n";
	}

}
