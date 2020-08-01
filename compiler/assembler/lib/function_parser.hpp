#pragma once

#include <vector>
#include <string>
#include <array>
#include <experimental/array>

#include "parser_utils.hpp"

using namespace std;

struct Function_parser : public Parser_utils{
  static bool is_function_declearation(vector<string> t, string &expression_name){
    const vector<vector<string>> assiment_seq_start{{"int", " ", "<NOT FOUND>", "("}};
    const vector<vector<string>> assiment_seq_stop{{")", ";"}};
    const size_t min_number_of_function_param = assiment_seq_start[0].size() + assiment_seq_stop[0].size();

    bool is_valid;
    if (t.size() < min_number_of_function_param){
      return false;
    }

    int number_of_parameters = 0;

    if (is_valid_expression(t, assiment_seq_start)){
      t.erase(t.begin(), t.begin()+assiment_seq_start[0].size());
      number_of_parameters = number_of_function_parameters(t);

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
    expression_name = "<FUNCTION DECLARATION ";
    expression_name += to_string(number_of_parameters);
    expression_name += " >";
    return is_valid;
  }

  static size_t calculate_numer_of_elements(int num_of_args, size_t size_of_one){
    return size_of_one + size_of_one*(num_of_args-1);
  };

  static int number_of_function_parameters(vector<string> &parameters){
    static constexpr auto parameter_template_one =
      experimental::make_array("int", " ", "<NOT FOUND>");
    static constexpr auto parameter_template_many =
      experimental::make_array(",", " ", "int", " ", "<NOT FOUND>");

    int num_of_args = 0;

    if (is_vector_equal(parameters, parameter_template_one,0)){
      num_of_args++;
    }
    else{
      return 0;
    }

    for (size_t i=parameter_template_one.size(); i<parameters.size(); i+= parameter_template_many.size()){
      if (is_vector_equal(parameters, parameter_template_many, i)){
        num_of_args++;
      }
      else{
        const size_t length = calculate_numer_of_elements(num_of_args, parameter_template_one.size());
        parameters.erase(parameters.begin(), parameters.begin()+length);
        return num_of_args;
      }
    }
    return 0;
  }
};
