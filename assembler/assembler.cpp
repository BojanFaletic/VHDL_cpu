#include <iostream>

#include "asm_parse.hpp"

using namespace std;

int main(){

  Asm_parse asm_parse("test.asm");

  asm_parse.print_program();

  return 0;
}