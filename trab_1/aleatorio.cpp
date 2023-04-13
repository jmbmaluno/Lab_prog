#include <random>
#include <iostream>

using namespace std;

class MeuGerador{
	random_device disp_aleat;
	mt19937 gerador;
	uniform_int_distribution<int> distr;
	
	public:

	MeuGerador(): gerador{ disp_aleat() }, distr(100,200) {}

	//int numero()
	int operator() (){return distr(gerador);}
};

int main(){
	MeuGerador g;

	for(int i = 0; i < 10; ++i) cout << " " << g();

	cout << "\n";
}
