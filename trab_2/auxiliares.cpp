#include "auxiliares.hpp"

MeuGerador::MeuGerador():gerador{disp_aleat()}{};

MeuGerador::operator() (int i, int f){
    uniform_int_distribution<int> distr(i,f);
    return distr(gerador); };