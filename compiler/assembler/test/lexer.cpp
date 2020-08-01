#include <iostream>
#include <string>
#include <cmath>
#include "lexer.hpp"

using namespace std;



template <typename T>
void print_vector(T name){
  for (auto i:name)
    cout << i << endl;
}


int assertm(bool is_correct, string msg){
  if (!is_correct){
    cout << msg << endl;
    return SUCCESS;
  }
  return ERROR;
}


template <typename T>
int check_if_equal(T test, T expected){
  int status = SUCCESS;
  unsigned int distance = min(test.size(), expected.size());
  status &= assertm(test.size()==expected.size(), "Size do not match");

  for (unsigned int i=0; i<distance; i++){
    status &= assertm(test[i]==expected[i], "Item are not same:" +
        string(test[i]) + " != " + string(expected[i]));
  }
  return status;
}



int main(){


  // expected function
  // test_definition();
  Lexer l("inta = 7");
  l.print_tokens();

  return 0;
}
