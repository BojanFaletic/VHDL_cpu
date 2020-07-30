#include <iostream>
#include <vector>
#include <string>

#include "parser.hpp"

using namespace std;

bool test_function(){
  Parser p("int a(int v){};");
  p.generate_operations();
  auto res = p.operations();

  const vector expects = {"<FUNCTION ASSIGNMENT>"};
  return (res[0] == expects[0]) ? true : false;
}


bool test_variable(){
  Parser p("int i=7;");
  p.generate_operations();
  auto res = p.operations();

  const vector expects = {"<VARIABLE ASSIGNMENT>"};
  return (res[0] == expects[0]) ? true : false;
}


void run_test(const string name, auto f_obj){
  const string res = f_obj() ? "SUCCESS" : "FAILED";
  cout << "test " << name;
  cout << " : " << res;
  cout << endl;
}

int main(){

  run_test("variable", test_variable);
  run_test("function", test_function);

  return 0;
}
