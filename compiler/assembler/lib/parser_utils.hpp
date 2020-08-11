#pragma once

#include <vector>
#include <string>
#include <array>

using namespace std;

struct Parser_utils{
  template<typename T>
  static bool is_valid_expression(const vector<string> &expression,
      const T &assignment_seq){
    for (auto &it:assignment_seq){
      if (is_vector_equal(expression, it))
        return true;
    }
    return false;
  }

  template<typename T>
  static bool is_vector_equal(const vector<string> &expression,
      const T &pattern, const int expression_offset = 0){
    if (expression.size()-expression_offset < pattern.size())
      return false;
    for (unsigned int i=0; i<pattern.size(); i++){
      if (expression[i+expression_offset] != pattern[i])
        return false;
    }
    return true;
  }
};
