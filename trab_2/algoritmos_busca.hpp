#ifndef ALGORITMOS_H
#define ALGORITMOS_H

int tamanho_string(const char* t);

bool forca_bruta(const char* p, const char* t, int* o);

void preprocessamento_kmp(const char* p, int* prefix_padrao);

bool kmp(const char* p, const char* t, int* o);

#endif