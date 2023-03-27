#include <iostream>

using namespace std;

template <typename T>
void insertion_sort(T *v, int n){
	for(int i = 0; i < n; ++i){
		int j = i-1;
		T chave = v[i];

		while(j >= 0 and v[j] > chave){
			T aux = v[j];
			v[j] = v[j+1];
			v[j+1] = aux;
			--j;
		}

		v[j+1] = chave;
	}
}	

template <typename T>
void imprimir_vetor(T *v, int n){
	cout << "Vetor: ";

	for(int i = 0; i < n; ++i){
		cout << v[i] << "  ";
	}

	cout << "\n";
}


int main(){
	int v[] = {2, 3, 1, 5, 4};
	double vd[] = {4.4, 5.5, 4.4, 1.1, 2.2};

	insertion_sort<int>(v,5);
	insertion_sort<double>(vd,5);

	imprimir_vetor<int>(v,5);
	imprimir_vetor<double>(vd,5);
}
