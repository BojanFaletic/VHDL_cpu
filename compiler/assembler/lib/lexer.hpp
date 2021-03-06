#pragma once

#include <experimental/array>

#include <iostream>
#include <string>
#include <vector>
#include <array>

#include "instructions.hpp"

using namespace std;

const int SUCCESS = 1;
const int ERROR = 0;
const int NOT_FOUND = -1;

typedef vector<pair<string, string>> token;
typedef unsigned int u32;

/*
struct mapping_t{
  vector<int> ROM;
  vector<int> RAM;
  vector<int> DATA;
};
*/

class Lexer{
  static constexpr auto identifiers = experimental::make_array("void", "int", " ", "{", "}", "(", ")", ";", 
    "<NUMBER>", "=", "+", "-", "*", "/", ",", "return");

  protected:
    token local_token;

  private:
    bool is_same_string(const string &msg, const string &pattern){
      if (msg.size() < pattern.size())
        return false;
      for (u32 i=0; i<pattern.size(); i++){
        if (msg[i] != pattern[i])
          return false;
      }
      return true;
    }

    bool is_valid_identifier(const string &msg, pair<string, string> &id){
      for (const auto &search_obj:identifiers){
        if (is_same_string(msg, search_obj)){
          id = {search_obj, search_obj};
          return true;
        }
      }
      return false;
    }

    int distance_to_next_token(string &msg){
      pair<string,string> tmp;
      for (u32 i=0; i<msg.size(); i++){
        const string offset_string = msg.substr(i);
        if (is_valid_identifier(offset_string,tmp))
          return i;
      }
      return NOT_FOUND;
    }

    bool is_number(const string st){
      for (const auto ch:st){
        if (ch < '0' || ch > '9')
          return false;
      }
      return true;
    }

    pair<string, string> handle_undefined_token(string &msg){
      const int distance = distance_to_next_token(msg);
      const string message = msg.substr(0, distance);
      const string ID_name =  (is_number(message)) ? "<NUMBER>" : "<NOT FOUND>";
      return {ID_name, message};
    }

    void merge_tokens(token &all_tokens, const pair<string,string> &rule){
      for (size_t i=0; i<all_tokens.size()-1; i++){
        if (all_tokens[i].first == rule.first &&
            all_tokens[i+1].first == rule.second){
          all_tokens[i].first =  rule.second;
          all_tokens[i].second = string(rule.first) + string(all_tokens[i+1].second);
          const auto it = all_tokens.begin();
          all_tokens.erase(it+i+1);
        }
      }
    };

    void handle_special_case_token(token &all_tokens){
      const pair<string,string> merge_rule = {"int", "<NOT FOUND>"};
      if (all_tokens.size() > 1){
        merge_tokens(all_tokens, merge_rule);
      }
    }

    void handle_token(string &msg, token &all_tokens){
      pair<string, string> item;
      if (not is_valid_identifier(msg,item)){
        item = handle_undefined_token(msg);
      }
      msg.erase(0, item.second.size());
      all_tokens.push_back(item);
    }

    int tokenize(string msg, token &all_tokens){
      int timeout = msg.size();
      while (msg.size()>0){
        if (not timeout--){
          cout << "KILLED\n";
          break;
        }
        handle_token(msg, all_tokens);
      }
      handle_special_case_token(local_token);
      return SUCCESS;
    }


  friend class Parser;
  public:
    Lexer(const string program_src) {
      tokenize(program_src, local_token);
    }


    void print_tokens(){
      for (auto &lt:local_token){
        cout << lt.first << " : " << lt.second << endl;
      }
    }
};
