#pragma once

#include <iostream>
#include <array>
#include <string>
#include <experimental/array>
#include <typeinfo>

#include "lexer.hpp"


using namespace std;


typedef vector<pair<string,string>> token;
typedef vector<pair<string,token>> operation;

class Parser {
  private:
    constexpr static auto delcerators = experimental::make_array("void", "int");

    vector<token> list_of_all_expressions;
    operation all_operations;

    bool is_vector_equal(const auto &v1, const auto &v2){
      if (v1.size() != v2.size())
        return false;
      for (unsigned int i=0; i<v1.size(); i++){
        if (v1[i] != v2[i])
          return false;
      }
      return true;
    }

    vector<string> split_token_to_vector(const token &t){
      vector<string> token_vector;
      for (auto &it:t)
        token_vector.push_back(it.first);
      return token_vector;
    }

    bool is_variable_assignment(const vector<string> &t){
      const vector<vector<string>> assiment_seq{{"int", " ", "<NOT FOUND>", " ", "=", "<NUMBER>", ";"},
                                                {"int", " ", "<NOT FOUND>", "=", "<NUMBER>", ";"}};
      for (auto &it:assiment_seq){
        if (is_vector_equal(t, it))
          return true;
      }

      return false;
    }

    void split_to_expressions(const token &list_of_all_tokens){
      const string end_of_expression = ";";
      token single_expression;

      for (const auto &expression : list_of_all_tokens){
        single_expression.push_back(expression);
        if (expression.first == end_of_expression){
          list_of_all_expressions.push_back(single_expression);
          single_expression.clear();
        }
      }
    }

  public:
    Parser(string program){
      Lexer lexer(program);
      split_to_expressions(lexer.local_token);
    }

    int generate_operations(){
      for (auto &expression:list_of_all_expressions){
        const vector<string> token_string = split_token_to_vector(expression);
        if (is_variable_assignment(token_string)){
          const string expression_name = "<VARIABLE ASSIGNMENT>";
          all_operations.push_back({expression_name, expression});
        }
        else{
          const string expression_name = "<ERROR EXPRESSION>";
          all_operations.push_back({expression_name, expression});

        }
      }
      return SUCCESS;
    }


    void print_expressions()
    {
      for (auto &exp:list_of_all_expressions){
        cout << "New expression\n";
        for (auto &it:exp){
          cout << it.first << " : " << it.second << endl;
        }
        cout << "End of expression\n";
      }
    }

    void print_token(const token &t){
      for (const auto &p:t){
        cout << "Token:" << p.first << " : " << p.second << endl;
      }
    }

    void print_operations(){
      for (auto &op:all_operations){
        const string op_name = op.first;
        cout << op_name << endl;
        if (op_name == "<ERROR EXPRESSION>"){
          cout << "DEBUG: expression \n";
          print_token(op.second);
        }
      }
    }

    vector<string> operations(){
      vector<string> ret_value;
      for (auto &ob:all_operations){
        ret_value.push_back(ob.first);
      }
      return ret_value;
    }


};
