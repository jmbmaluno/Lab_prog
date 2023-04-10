#include <iostream>
#include "introsort.h"

int main(){
	int v[] = {6,1,3,2};

	imprimir_vetor<int>(v,4);

	quicksort<int>(v,0,3);

	imprimir_vetor<int>(v,4);
}
