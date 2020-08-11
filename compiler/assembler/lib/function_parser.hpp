#pragma once
#include "parser_utils.hpp"
#include "utils.hpp"

#include <array>
#include <iostream>
#include <string>
#include <vector>


using namespace std;

struct Function_parser : public Parser_utils {
  s_auto decleration_start =
      make_2d_array("int", " ", "<NOT FOUND>", " ", "(", " ");
  s_auto decleration_stop = make_2d_array(")", ";");
  s_auto definition_stop = make_2d_array(")", " ", "{");
  s_const size_t min_size_of_t =
      decleration_start[0].size() +
      min(decleration_stop[0].size(), definition_stop[0].size());

  s_auto one_f_param = make_array("int", " ", "<NOT FOUND>", " ");
  s_auto many_f_param = make_array(",", " ", "int", " ", "<NOT FOUND>", " ");
  s_auto f_body_end = make_array("}", ";");

  s_const int function_definition = 1;
  s_const int function_decleration = 2;
  s_const int not_found = 0;

  static string create_decleration_name(size_t param_size) {
    return string("<FUNCTION DECLARATION ") + to_string(param_size) +
           string(" >");
  }

  static string create_body_name(size_t param_size) {
    return string("<FUNCTION BODY ") + to_string(param_size) + string(" >");
  }

  static int is_deceleration_or_definition(vector<string> &t) {
    if (is_valid_expression(t, decleration_stop)) {
      t.erase(t.begin(), t.begin() + decleration_stop[0].size());
      return function_decleration;
    } else if (is_valid_expression(t, definition_stop)) {
      t.erase(t.begin(), t.begin() + definition_stop[0].size());
      return function_definition;
    }
    return not_found;
  }

  static int is_function_head(vector<string> &t, size_t &num_of_args) {
    if (is_valid_expression(t, decleration_start)) {
      t.erase(t.begin(), t.begin() + decleration_start[0].size());
      num_of_args = number_of_function_parameters(t);
      return is_deceleration_or_definition(t);
    }
    return 0;
  }

  static bool is_function(vector<string> t, string &expression_name) {
    if (t.size() < min_size_of_t) {
      return false;
    }

    size_t number_of_parameters = -1;
    int function_type = is_function_head(t, number_of_parameters);
    if (function_type == not_found) {
      return false;
    } else if (function_type == function_decleration) {
      expression_name = create_decleration_name(number_of_parameters);
      return true;
    } else if (function_type == function_definition) {
      expression_name = create_body_name(number_of_parameters);
      if (is_function_body_valid(t)) {
        return true;
      }
      return false;
    }
    return false;
  }

  static size_t calculate_numer_of_elements(int num_of_args) {
    return one_f_param.size() + many_f_param.size() * (num_of_args - 1);
  };

  static int number_of_function_parameters(vector<string> &parameters) {
    int num_of_args = 0;
    if (is_vector_equal(parameters, one_f_param, 0))
      num_of_args++;

    for (size_t i = one_f_param.size(); i < parameters.size();
         i += many_f_param.size()) {
      if (is_vector_equal(parameters, many_f_param, i)) {
        num_of_args++;
      } else {
        const size_t length = calculate_numer_of_elements(num_of_args);
        parameters.erase(parameters.begin(), parameters.begin() + length);
        return num_of_args;
      }
    }
    return 0;
  }

  static bool is_function_body_valid(vector<string> &t) {
    while (t.size() >= f_body_end.size()) {
      if (is_vector_equal(t, f_body_end)){
        return true;
      }
      t.erase(t.begin());
    }
    return false;
  }
};
