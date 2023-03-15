#include <iostream>

using std::cout;

bool iguais(const char *i, const char *j){
	
	const char *p;
	const char *v;

	p = i; v = j;

	while(*p != '\0' and *v != '\0'){

		if(*p != *v) return false;

		p++;
		v++;
	}

	if(*p != '\0' or *v != '\0'){
		return false;
	}

	return true;
}

int main(int argc, char **argv){
	if(argc == 3){
		if(iguais(argv[1], argv[2])) cout << "São iguais\n";
		else cout << "São diferentes\n";
	}

	else cout << "Os argumentos não são válidos\n";
}
