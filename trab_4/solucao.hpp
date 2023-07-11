// -----------------------------------------------------------------------------
// Universidade Federal do CearÃ¡, Centro de CiÃªncias, Departamento de ComputaÃ§Ã£o
// Disciplina:  LaboratÃ³rio de ProgramaÃ§Ã£o - CK0215 2023.1 T01A
// Professor:   Pablo Mayckon Silva Farias
//
// Trabalho 4 - Interface para ImplementaÃ§Ã£o de DicionÃ¡rio baseado em Ãrvore AVL
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// IDENTIFICAÃ‡ÃƒO DO(A) ESTUDANTE:
//
// NOME: João Marcos Brito Matias
// MATRÃCULA: 494952
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// Tudo o que estÃ¡ prenullptre na interface abaixo deve ser mantido como estÃ¡,
// pois esta interface serÃ¡ utilizada no programa do professor para a realizaÃ§Ã£o
// dos testes.
//
// O trabalho consiste portanto em *completar* a implementaÃ§Ã£o abaixo,
// tornando-a funcional e atendendo aos requisitos deste trabalho.
//
// Os pontos a serem completados estÃ£o marcados com "TODO", isto Ã©, "por fazer".
// -----------------------------------------------------------------------------

#ifndef DICIOAVL_HPP
#define DICIOAVL_HPP

using namespace std;
// -----------------------------------------------------------------------------

// A classe DicioAVL deve implementar um dicionÃ¡rio que associe chaves de tipo
// TC a valores de tipo TV.
//
// O dicionÃ¡rio deve organizar esses dados numa Ã¡rvore AVL em que os elementos
// sejam ordenados entre si a partir de suas chaves.
//
// Ã‰ pressuposto da classe que as chaves podem ser normalmente comparadas
// atravÃ©s dos operadores relacionais comuns: <, >=, !=, etc.

template <typename TC, typename TV>
class DicioAVL {
   public:

   // Numa implementaÃ§Ã£o tÃ­pica de dicionÃ¡rio,
   // a reprenullptraÃ§Ã£o interna normalmente fica inacessÃ­vel ao usuÃ¡rio;
   // neste trabalho, porÃ©m,
   // o professor precisa avaliar se a Ã¡rvore estÃ¡ correta,
   // e por isso a estrutura do nÃ³ Ã© exposta ao usuÃ¡rio (daÃ­ o "public" acima),
   // assim como o ponteiro raiz e a nullptrinela:

   struct Noh{
      TC chave;  TV valor;
      Noh* esq = nullptr; 
      Noh* dir = nullptr; 
      Noh* pai = nullptr;
      int altura = 0;

      // -----------------------------------------------------------------------

      // Esta funÃ§Ã£o deve retornar um ponteiro para o filho direito,
      // se o nÃ³ possuir filho direito;
      // em caso contrÃ¡rio, deve ser retornado um ponteiro para o nÃ³ nullptrinela,
      // definido mais abaixo.

      Noh* obter_dir (){
        return dir;
      }

      // -----------------------------------------------------------------------

      // Esta funÃ§Ã£o deve retornar um ponteiro para o filho esquerdo,
      // se o nÃ³ possuir filho esquerdo;
      // em caso contrÃ¡rio, deve ser retornado um ponteiro para o nÃ³ nullptrinela,
      // definido mais abaixo.

      Noh* obter_esq (){
        return esq;
      }

      // -----------------------------------------------------------------------

      // Esta funÃ§Ã£o deve retornar um ponteiro para o nÃ³ pai,
      // se o nÃ³ possuir nÃ³ pai;
      // em caso contrÃ¡rio, deve ser retornado um ponteiro para o nÃ³ nullptrinela,
      // definido mais abaixo.

      Noh* obter_pai (){
        return pai;
      }

     }; // struct Noh

   // --------------------------------------------------------------------------

   // Campos pÃºblicos de DicioAVL: raiz e nullptrinela.
   // Lembrete: nÃ£o altere-os, pois serÃ£o usados nos testes automÃ¡ticos.
   Noh* obter_raiz() {return raiz;}

   Noh  sent;  // NÃ³ sentrinela.
   Noh *raiz;  // "raiz" deve apontar para "nullptr" quando a Ã¡rvore estiver vazia.

