#pragma once

#include <iostream>
#include <array>
#include <string>
#include <typeinfo>

#include "function_parser.hpp"
#include "parser_utils.hpp"
#include "lexer.hpp"


using namespace std;


typedef vector<pair<string,string>> token;
typedef vector<pair<string,token>> operation;

class Parser {
  private:
    constexpr static auto declarator = make_array("void", "int");

    vector<token> expressions;
    operation operations;

    vector<string> split_token_to_vector(const token &t){
      vector<string> token_vector;
      for (auto &it:t)
        token_vector.push_back(it.first);
      return token_vector;
    }

    bool is_variable_assignment(const vector<string> &t, string &expression_name){
      static constexpr auto assignment_seq =
        make_array("int", " ", "<NOT FOUND>"," " ,"=", " ", "<NUMBER>", ";");
      expression_name = "<VARIABLE ASSIGNMENT>";
      return Parser_utils::is_vector_equal(t, assignment_seq);
    }

    int standardize_expression(vector<token> &all_expressions){
      for (auto &expression:all_expressions){
        handle_space(expression);
      }
      return SUCCESS;
    }

    bool is_token_valid(pair<string,string> word, size_t single_expression_size){
      if (single_expression_size == 0 && word.first==" ") return false;
      return true;
    };

    void split_to_expressions(const token &all_tokens, vector<token> &all_expressions){
      const string end_of_expression = ";";
      token single_expression;

      for (const pair<string,string> &word : all_tokens){
        if (is_token_valid(word, single_expression.size())){
          single_expression.push_back(word);
        }
        if (word.first == end_of_expression){
          all_expressions.push_back(single_expression);
          single_expression.clear();
        }
      }

      if (single_expression.size() > 0){
        while (single_expression.back().first == " "){
          single_expression.pop_back();
        }
        all_expressions.push_back(single_expression);
      }
    }

    bool is_check_rule(const pair<string,string> &token_ids, const token &rules){
      for (const pair<string, string> &rule:rules){
        if (token_ids == rule){
          return true;
        }
      }
      return false;
    }

    bool is_not_check_rule(const pair<string,string> &token_ids, const token &rules){
      for (const pair<string, string> &rule:rules){
        if (token_ids.first != rule.first && token_ids.second != rule.second){
          return true;
        }
      }
      return false;
    }


    bool is_space_needed(pair<string, string> &current_pair, pair<string,string> &next_pair){
      const token rules_not = {{" ", " "}};
      const token rule_is = {{"int", "<NOT FOUND>"}};

      const pair<string,string> rule_idx = {current_pair.first, next_pair.first};

      return (is_not_check_rule(rule_idx, rules_not) && !is_check_rule(rule_idx, rule_is));
    }

    bool is_exes_space(pair<string, string> &current_pair, pair<string,string> &next_pair){
      const token rules = {{" ", " "}, {" ", ";"}};
      const pair<string,string> rule_idx = {current_pair.first, next_pair.first};
      return is_check_rule(rule_idx, rules);
    }

    void handle_space(token &t){
      const pair<string, string> space_symbol = {" ", " "};

      for (unsigned int idx = 0; idx < t.size()-1; idx++){
        if (is_space_needed(t[idx], t[idx+1])){
          auto it = t.begin() + idx+1;
          t.insert(it, space_symbol);
          idx++;
        }
        if (is_exes_space(t[idx], t[idx+1])){
          auto it = t.begin() + idx;
          t.erase(it);
        }
      }
    }

    int generate_operations(operation &all_operations, vector<token> &all_expressions){
      string expression_buffer;

      for (auto &expression:all_expressions){
        const vector<string> token_string = split_token_to_vector(expression);
        string expression_name;

        if (is_variable_assignment(token_string, expression_buffer)){
          expression_name = expression_buffer;
        }
        else if (Function_parser::is_function(token_string, expression_buffer)){
          expression_name = expression_buffer;
        }
        else{
          expression_name = "<ERROR EXPRESSION>";
        }
        all_operations.push_back({expression_name, expression});

      }
      return SUCCESS;
    }

  public:
    Parser(string program){
      Lexer lexer(program);
      split_to_expressions(lexer.local_token, expressions);
      standardize_expression(expressions);
      generate_operations(operations, expressions);
    }


    void print_expressions()
    {
      for (auto &exp:expressions){
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
      for (auto &op:operations){
        const string op_name = op.first;
        cout << op_name << endl;
        if (op_name == "<ERROR EXPRESSION>"){
          cout << "DEBUG: expression \n";
          print_token(op.second);
        }
      }
    }

    vector<string> get_operations(){
      vector<string> ret_value;
      for (auto &ob:operations){
        ret_value.push_back(ob.first);
      }
      return ret_value;
    }

};
