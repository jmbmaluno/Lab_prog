// -----------------------------------------------------------------------------
// Universidade Federal do CearÃ¡, Centro de CiÃªncias, Departamento de ComputaÃ§Ã£o
// Disciplina: LaboratÃ³rio de ProgramaÃ§Ã£o - CK0215 2023.1 T01A
// Professor: Pablo Mayckon Silva Farias
//
// Material para a Aula 24, em 12/06/2023.
//
// Interface para ImplementaÃ§Ã£o de DicionÃ¡rio baseado em Ãrvore BinÃ¡ria de Busca
// -----------------------------------------------------------------------------

#ifndef DICIOABB_HPP
#define DICIOABB_HPP

// -----------------------------------------------------------------------------

template <typename TC, typename TV>
class DicioABB
  {
   //Definições internas, campos da classe, etc.
   struct Noh {TC chave; TV valor; Noh* esq, Noh* dir, Noh* pai};

   Noh sent;
   Noh raiz;

   public:

   class Iterador
     {
      // Definições internas, campos da classe, etc.
      Noh *noh;
      public:

      // -----------------------------------------------------------------------

      // Retorna a chave do par apontado pelo iterador.
      TC chave () { return noh->chave; }

      // -----------------------------------------------------------------------

      // Retorna o valor do par apontado pelo iterador.
      TV valor () { return noh->valor; }

      // -----------------------------------------------------------------------

      Iterador (Noh *n) : noh{n} { }

      // -----------------------------------------------------------------------

      // Faz o iterador passar para o nó sucessor, caso haja,
      // ou então para o "fim", caso não haja sucessor.
      Iterador& operator ++ ()
        {
            if(noh.esq == sent){
                TV aux = noh.chave;
                while(noh != sent && noh.pai.chave < aux){
                    noh = noh.pai;
                }

            }
        }

      // -----------------------------------------------------------------------


      // Informa se o iterador atual aponta
      // para o mesmo elemento apontado por "j".
      bool operator == (Iterador j) { return noh == j.noh; }

      // -----------------------------------------------------------------------

      // Informa se o iterador atual aponta
      // para um elemento diferente daquele apontado por "j".
      bool operator != (Iterador j) { return noh != j.noh; }

      // -----------------------------------------------------------------------

      friend DicioABB;

     };   // class Iterador

   // --------------------------------------------------------------------------

   // Retorna um iterador para o menor elemento do dicionÃ¡rio,
   // ou para o "fim", caso nÃ£o haja elementos.
   Iterador begin ()
     {
      
     }

   // --------------------------------------------------------------------------

   // Retorna um iterador para o "fim" do dicionÃ¡rio ("apÃ³s o Ãºltimo").
   Iterador end () { return {&sent}; }

   // --------------------------------------------------------------------------

   // Inicializa o DicionÃ¡rio, deixando-o no estado vazio.
   DicioABB () { ... /* TODO */ }

   // --------------------------------------------------------------------------

   // Desaloca a memÃ³ria utilizada pelo dicionÃ¡rio.
   ~DicioABB () { ... /* TODO */ }

   // --------------------------------------------------------------------------

   // Se a chave "c" nÃ£o pertencer ao dicionÃ¡rio,
   // insere o par (c,v), retornando um iterador para o par inserido.
   // Joga std::bad_alloc em caso de falha de alocaÃ§Ã£o de memÃ³ria.
   //
   // Se a chave "c" jÃ¡ estiver no dicionÃ¡rio,
   // retorna um iterador para o par da chave "c",
   // sem modificar o dicionÃ¡rio.
   Iterador inserir (TC c, TV v)
     {
      ... // TODO
     }

   // --------------------------------------------------------------------------

   // Retorna um iterador apontando para o par da chave "c", caso ela ocorra;
   // Em caso contrÃ¡rio, retorna um iterador para o "fim".
   Iterador buscar (TC c)
     {
      ... // TODO
     }

   // --------------------------------------------------------------------------

   // PrÃ©-condiÃ§Ã£o: o iterador "i" necessariamente se refere a um par/nÃ³
   //               da Ã¡rvore, ou entÃ£o para o "fim".
   //
   // Remove o par apontado pelo iterador recebido,
   // exceto se o iterador apontar para o "fim",
   // caso em que a funÃ§Ã£o nÃ£o altera o dicionÃ¡rio.

   void remover (Iterador i)
     {
      ... // TODO
     }

  };  // class DicioABB

// -----------------------------------------------------------------------------

#endif