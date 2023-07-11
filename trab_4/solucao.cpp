#include <iostream>
using namespace std;

template <typename TC, typename TV>
class DicioAVL {
public: // --------------------------------------------------------------------

    struct Noh {
        TC chave;
        TV valor;
        Noh* pai = nullptr;
        Noh* esq = nullptr;
        Noh* dir = nullptr;
        int altura = 0;
        Noh* obter_dir() { return dir; }
        Noh* obter_esq() { return esq; }
        Noh* obter_pai() { return pai; }

    }; // Noh  ----------------------------------------------------------------

    Noh* obter_raiz() { return raiz; }

private: // ---------------------------------------------------------------
    Noh* raiz;

    Noh* procurarMenor(Noh* atual) {
        if (atual == nullptr) {
            return nullptr;
        }
        struct Noh* no1 = atual;
        struct Noh* no2 = atual->esq;
        while (no2 != NULL) {
            no1 = no2;
            no2 = no2->esq;
        }
        return no1;
    }

    int alturaNo(Noh* no) {
        if (no == NULL)
            return -1;
        else
            return no->altura;
    }

    int balancearNo(Noh* no) {
        return labs(alturaNo(no->esq) - alturaNo(no->dir));
    }

    void rotacaoLL(Noh** raiz) {
        if ((*raiz) == nullptr) {
            return;
        }

        Noh* temp = (*raiz)->esq;

        if (temp != nullptr) {
            temp->pai = (*raiz)->pai;
        }

        (*raiz)->pai = temp;

        if (temp != nullptr) {
            (*raiz)->esq = temp->dir;
            temp->dir = (*raiz);
        }

        if ((*raiz)->esq != nullptr) {
            (*raiz)->esq->pai = (*raiz);
        }

        (*raiz)->altura = max(alturaNo((*raiz)->esq), alturaNo((*raiz)->dir)) + 1;

        temp->altura = max(alturaNo(temp->esq), (*raiz)->altura) + 1;

        (*raiz) = temp;
    }

    void rotacaoRR(Noh** raiz) {
        if ((*raiz) == nullptr) {
            return;
        }

        Noh* temp = (*raiz)->dir;

        if (temp != nullptr) {
            temp->pai = (*raiz)->pai;
        }

        (*raiz)->pai = temp;

        if (temp != nullptr) {
            (*raiz)->dir = temp->esq;
            temp->esq = (*raiz);
        }


        if ((*raiz)->dir != nullptr) {
            (*raiz)->dir->pai = (*raiz);
        }

        (*raiz)->altura = max(alturaNo((*raiz)->esq), alturaNo((*raiz)->dir)) + 1;

        temp->altura = max(alturaNo(temp->dir), (*raiz)->altura) + 1;

        (*raiz) = temp;
    }

    void rotacaoLR(Noh** raiz) {
        rotacaoRR(&(*raiz)->esq);
        rotacaoLL(raiz);
    }

    void rotacaoRL(Noh** raiz) {
        rotacaoLL(&(*raiz)->dir);
        rotacaoRR(raiz);
    }

    Noh* inserirAvl(Noh** raiz, Noh* pai, TC chave, TV valor) {
        Noh* aux = nullptr;
        if ((*raiz) == NULL) {
            Noh* aux = new Noh();

            aux->chave = chave;
            aux->valor = valor;
            aux->altura = 0;
            aux->dir = NULL;
            aux->esq = NULL;
            aux->pai = pai;

            (*raiz) = aux;
            return aux;
        }

        Noh* atual = (*raiz);
        if (chave < atual->chave) {
            if ((aux = inserirAvl(&(*raiz)->esq, *raiz, chave, valor)) != nullptr) {
                if (balancearNo(atual) >= 2) {
                    if ((*raiz)->esq != nullptr && chave < (*raiz)->esq->chave) {
                        rotacaoLL(raiz);
                    }
                    else {
                        rotacaoLR(raiz);
                    }
                }
            }
        }
        else {
            if (chave > atual->chave) {
                if ((aux = inserirAvl(&(*raiz)->dir, *raiz, chave, valor)) != nullptr) {
                    if (balancearNo(atual) >= 2) {
                        if ((*raiz)->dir != nullptr && chave > (*raiz)->dir->chave) {
                            rotacaoRR(raiz);
                        }
                        else {
                            rotacaoRL(raiz);
                        }
                    }
                }
            }
            else {
                return nullptr;
            }
        }

        atual->altura = max(alturaNo(atual->esq), alturaNo(atual->dir)) + 1;
        return aux;
    }

    Noh* corrigir(Noh* sucessor, Noh* atual) {
        if (atual->dir == sucessor) {
            atual->dir = sucessor->dir;
            sucessor->dir = atual;
        }
        else {
            sucessor->pai->esq = atual;
            swap(atual->dir, sucessor->dir);
        }

        swap(sucessor->pai, atual->pai);

        swap(sucessor->altura, atual->altura);

        swap(sucessor->esq, atual->esq);

        if (sucessor->esq != nullptr) {
            sucessor->esq->pai = sucessor;
        }

        if (sucessor->dir != nullptr) {
            sucessor->dir->pai = sucessor;
        }

        if (atual->esq != nullptr) {
            atual->esq->pai = atual;
        }

        if (atual->dir != nullptr) {
            atual->dir->pai = atual;
        }
        return sucessor;
    }

