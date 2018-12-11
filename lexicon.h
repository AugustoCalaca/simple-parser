#include <string>
#include "token.h"

#define estados 35 // fazer o automato e confirmar valor
#define alfabeto 35 // confirmar
#define estado_erro 60

class Lexico : public Tokens{
  public:
    void AnalisadorLexico ();
    int PosicaoIndice (char ch);
    bool isFinal (int estado);
    void print ();
    void iniciar();
    Lexico();
    void Token (int final);
  private:
    int automato [estados][alfabeto];
    char indice [alfabeto];
  };
