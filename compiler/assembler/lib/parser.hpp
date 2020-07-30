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

    bool is_vector_equal(const auto &v1, const auto &v2, const int v2_offset = 0){
      if (v1.size() != v2.size())
        return false;
      if (v2.size()-v2_offset < v1.size())
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

    bool is_valid_expression(const vector<string> &expression, const vector<vector<string>> &assiment_seq){
      for (auto &it:assiment_seq){
        if (is_vector_equal(expression, it))
          return true;
      }
      return false;
    }

    bool is_variable_assignment(const vector<string> &t, string &expression_name){
      const vector<vector<string>> assiment_seq{{"int", " ", "<NOT FOUND>", " ", "=", "<NUMBER>", ";"},
                                                {"int", " ", "<NOT FOUND>", "=", "<NUMBER>", ";"}};
      expression_name = "<VARIABLE ASSIGNMENT>";
      return is_valid_expression(t, assiment_seq);
    }

    int number_of_function_parameters(vector<string> &parameters){
      const vector<string> parameter_template = {"int", " ", "<NOT FOUND>"};
      int num_of_args = 0;
      for (unsigned int i=0; i<parameters.size(); i+= parameter_template.size()){
        if (is_vector_equal(parameter_template, parameters, i)){
          num_of_args++;
        }
        else{
          return num_of_args;
        }
      }
      return num_of_args;
    }


    bool is_function_declearation(vector<string> t, string &expression_name){
      const vector<vector<string>> assiment_seq{{"int", " ", "<NOT FOUND>", "(", "int", " ", "<NOT FOUND>", ")", ";"}};


      const vector<vector<string>> assiment_seq_start{{"int", " ", "<NOT FOUND>", "("}};
      const vector<vector<string>> assiment_seq_stop{{")", ";"}};

      bool is_valid;

      int number_of_parameters = 0;

      if (is_valid_expression(t, assiment_seq_start)){
        t.erase(t.begin(), t.begin()+assiment_seq_start.size());
        number_of_parameters = number_of_function_parameters(t);
        t.erase(t.begin(), t.begin()+3*number_of_parameters);
        if (is_valid_expression(t, assiment_seq_stop)){
          is_valid = true;
        }
        else{
          is_valid = false;
        }
      }
      else{
        is_valid = false;
      }


      expression_name = "<FUNCTION DECLARATION>";
      expression_name += "<";
      expression_name += to_string(number_of_parameters);
      expression_name += ">";
      return is_valid;
    }


    int standardize_expression(){
      for (auto &expression:list_of_all_expressions){
      }
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
      string expression_buffer;

      for (auto &expression:list_of_all_expressions){
        const vector<string> token_string = split_token_to_vector(expression);
        string expression_name;

        if (is_variable_assignment(token_string, expression_buffer)){
          expression_name = expression_buffer;
        }
        else if (is_function_declearation(token_string, expression_buffer)){
          expression_name = expression_buffer;
        }
        else{
          expression_name = "<ERROR EXPRESSION>";
        }
        all_operations.push_back({expression_name, expression});

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


    bool is_space_needed(pair<string, string> &current_pair, pair<string,string> &next_pair){
      if (current_pair.first != " " && next_pair.first != " "){
        if (current_pair.first == "int" && next_pair.first == "int")
          return false;
        else
          return true;
      }
      return false;
    }

    void insert_space(token &t){
      const pair<string, string> space_symbol = {" ", " "};

      for (unsigned int idx = 0; idx < t.size()-1; idx++){
        if (is_space_needed(t[idx], t[idx+1])){
          auto it = t.begin() + idx;
          t.insert(it, space_symbol);
          idx++;
        }
      }
    }

};
