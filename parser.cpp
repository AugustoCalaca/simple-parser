#include "parser.h"


void Sintatico::incLine() {
    line++;
}

void Sintatico::error(string str = ""){
  cout << "ERROR \nteste.txt::" << line
  << " expected " << str << "\n\n";
  exit(0);
}

void Sintatico::saltBlank() {
  while(tok == BARRAN || tok == WHITE || tok == TAB)
    avancar();
}

void Sintatico::avancar() {
  tok = Lexico::getToken();
  if (Lexico::isEqual(tok, BARRAN))
    incLine();
  Lexico::EraseToken();
}

void Sintatico::eat(int token_consumir) {
  if (Lexico::isEqual(tok, token_consumir)) {
    avancar();
    saltBlank();
  } else {
    if(token_consumir == PONTOVIRGULA)
      error(";");
    if(token_consumir == PROGRAM)
      error("program");
    if(token_consumir == VIRGULA)
      error(",");
    if(token_consumir == FECHAPAR)
      error(")");
    if(token_consumir == DO)
      error("do");
    if(token_consumir == THEN)
      error("then");
  }
}

void Sintatico::programa(){
  line = 1;
  avancar();
  saltBlank();
  eat(PROGRAM);
  identificador();
  eat(PONTOVIRGULA);
  saltBlank();
  bloco();
  saltBlank();
  eat(PONTO);
  cout << "COMPILATION SUCcESS\n";
}

void Sintatico::bloco() {
  if (isEqual(tok,VAR)) {
    variaveis();
  }
  saltBlank();
  // while (isEqual(tok, FUNCTION) || isEqual(tok, PROCEDURE)){
  //   rotina();
  // }
  corpo();
}

void Sintatico::variaveis(){
  eat(VAR);
  do {
    lista_de_identificadores();
    eat(DOISPONTOS);
    tipo();
    eat(PONTOVIRGULA);
  } while (isEqual(tok, LETRA));
}

void Sintatico::rotina() {
  if (isEqual(tok,FUNCTION)) funcao();
  else if (isEqual(tok,PROCEDURE)) procedimento();
}

void Sintatico::funcao() {
  eat(FUNCTION);
  identificador();
  parametros_formais();
  eat(DOISPONTOS);
  identificador();
  eat(PONTOVIRGULA);
  bloco();
  eat(PONTOVIRGULA);
}

void Sintatico::procedimento() {
  eat(PROCEDURE);
  identificador();
  parametros_formais();
  eat(PONTOVIRGULA);
  bloco();
  eat(PONTOVIRGULA);
}

void Sintatico::corpo() {
  eat(BEGIN);
  saltBlank();
  // cout << "deu bom\n";
  while(1) {
    comando();
    // cout << " to aqui na linha " << line << "\n";
    eat(PONTOVIRGULA);
    if(isEqual(tok, END))
      break;
  }
  eat(END);
}

void Sintatico::tipo() {
  if(isEqual(tok, INTEGER))
    avancar();
}

void Sintatico::parametros_formais() {
  if (isEqual(tok, ABREPAR)){
    eat(ABREPAR);
    parametro_formal();
    while (isEqual(tok, PONTOVIRGULA)) {
      eat(PONTOVIRGULA);
      parametro_formal();
    }
    eat(FECHAPAR);
  } else eat(ABREFECHAPAR);
}

void Sintatico::parametro_formal() {
  parametro_expressao();
}

void Sintatico::parametro_expressao() {
  if (isEqual(tok, VAR)) eat(VAR);
  lista_de_identificadores();
  eat(DOISPONTOS);
  identificador();
}

void Sintatico::comando() {
  // cout << "entrando no comando\n";
  comando_sem_rotulo();
  if (isEqual(tok, DIGITO)) {
    numero();
    eat(DOISPONTOS);
  }
}

void Sintatico::variavel() {
  identificador();
}

void Sintatico::comando_sem_rotulo() {
  switch (tok) {
    case BEGIN: composto(); break;
    case IF   : condicional(); break;
    case ELSE : error("then");
    case WHILE: repetitivo(); break;
    case DO : error("while");
    case LETRA:
      identificador();
      if (isEqual(tok, DOISPONTOSIGUAL))
        atribuicao();
      else chamada_de_procedimento();
      break;
    default: saltBlank();
  }
}

void Sintatico::atribuicao() {
  eat(DOISPONTOSIGUAL);
  // cout << "eita\n";
  expressao();
}

void Sintatico::chamada_de_procedimento() {
  if (isEqual(tok,ABREPAR)){
    eat(ABREPAR);
    lista_de_expressoes();
    eat(FECHAPAR);
  } else eat(ABREFECHAPAR);
}

