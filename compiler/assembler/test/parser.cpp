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

  if (output == expected){
    return true;
  }
  else{
    cout << "ERROR while running test\n";
    handle_failure(p);
    return false;
  }
}

template<typename T>
void run_test(const string name, T f_obj){
  const string res = f_obj() ? "SUCCESS" : "FAILED";
  cout << "test " << name;
  cout << " : " << res;
  cout << endl;
}

bool test_function(){
  int test_scoreboard = 0;

  // test 1 argument
  {
  Parser p("int a(int v);");
  auto res = p.get_operations();

  vector<string> expects{"<FUNCTION DECLARATION 1 >"};
  test_scoreboard += handle_test_result(res, expects, p) ? 1 : 0;
  }

  {
  // test 2 arguments
  Parser p("int a(int v, int b);");
  auto res = p.get_operations();

  vector<string> expects{"<FUNCTION DECLARATION 2 >"};
  test_scoreboard += handle_test_result(res, expects, p) ? 1 : 0;
  }

  {
  // test 3 arguments
  Parser p("int a(int v, int b, int c);");
  auto res = p.get_operations();

  vector<string> expects{"<FUNCTION DECLARATION 3 >"};
  test_scoreboard += handle_test_result(res, expects, p) ? 1 : 0;
  }
  return test_scoreboard==3;
}


bool test_variable(){
  int test_scoreboard = 0;

  {
  Parser p("int i=  7;");
  auto res = p.get_operations();

  const vector<string> expects{"<VARIABLE ASSIGNMENT>"};


  test_scoreboard += handle_test_result(res, expects, p) ? 1 : 0;
  }

  {
  Parser p("int i=7; int j = 8;");
  auto res = p.get_operations();

  const vector<string> expects{"<VARIABLE ASSIGNMENT>", "<VARIABLE ASSIGNMENT>"};

  test_scoreboard += handle_test_result(res, expects, p) ? 1 : 0;
  }

  return test_scoreboard == 2;
}

bool test_random(){
  Parser p("8 ");
  auto res = p.get_operations();

  const vector<string> expects{"<VARIABLE ASSIGNMENT>"};

  return handle_test_result(res, expects, p);
};


bool test_fx(){
  Parser p("int f(int a){int a=5; return a};");
  auto res = p.get_operations();

  const vector<string> expects{"<FUNCTION BODY 1 >"};

  return handle_test_result(res, expects, p);

}

int main(){

  //run_test("variable", test_variable);
  //run_test("function", test_function);
  //run_test("random", test_random);

  run_test("f body", test_fx);

  return 0;
}
