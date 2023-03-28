#include <iostream>

using namespace std;

template <typename T>
void trocar(T* v, int i, int j){
	T aux = v[i];
	v[i] = v[j];
	v[j] = aux;
}

template <typename T>
int particionar(T *v, int p, int r){
	T pivot = v[r];
	int i = p-1;
	for(int j = p; j < r; ++j){
		if(v[j] <= pivot){
			i = i + 1;
			trocar(v,i,j);
		}
	}
	
	trocar(v,i+1,r);
	return i+1;
}

template <typename T>
void quicksort(T *v, int p, int r){
	if(p < r){
		int q = particionar(v, p, r);
		quicksort(v, r, q-1);
		quicksort(v, r, q+1);
	}
}

template <typename T>
void imprimir(T *v, int n){
	cout << "Vetor: { ";
	for(int i = 0; i < n; ++i){
		cout << v[i] << " ";
	}
	cout << "}\n";
}

int main(){
	int vi[] = {6, 5, 4, 3, 2, 1};
	double vd[] = {6.6, 5.5, 4.4, 3.3, 2.2, 1.1};

	imprimir<int>(vi,6);
	imprimir<double>(vd,6);

	quicksort<int>(vi,0,5);
	quicksort<double>(vd,0,5);

	imprimir<int>(vi,6);
	imprimir<double>(vd,6);
}
