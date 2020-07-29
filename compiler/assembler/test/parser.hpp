#pragma once

#include <iostream>
#include <array>
#include <string>

#include "lexer.hpp"


using namespace std;

class Parser {
  public:
    Parser(string program){
      Lexer lexer(program);

      cout << lexer.local_token[0].first << endl;

    }


};
