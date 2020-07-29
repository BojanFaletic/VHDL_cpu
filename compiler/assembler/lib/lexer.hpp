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

typedef vector<pair<int, string>> token;
typedef unsigned int u32;


struct mapping_t{
  vector<int> ROM;
  vector<int> RAM;
  vector<int> DATA;
};







class Lexer{

  static constexpr auto gen_token = [] (auto tc){
    constexpr int N = tc.size();
    array<pair<int, const char*>, N> t;
    int id = 0;
    for (const char* it:tc){
      t[id] = pair<int, const char*>{id, it};
      id++;
    }
    return t;
  };


  static constexpr auto identifiers = experimental::make_array("void", "int", " ", "{", "}", "(", ")", ";", "<number>", "=", "+", "-", "*", "/");

  protected:
    static constexpr auto identifiers_token = gen_token(identifiers);
    token local_token;

  private:
    bool is_potencial_candidate(const string &msg, const string &search){
      return (msg.size() >= search.size()) ? true : false;
    }

    bool is_same_string(const string &msg, const string &pattern){
      if (msg.size() < pattern.size())
        return false;
      for (u32 i=0; i<pattern.size(); i++){
        if (msg[i] != pattern[i])
          return false;
      }
      return true;
    }

    bool is_valid_identifier(const string &msg, pair<int, string> &id){
      for (auto &search_obj:identifiers_token){
        if (is_same_string(msg, search_obj.second)){
          id = search_obj;
          return true;
        }
      }
      return false;
    }

    int distance_to_next_token(string &msg){
      pair<int,string> tmp;
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

    static constexpr int get_ID_from_name(const string &name){
      for (auto &it:identifiers_token){
        if (name == it.second)
          return it.first;
      }
      return NOT_FOUND;
    }

    int tokenize(string msg){
      int timeout = msg.size();

      while (msg.size()>0){
        pair<int, string> item;
        if (not is_valid_identifier(msg,item)){
          const int distance = distance_to_next_token(msg);

          int ID_name = NOT_FOUND;
          const string message = msg.substr(0, distance);
          if (is_number(message)){
            ID_name = get_ID_from_name("<number>");
          }
          item = {ID_name, message};
        }
        msg.erase(0, item.second.size());
        local_token.push_back(item);
        if (not timeout--){
          cout << "KILLED\n";
          break;
        }
      }
      return SUCCESS;
    }


  friend class Parser;
  public:
    Lexer(const string program_src) {
      tokenize(program_src);
    }


    void print_tokens(){
      for (auto &lt:local_token){
        cout << lt.first << " : " << lt.second << endl;
      }
    }
};
