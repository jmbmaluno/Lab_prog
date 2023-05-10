#ifndef ALGORITMOS_H
#define ALGORITMOS_H

int tamanho_string(const char* t);

void forca_bruta(const char* p, const char* t, int* o);

void preprocessamento_kmp(const char* p, int* prefix_padrao);

void kmp(const char* p, const char* t);

#endif