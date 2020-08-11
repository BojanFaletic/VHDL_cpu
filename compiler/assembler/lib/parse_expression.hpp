#pragma once

#include <string>
#include <vector>

#include "utils.hpp"

using namespace std;

struct Parse_expression {

  static bool is_token_valid(pair<string,string> word, size_t single_expression_size){
    if (single_expression_size == 0 && word.first==" ") return false;
    return true;
  };


  static void split_to_expressions(const token &all_tokens,
                                   vector<token> &all_expressions) {

    const string end_of_expression = ";";
    const string start_bracket = "{";
    const string end_bracket = "}";

    token single_expression;

    for (const pair<string, string> &word : all_tokens) {
      if (is_token_valid(word, single_expression.size())) {
        single_expression.push_back(word);
      }
      if (word.first == end_of_expression) {
        all_expressions.push_back(single_expression);
        single_expression.clear();
      }
    }

    if (single_expression.size() > 0) {
      while (single_expression.back().first == " ") {
        single_expression.pop_back();
      }
      all_expressions.push_back(single_expression);
    }
  }
};
