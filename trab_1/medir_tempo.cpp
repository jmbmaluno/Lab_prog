#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

int main(){
	int n; cout << "n: ";

	auto inicio = steady_clock::now();

	cin >> n;
	
	auto fim = steady_clock::now();;

	duration<double> d = fim - inicio;

	cout << "Você demorou " << d.count() << " segundos\n";
}