   // ==========================================================================

   private:

   Noh* procurarMenor(Noh* atual){
    if(atual == nullptr){
        return nullptr;
    }

    struct Noh* no1 = atual;
    struct Noh* no2 = atual->esq;
    while(no2 != nullptr){
        no1 = no2;
        no2 = no2->esq;
    }

    return no1;
   }

   int alturaNo(Noh* no){
    if (no == nullptr) return -1;
    return no->altura;
   }


   int balancearNo(Noh* no){
    return labs(alturaNo(no->esq) - alturaNo(no->dir));
   }

   
   void rotacaoLL(Noh** raiz){
    if((*raiz) != nullptr){
      Noh* temp = (*raiz)->esq;

      if(temp != nullptr){
        temp->pai = (*raiz)->pai;
      }

      (*raiz)->pai = temp;

      if(temp != nullptr){
        (*raiz)->esq = temp->dir;
        temp->dir = (*raiz);
      }

      if((*raiz)->esq != nullptr){
        (*raiz)->esq->pai = (*raiz);
      }

      (*raiz)->altura = max(alturaNo((*raiz)->esq), alturaNo((*raiz)->dir)) + 1;
    
      temp->altura = max(alturaNo(temp->esq), (*raiz)->altura) + 1;

      (*raiz) = temp;
    }
   }