void Sintatico::desvio() {
  // eat(GOTO);
  numero();
}

void Sintatico::composto() {
  eat(BEGIN);
  comando_sem_rotulo();
  while (isEqual(tok,PONTOVIRGULA)) {
    eat(PONTOVIRGULA);
    comando_sem_rotulo();
  }
  eat(END);
}

void Sintatico::condicional() {
  eat(IF);
  expressao();
  eat(THEN);
  comando_sem_rotulo();
  if (isEqual(tok, ELSE)){
    eat(ELSE);
    comando_sem_rotulo();
  }
}

void Sintatico::repetitivo() {
  eat(WHILE);
  expressao();
  eat(DO);
  comando_sem_rotulo();
}

void Sintatico::expressao() {
  expressao_simples();
  if (isEqual(tok,IGUAL) ||
      isEqual(tok,DIFERENTE) ||
      isEqual(tok,MENOR) ||
      isEqual(tok,MENORIGUAL) ||
      isEqual(tok,MAIORIGUAL) ||
      isEqual(tok,MAIOR)) {
    // cout << "era pr eu ta aqui?\n";
    operador_relacional();
    expressao_simples();
  }
}

void Sintatico::operador_relacional() {
  switch (tok) {
    case IGUAL     : eat(IGUAL)     ; break;
    case DIFERENTE : eat(DIFERENTE) ; break;
    case MENOR     : eat(MENOR)     ; break;
    case MENORIGUAL: eat(MENORIGUAL); break;
    case MAIORIGUAL: eat(MAIORIGUAL); break;
    case MAIOR     : eat(MAIOR)     ; break;
  }
}

void Sintatico::expressao_simples() {
  if (isEqual(tok, MAIS)) eat(MAIS);
  else if (isEqual(tok, MENOS)) eat(MENOS);
  termo();
  while (isEqual(tok,MAIS) ||
         isEqual(tok,MENOS)) {
    operador_aditivo();
    // cout << "vai dar merda...\n";
    termo();
    // cout << "..deu merda\n";
  }
  // cout << "cabou expressao\n";
}

void Sintatico::operador_aditivo() {
  switch (tok) {
    case MAIS : eat(MAIS) ; break;
    case MENOS: eat(MENOS); break;
  }
}

void Sintatico::termo() {
  fator();
  while (isEqual(tok, VEZES) ||
         isEqual(tok, BARRA)){
    operador_multiplicativo();
    fator();
  }
}

void Sintatico::operador_multiplicativo() {
  switch (tok) {
    case VEZES: eat(VEZES); break;
    case BARRA: eat(BARRA); break;
  }
}

void Sintatico::fator() {
  switch (tok) {
    case ABREPAR: eat(ABREPAR); expressao(); eat(FECHAPAR); break;
    case DIGITO : numero()    ; break;
    case LETRA  :
      identificador();
      if (isEqual(tok, ABREPAR) || isEqual(tok, ABREFECHAPAR)) {
        chamada_de_funcao();
      }
      break;
  }
}

void Sintatico::chamada_de_funcao() {
  if (isEqual(tok,ABREPAR)) {
    eat(ABREPAR);
    lista_de_expressoes();
    eat(FECHAPAR);
  } else eat(ABREFECHAPAR);
}

void Sintatico::constante() {
  if (isEqual(tok, LETRA)) identificador();
  else {
    if (isEqual(tok, MAIS)) eat(MAIS);
    else if (isEqual(tok, MENOS)) eat(MENOS);
    numero();
  }
}

void Sintatico::numero() {
  do {
    eat(DIGITO);
  } while (isEqual(tok, DIGITO));
}

void Sintatico::identificador() {
  if (Lexico::isEqual(tok, LETRA)) {
    do {
      switch (tok) {
        case DIGITO: eat(DIGITO); break;
        case LETRA : eat(LETRA) ; break;
      }
    } while (Lexico::isEqual(tok, LETRA) || Lexico::isEqual(tok, DIGITO));
  }
  else {
    error("ID valid");
    exit(0);
  }
}

void Sintatico::lista_de_identificadores() {
  identificador();
  while (isEqual(tok,VIRGULA)){
    eat(VIRGULA);
    identificador();
  }
}

void Sintatico::lista_de_numeros() {
  numero();
  while (isEqual(tok,VIRGULA)){
    eat(VIRGULA);
    numero();
  }
}

void Sintatico::lista_de_expressoes() {
  expressao();
  while (isEqual(tok,VIRGULA)) {
    eat(VIRGULA);
    expressao();
  }
}
