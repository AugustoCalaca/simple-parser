#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Tokens {
  protected:
    int getToken ();
    void printTokens ();
    void Inverter ();
    bool isEqual (int tok_, int need);
    bool NextIsEqual (int t);
    bool IsReservada (string palavra);
    void setToken (int new_token);
    void setToken (int new_token, int qnt);
    void EraseToken ();
    enum automato_reservadas {
      LETRA = 2,
      DIGITO,
      IGUAL,
      MENOR,  // 5
      MAIOR,
      MAIS,
      MENOS,
      VEZES,
      BARRA, // 10
      DOISPONTOS,
      ABREPAR,
      FECHAPAR,
      ABRECOCH,
      FECHACOCH, // 15
      ABRECOMENTARIO,
      FECHACOMENTARIO,
      VIRGULA,
      BARRAN,
      WHITE, // 20
      PONTOVIRGULA,
      PONTO,
      TAB,
      BARRABARRA,
      ABREFECHAPAR, // 25
      ABREFECHACOMENTARIO,
      DOISPONTOSIGUAL,
      DIFERENTE,
      MENORIGUAL,
      MAIORIGUAL // 29
    };

    enum reservadas {
      ABSOLUTE = 30,
      IF,
      THEN,
      ELSE,
      BEGIN,
      FUNCTION, // 35
      TO,
      INTEGER, // 40
      PROCEDURE,
      PROGRAM,
      VAR,
      WHILE,
      DO,
      END,
      UNDER,
      EXIT // 53
    };

  private:
    vector<int> Token;
};