   void rotacaoRR(Noh** raiz){
      if((*raiz) != nullptr){

        Noh* temp = (*raiz)->dir;

        if(temp != nullptr){
          temp->pai = (*raiz)->pai;
        }

        (*raiz)->pai = temp;

        if(temp != nullptr){
          (*raiz)->dir = temp->esq;
          temp->esq = (*raiz);
        }

        if((*raiz)->dir != nullptr){
          (*raiz)->dir->pai = (*raiz);
        }

        (*raiz)->altura = max(alturaNo((*raiz)->esq), alturaNo((*raiz)->dir)) + 1;

        temp->altura = max(alturaNo(temp->dir), (*raiz)->altura) + 1;

        (*raiz) = temp;
      }
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
        if ((*raiz) == nullptr) {
            Noh* aux = new Noh();

            aux->chave = chave;
            aux->valor = valor;
            aux->altura = 0;
            aux->dir = nullptr;
            aux->esq = nullptr;
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
   // ==========================================================================

   public:

    void limparMemoria(Noh* raiz) {
        if (raiz == nullptr)
            return;
        if (raiz->obter_esq() == nullptr && raiz->obter_dir() == nullptr) {
            delete[] raiz;
            raiz = nullptr;
            return;
        }
        limparMemoria(raiz->obter_esq());
        limparMemoria(raiz->obter_dir());
    }

   // --------------------------------------------------------------------------

   class Iterador
     {
      private:

      Noh* noh = nullptr;

      // -----------------------------------------------------------------------

      public:
      // -----------------------------------------------------------------------

      // Lembrete: Ã© possÃ­vel implementar diferentes construtores para uma mesma
      // classe.

      // Construtor padrÃ£o (sem argumentos): deve ser possÃ­vel inicializar um
      // iterador sem que ele aponte para algum elemento especÃ­fico de um
      // DicioAVL. Isso Ã© Ãºtil para declarar uma variÃ¡vel de tipo Iterador sem
      // ter a obrigaÃ§Ã£o de jÃ¡ apontÃ¡-la para um elemento de um dicionÃ¡rio.
      //
      // A Ãºnica operaÃ§Ã£o esperada sobre um iterador assim inicializado Ã©
      // receber uma cÃ³pia de outro iterador.
      // Portanto, nÃ£o se deve chamar mÃ©todos como "chave" nem operadores como
      // "==" e "++" sobre um iterador que nÃ£o esteja apontando para um elemento
      // de um dicionÃ¡rio.
      //
      // ObservaÃ§Ã£o: caso deseje, vocÃª pode implementar o construtor padrÃ£o de
      // forma que seja vÃ¡lido chamar os operadores "==" e "!=" sobre um
      // iterador assim inicializado. PorÃ©m, isso nÃ£o Ã© exigido neste trabalho.

      //Iterador (Noh *n) : noh{n} {}

      // -----------------------------------------------------------------------

      // Os operadores "!=" e "==" abaixo podem ser chamados mesmo caso
      // o iterador esteja no "fim" do dicionÃ¡rio ("posiÃ§Ã£o" em que o iterador
      // nÃ£o se refere a nenhum elemento propriamente dito).

      // -----------------------------------------------------------------------

      // Este mÃ©todo deve retornar "true" se e somente se
      // o iterador atual e "j" NÃƒO SE REFEREM ao mesmo elemento ou posiÃ§Ã£o do
      // dicionÃ¡rio.

      bool operator != (Iterador j){
        return noh != j.noh;
      }

      // -----------------------------------------------------------------------

      // Este mÃ©todo deve retornar "true" se e somente se
      // o iterador atual e "j" SE REFEREM ao mesmo elemento ou posiÃ§Ã£o do
      // dicionÃ¡rio.

      bool operator == (Iterador j){
        return noh == j.noh;
      }

      // -----------------------------------------------------------------------

      // Os mÃ©todos abaixo possuem como PRÃ‰-CONDIÃ‡ÃƒO o fato de que o iterador
      // aponta para um elemento propriamente dito do dicionÃ¡rio, ou seja,
      // que o iterador nÃ£o aponta para o "fim" do dicionÃ¡rio.
      //
      // Como para toda prÃ©-condiÃ§Ã£o, Ã© responsabilidade do usuÃ¡rio de Iterador
      // garantir que ela serÃ¡ satisfeita sempre que o mÃ©todo for chamado.
      //
      // Portanto, esses mÃ©todos NÃƒO PRECISAM TESTAR se o iterador aponta para o
      // "fim" do dicionÃ¡rio.

      // -----------------------------------------------------------------------

      // Este mÃ©todo deve retornar a "chave" do elemento apontado pelo iterador.

      TC chave (){
        return noh->chave;
      }

      // -----------------------------------------------------------------------

      // Este mÃ©todo deve retornar o "valor" do elemento apontado pelo iterador.

      TV valor (){
        return noh->valor;
      }

      // -----------------------------------------------------------------------
      
      void setIt(Noh* novo){noh = novo;}

      Noh* getIt() {return noh;}

      // -----------------------------------------------------------------------
      
      // Este mÃ©todo deve fazer o iterador passar ao prÃ³ximo elemento do
      // dicionÃ¡rio, isto Ã©, ao elemento da CHAVE SUCESSORA, na ordem crescente
      // das chaves, se houver uma chave sucessora.
      //
      // Caso nÃ£o haja chave sucessora (ou seja, caso o iterador aponte para a
      // maior chave), o iterador deve passar a apontar para o "fim" do
      // dicionÃ¡rio.

      Iterador& operator ++ (){
        if (noh->obter_pai() != nullptr && noh->obter_pai()->chave > noh->chave) {
            if (noh->obter_dir() == nullptr) {
                noh = noh->obter_pai();
            }
            else {
                Noh* aux = noh->obter_dir();
                while (aux->obter_esq() != nullptr) {
                    aux = aux->obter_esq();
                }

                noh = aux;
            }
        }
        else {
            if (noh->obter_dir() != nullptr) {
                Noh* aux = noh->obter_dir();
                while (aux->obter_esq() != nullptr) {
                    aux = aux->obter_esq();
                }

                noh = aux;
            }
            else {
                Noh* aux = noh;
                while (aux->obter_pai() != nullptr && aux->chave > aux->obter_pai()->chave) {
                    aux = aux->obter_pai();
                }

                if (aux->obter_pai() == nullptr) {
                    noh = nullptr;
                }
                else {
                    noh = aux->obter_pai();
                }
            }
        }
      }

      friend DicioAVL;
    }; // class Iterador

   // --------------------------------------------------------------------------

   // MÃ©todos pÃºblicos de DicioAVL:

   // --------------------------------------------------------------------------

   // Construtor: deve inicializar o dicionÃ¡rio como vazio.

   DicioAVL (){
    raiz = nullptr;
   }

   // --------------------------------------------------------------------------

   // Destrutor: deve desalocar toda a memÃ³ria dinamicamente alocada pelo
   // dicionÃ¡rio (no caso, basicamente a Ã¡rvore AVL).

   ~DicioAVL (){
    limparMemoria(this->obter_raiz());
   }

   // --------------------------------------------------------------------------

   // Este mÃ©todo deve retornar um iterador apontando para o elemento de menor
   // chave, caso exista um.
   // Se o dicionÃ¡rio estiver vazio, deve retornar um iterador para o "fim".

   Iterador begin (){
    Iterador novo;
    novo.setIt(procurarMenor(obter_raiz()));
    return novo;
   }


   // --------------------------------------------------------------------------

   // Deve retornar um iterador num estado especial, que seja diferente do
   // estado de um iterador que aponte para um elemento propriamente dito,
   // e que dessa forma sirva para caracterizar a situaÃ§Ã£o em que o iterador
   // tenha atingido o "fim" do dicionÃ¡rio.

   Iterador end (){
    Iterador aux;
    aux.setIt(nullptr);
    return aux;
   }

   // --------------------------------------------------------------------------

   // Este mÃ©todo deve inserir a chave "c" e o valor "v" no dicionÃ¡rio, partindo
   // da PRÃ‰-CONDIÃ‡ÃƒO de que a chave "c" nÃ£o estÃ¡ prenullptre no dicionÃ¡rio,
   // ou seja, a funÃ§Ã£o nÃ£o precisa nem deve fazer esse teste.
   //
   // Em caso de falha de alocaÃ§Ã£o de memÃ³ria,
   // o mÃ©todo deve jogar uma exceÃ§Ã£o do tipo std::bad_alloc
   // (que jÃ¡ Ã© aquele jogada pelo operador "new" em caso de falha de alocaÃ§Ã£o).
   //
   // A funÃ§Ã£o deve retornar um iterador apontando para o elemento inserido.
   //
   // ATENÃ‡ÃƒO: o iterador retornado deve continuar vÃ¡lido e relativo ao par
   // -------  (c,v) enquanto esse par nÃ£o for removido do dicionÃ¡rio.
   //
   // A observaÃ§Ã£o acima Ã© particularmente importante para o caso da REMOÃ‡ÃƒO
   // em que o nÃ³ do par a ser removido possui dois filhos. Nesse caso, nÃ£o
   // basta apenas copiar os campos do nÃ³ sucessor para o nÃ³ em questÃ£o, pois
   // isso faria com que o par sucessor mudasse de nÃ³, invalidando algum
   // iterador relativo a esse par; portanto, nesse caso da remoÃ§Ã£o, Ã©
   // necessÃ¡rio que o nÃ³ do sucessor realmente ocupe o lugar da Ã¡rvore que
   // estava sendo ocupado pelo nÃ³ a ser removido.

   Iterador inserir (TC c, TV v){
        Iterador aux;
        Noh* novo = inserirAvl(&raiz, nullptr, c, v);

        if(novo != nullptr){
            aux.setIt(novo);
        } 

        return aux;
    }

   // --------------------------------------------------------------------------

   // Deve retornar um iterador apontando para o elemento de chave "c",
   // caso essa chave esteja prenullptre no dicionÃ¡rio.
   // Se a chave nÃ£o estiver prenullptre, deve retornar um iterador para o "fim".

   Iterador buscar (TC c){
        Iterador aux;
        Noh* novo = buscarAvl(raiz, c);
        aux.setIt(novo);
        return aux;
    }

   // --------------------------------------------------------------------------

   // Este mÃ©todo deve remover do dicionÃ¡rio o elemento apontado pelo iterador
   // recebido, caso o iterador aponte para um elemento do dicionÃ¡rio.
   //
   // Ã‰ PRÃ‰-CONDIÃ‡ÃƒO da funÃ§Ã£o que o iterador recebido estarÃ¡ apontando
   // para algum elemento ou para o "fim" do dicionÃ¡rio.
   //
   // Se o iterador apontar para o "fim" do dicionÃ¡rio,
   // a funÃ§Ã£o deve simplesmente deixar o dicionÃ¡rio inalterado.

   void remover (Iterador i){
    removerAvl(&raiz, i.chave());
   }

  }; // class DicioAVL

// -----------------------------------------------------------------------------

#endif