#include <iostream>
using namespace std;

int parent(int i){
	return (i-1)/2;
}

int left(int i){
	return 2*i + 1;
}

int right(int i){
	return 2*i + 2;
}


template <typename T>
void trocar(T* a, int i, int j){
	T aux = a[i];
	a[i] = a[j];
	a[j] = aux;
}

template <typename T>
void max_heapify(T* a, int i, int n){
	int l = left(i);
	int r = right(i);
	int maior;

	if (l < n && a[l] > a[i]){
		maior = l;
	}
	else{maior = i;}

	if (r < n && a[r] > a[maior]){
		maior = r;
	}

	if (maior != i){
		trocar(a,i,maior);
		max_heapify(a,maior,n);
	}
}

template <typename T>
void build_max_heap(T* a, int n){
	for(int i = n/2-1; i >= 0; --i){
		max_heapify(a, i, n);
	}
}

template <typename T>
void heapsort(T* a, int n){
	build_max_heap(a,n);
	for(int i = n-1; i >= 1; --i){
		trocar(a,0,i);
		max_heapify(a,0,n-1);
	}
}

template <typename T>
void imprimir_vetor(T* a, int n){
	cout << "Vetor: ";

	for(int i = 0; i < n; ++i){
		cout << a[i] << " ";
	}

	cout << "\n";
}

int main(){
	int a[] = {6,3,1,4};
	
	imprimir_vetor<int>(a,4);

	heapsort<int>(a,4);

	imprimir_vetor<int>(a,4);

}
