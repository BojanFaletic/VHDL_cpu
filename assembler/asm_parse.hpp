#ifndef ASM_PARSE_HPP
#define ASM_PARSE_HPP

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "instructions.hpp"

using namespace std;

void assertm(bool exp, string msg) {
  if (!exp) {
    cout << "ERROR: " << msg << endl;
    exit(1);
  }
}

#define one_line_t vector<string>
#define full_program_t vector<one_line_t>

class Asm_parse {
private:
  full_program_t program;
  vector<int> converted_program;

  int read_file(string filename) {
    ifstream asm_file;
    string line;
    asm_file.open(filename);

    if (asm_file.is_open()) {
      string line;
      while (getline(asm_file, line)) {
        if (line[0] == ';')
          continue;
        cout << line << endl;
        stringstream ss(line);
        one_line_t one_line;
        string word;
        while (ss >> word) {
          one_line.push_back(word);
        }
        program.push_back(one_line);
      }
      asm_file.close();
      return 1;
    }
    return 0;
  }

  bool is_label(one_line_t &line) {
    return line.size() == 3 && line[0].back() == ':';
  }

  int find_destination_line(string pattern) {
    int addr = 0;
    for (one_line_t &line : program) {
      if (is_label(line)) {
        if (line[0] == (pattern + ":")) {
          return addr;
        }
      }
      addr++;
    }
    return -1;
  }

  bool is_label(string &st) {
    if ((st[0] == '0' && tolower(st[1]) == 'x') || isdigit(st[0]))
      return false;
    return true;
  }

  int decode_cmd(string cmd, bool is_immediate) {
    if (is_immediate) {
      if (cmd == "LOAD")
        return LOAD_I;
      if (cmd == "STORE")
        return STORE_I;
      if (cmd == "ADD")
        return ADD_I;
      if (cmd == "CMP_LT")
        return CMP_LT_I;
      if (cmd == "JMP_EQ")
        return JMP_EQ_I;
    } else {
      if (cmd == "LOAD")
        return LOAD;
      if (cmd == "STORE")
        return STORE;
      if (cmd == "JMP")
        return JMP;
      if (cmd == "ADD")
        return ADD;
      if (cmd == "CMP_LT")
        return CMP_LT;
      if (cmd == "JMP_EQ")
        return JMP_EQ;
    }
    return -1;
  }

  int decode_value(string value) {
    const bool is_value = value[0] == '#';
    if (is_value) {
      value.erase(value.begin());
    }

    if (!is_label(value)) {
      return stoi(value, nullptr, 0);
    } else {
      return find_destination_line(value);
    }
  }

  int is_invalid_instruction(int instruction_id) {
    return instruction_id == -1;
  }

  int convert_regular_instruction(one_line_t &line) {
    int cmd_number, instruction;
    if (line.size() < 2)
      return -1;

    int offset = line.size() == 2 ? 0 : 1;

    instruction = decode_value(line[offset + 1]);
    assertm(instruction != -1, line[offset + 1]);

    const bool is_immidiate = line[offset + 1][0] == '#';
    cmd_number = decode_cmd(line[offset], is_immidiate);
    assertm(cmd_number != -1, line[offset]);

    if (is_invalid_instruction(cmd_number) ||
        is_invalid_instruction(instruction))
      return -1;

    int translation_cmd = (cmd_number << 8) | instruction;
    return translation_cmd;
  }

  int convert() {
    for (one_line_t &line : program) {
      int instruction_id = convert_regular_instruction(line);
      assertm(instruction_id != -1, "Invalid instruction id: " + line[0]);
      converted_program.push_back(instruction_id);
    }
    return 1;
  }

public:
  Asm_parse(string filename) {
    if (!read_file(filename)) {
      cout << filename + " not found\n";
    }

    convert();
  }

  void print_program() {
    for (int el : converted_program) {
      cout << el << endl;
    }
  }
};

#endif