    Noh* removerAvl(Noh** raiz, TC chave) {
        if ((*raiz) == nullptr) {
            return nullptr;
        }

        Noh* aux = nullptr;

        if (chave < (*raiz)->chave) {
            if ((aux = removerAvl(&(*raiz)->esq, chave)) != nullptr) {
                if (balancearNo(*raiz) >= 2) {
                    if (alturaNo((*raiz)->dir->esq) <= alturaNo((*raiz)->dir->dir)) {
                        rotacaoRR(raiz);
                    }
                    else {
                        rotacaoRL(raiz);
                    }
                }
            }
        }
        if ((*raiz)->chave < chave) {
            if ((aux = removerAvl(&(*raiz)->dir, chave)) != nullptr) {
                if (balancearNo(*raiz) >= 2) {
                    if ((*raiz)->esq != nullptr && alturaNo((*raiz)->esq->dir) <= alturaNo((*raiz)->esq->esq)) {
                        rotacaoLL(raiz);
                    }
                    else {
                        rotacaoLR(raiz);
                    }
                }
            }
        }

        if ((*raiz)->chave == chave) {
            if ((*raiz)->esq == nullptr || (*raiz)->dir == nullptr) {
                Noh* aux = (*raiz);
                if ((*raiz)->esq != nullptr) {
                    (*raiz)->esq->pai = (*raiz)->pai;
                    (*raiz) = (*raiz)->esq;
                }
                else {
                    if ((*raiz)->dir != nullptr) {
                        (*raiz)->dir->pai = (*raiz)->pai;
                    }
                    (*raiz) = (*raiz)->dir;
                }

                delete[] aux;
            }
            else {
                Noh* sucessor = procurarMenor((*raiz)->dir);

                Noh* a = (*raiz);

                (*raiz) = corrigir(sucessor, a);

                aux = removerAvl(&(*raiz)->dir, a->chave);
                if (balancearNo(*raiz) >= 2) {
                    if (alturaNo((*raiz)->esq->dir) <= alturaNo((*raiz)->esq->esq)) {
                        rotacaoLL(raiz);
                    }
                    else {
                        rotacaoLR(raiz);
                    }
                }
            }
            if ((*raiz) != nullptr) {
                (*raiz)->altura = max(alturaNo((*raiz)->esq), alturaNo((*raiz)->dir)) + 1;
            }
            return (Noh*)1;
        }

        (*raiz)->altura = max(alturaNo((*raiz)->esq), alturaNo((*raiz)->dir)) + 1;
        return aux;
    }

    Noh* buscarAvl(Noh* raiz, TC chave) {
        if (raiz == nullptr)
            return 0;
        Noh* atual = raiz;
        while (atual != nullptr) {
            if (chave == atual->chave) {
                return atual;
            }
            if (chave > atual->chave) {
                atual = atual->obter_dir();
            }
            else {
                atual = atual->obter_esq();
            }
        }
        return nullptr;
    }

public: // --------------------------------------------------------------------

    void limparMemoria(Noh* raiz) {
        if (raiz == NULL)
            return;
        if (raiz->obter_esq() == nullptr && raiz->obter_dir() == nullptr) {
            delete[] raiz;
            raiz = nullptr;
            return;
        }
        limparMemoria(raiz->obter_esq());
        limparMemoria(raiz->obter_dir());
    }
    DicioAVL() { raiz = nullptr; }
    ~DicioAVL() {
        limparMemoria(this->obter_raiz());
    }

    class Iterador {
    private: // --------------------------------------------------------------
        Noh* it = nullptr;

    public: // ---------------------------------------------------------------
        bool operator!=(Iterador a) {
            return this->it != a.it;
        }
        bool operator==(Iterador a) {
            return this->it == a.it;
        }

        void setIt(Noh* novoNoh) { this->it = novoNoh; }
        Noh* getIt() { return this->it; }

        TC chave() {
            return this->it->chave;
        }
        TV valor() {
            return this->it->valor;
        }
        void operator++() {
            if (it->obter_pai() != nullptr && it->obter_pai()->chave > it->chave) {
                if (it->obter_dir() == nullptr) {
                    it = it->obter_pai();
                }
                else {
                    Noh* aux = it->obter_dir();
                    while (aux->obter_esq() != nullptr) {
                        aux = aux->obter_esq();
                    }

                    it = aux;
                }
            }
            else {
                if (it->obter_dir() != nullptr) {
                    Noh* aux = it->obter_dir();
                    while (aux->obter_esq() != nullptr) {
                        aux = aux->obter_esq();
                    }

                    it = aux;
                }
                else {
                    Noh* aux = it;
                    while (aux->obter_pai() != nullptr && aux->chave > aux->obter_pai()->chave) {
                        aux = aux->obter_pai();
                    }

                    if (aux->obter_pai() == nullptr) {
                        it = nullptr;
                    }
                    else {
                        it = aux->obter_pai();
                    }
                }
            }
        }

    }; // Iterador ------------------------------------------------------------

    Iterador inicio() {
        // printf("%d \n",raiz);
        Iterador novoIterador;
        novoIterador.setIt(procurarMenor(obter_raiz()));
        return novoIterador;
    }

    Iterador fim() {
        Iterador aux;
        aux.setIt(nullptr);
        return aux;
    }

    Iterador inserir(TC c, TV v) {
        Iterador aux;
        Noh* novonoh = inserirAvl(&raiz, nullptr, c, v);
        if (novonoh != nullptr) {
            aux.setIt(novonoh);
        }
        return aux;
    }

    Iterador buscar(TC c) {
        Iterador aux;
        Noh* novonoh = buscarAvl(raiz, c);
        aux.setIt(novonoh);
        return aux;
    }

    void remover(Iterador i) {
        removerAvl(&this->raiz, i.chave());
    }

}; // DicioAVL  --------------------------------------------------------------
