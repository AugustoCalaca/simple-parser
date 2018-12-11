#include <iostream>

#include "parser.h"
using namespace std;

int main (int argc, char *argv[]){
  Sintatico novo;
  novo.AnalisadorLexico();
  // novo.printTokens();
  novo.programa();

  return 0;
}
