#include <iostream>
#include <vector>
#include <string>

#include "parser.hpp"

using namespace std;


void handle_failure(Parser &obj){
  obj.print_operations();
}

template<typename T, typename U>
bool handle_test_result(T &output, U &expected,
    Parser &p){

  if (output[0] == expected[0]){
    return true;
  }
  else{
    cout << "ERROR while running test\n";
    handle_failure(p);
    return false;
  }
}

bool test_function(){
  Parser p("int a(int v);");
  p.generate_operations();
  auto res = p.operations();

  const vector<string> expects{"<FUNCTION DECLARATION>"};

  return handle_test_result(res, expects, p);

}


bool test_variable(){
  Parser p("int i=7;");
  p.generate_operations();
  auto res = p.operations();

  const vector<string> expects{"<VARIABLE ASSIGNMENT>"};

  return handle_test_result(res, expects, p);
}


void run_test(const string name, auto f_obj){
  const string res = f_obj() ? "SUCCESS" : "FAILED";
  cout << "test " << name;
  cout << " : " << res;
  cout << endl;
}


void test_insert_space(){
  Parser p("");

  vector<pair<string,string>> example_seq = {{"int", "int"},{" ", " "}, {";" , ";"}};

  p.insert_space(example_seq);

  for (auto &a:example_seq){
      cout << "first: " << a.first << " : " << a.second << endl;
  }
}

int main(){

  run_test("variable", test_variable);
  //run_test("function", test_function);

  test_insert_space();

  return 0;
}
