#include <fstream>

#include "lexicon.h"

using namespace std;


Lexico::Lexico() {
  for (int i = 0; i < estados; i++){
    for (int j = 0; j < alfabeto; j++){
      automato[i][j] = 0;
    }
  }

  automato[1][0]   = LETRA;
  automato[1][1]   = DIGITO;
  automato[1][2]   = IGUAL;
  automato[1][3]   = MENOR;
  automato[1][4]   = MAIOR;
  automato[1][5]   = MAIS;
  automato[1][6]   = MENOS;
  automato[1][7]   = VEZES;
  automato[1][8]   = BARRA;
  automato[1][9]   = DOISPONTOS;
  automato[1][10]  = ABREPAR;
  automato[1][11]  = FECHAPAR;
  automato[1][12]  = ABRECOCH;
  automato[1][13]  = FECHACOCH;
  automato[1][14]  = ABRECOMENTARIO;
  automato[1][15]  = FECHACOMENTARIO;
  automato[1][16]  = VIRGULA;
  automato[1][17]  = BARRAN;
  automato[1][18]  = WHITE;
  automato[1][19]  = PONTOVIRGULA;
  automato[1][20]  = PONTO;
  automato[1][21]  = TAB;
  automato[LETRA][LETRA - 2]   = LETRA;
  automato[DIGITO][DIGITO - 2] = DIGITO;
  automato[MENOR][IGUAL - 2]   = MENORIGUAL;
  automato[MENOR][MAIOR - 2]   = DIFERENTE;
  automato[MAIOR][IGUAL - 2]   = MAIORIGUAL;
  automato[DOISPONTOS][IGUAL - 2]   = DOISPONTOSIGUAL;
  automato[BARRA][BARRA - 2]  = BARRABARRA;
  automato[ABREPAR][FECHAPAR - 2]  = ABREFECHAPAR;
  automato[ABRECOMENTARIO][FECHACOMENTARIO - 2]  = ABREFECHACOMENTARIO;

  indice[0]  = 'a';
  indice[1]  = '0';
  indice[2]  = '=';
  indice[3]  = '<';
  indice[4]  = '>';
  indice[5]  = '+';
  indice[6]  = '-';
  indice[7]  = '*';
  indice[8]  = '/';
  indice[9]  = ':';
  indice[10] = '(';
  indice[11] = ')';
  indice[12] = '[';
  indice[13] = ']';
  indice[14] = '{';
  indice[15] = '}';
  indice[16] = ',';
  indice[17] = '\n';
  indice[18] = ' ';
  indice[19] = ';';
  indice[20] = '.';
  indice[21] = '\t';
}

int Lexico::PosicaoIndice (char ch) {
  int i = 2;
  while (i < alfabeto) {
    if (ch == indice[i])
      return i;
    i++;
  }
  if (isalpha(ch))
    return 0;
  if (isdigit(ch))
    return 1;
  return -1;
}

bool Lexico::isFinal (int estado) {
  if (estado != 1 && estado != 0) return true;
  else return false;
}

void Lexico::AnalisadorLexico() {
  ifstream fin ("/media/augusto/Augusto/Documentos/Codigos/simple-parser/test.txt", ifstream::in);
  vector<char> caracter;
  char ch;
  int i, j;

  while (fin.get(ch)) {
    caracter.push_back(ch);
  }

  fin.clear();
  fin.close();
  int current_state = 1;
  int final_state = 0;
  int indice_caracter;
  string palavra;
  i = j = 0;
  while (i < caracter.size()) {
    indice_caracter = PosicaoIndice(caracter[i]);
    // cout << " " << caracter[i] << " | " << current_state << " -> " << indice_caracter << "\n";
    if (indice_caracter == -1 && current_state != 1) current_state = 0;
    if (indice_caracter == -1 && current_state == 1) current_state = estado_erro;
    if (indice_caracter != -1) current_state = automato[current_state][indice_caracter];

    if (isFinal(current_state)) final_state = current_state;

        // cout << caracter[i];
    if (current_state != 0) {
      if (current_state == 2 ) {
       palavra.push_back(caracter[i]);
      }
      i++;
    }
    if (current_state == estado_erro) {
      cout << "\nExpected caracter valid!!\n\n";
      exit(0);
    }
    if (current_state == 0) {
      if (final_state == 2 || final_state == UNDER) {
        // cout << "palavra: " << palavra << "\n";
        if (Tokens::IsReservada(palavra));
        else Tokens::setToken(2, palavra.size());
        palavra.clear();
      }
      else Token(final_state);
      current_state = 1;
      final_state = 0;
    }
  }
  Token (final_state);
  Inverter();
}

void Lexico::Token (int final) {
	switch (final) {
		case 3 : Tokens::setToken (3) ; break;
		case 4 : Tokens::setToken (4) ; break;
    case 5 : Tokens::setToken (5) ; break;
    case 6 : Tokens::setToken (6) ; break;
		case 7 : Tokens::setToken (7) ; break;
		case 8 : Tokens::setToken (8) ; break;
		case 9 : Tokens::setToken (9) ; break;
		case 10: Tokens::setToken (10); break;
		case 11: Tokens::setToken (11); break;
    case 12: Tokens::setToken (12); break;
    case 13: Tokens::setToken (13); break;
    case 14: Tokens::setToken (14); break;
    case 15: Tokens::setToken (15); break;
    case 16: Tokens::setToken (16); break;
    case 17: Tokens::setToken (17); break;
    case 18: Tokens::setToken (18); break;
    case 19: Tokens::setToken (19); break;
    case 20: Tokens::setToken (20); break;
    case 21: Tokens::setToken (21); break;
    case 22: Tokens::setToken (22); break;
    case 23: Tokens::setToken (23); break;
    case 24: Tokens::setToken (24); break;
    case 25: Tokens::setToken (25); break;
    case 26: Tokens::setToken (26); break;
    case 27: Tokens::setToken (27); break;
    case 28: Tokens::setToken (28); break;
    case 29: Tokens::setToken (29); break;
    case UNDER: Tokens::setToken (2) ; break;
    case ABSOLUTE: break;
  }
}
