#ifndef CPU_HPP
#define CPU_HPP

#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "instruction.hpp"

using namespace std;

#define ROM_SIZE 256
#define RAM_SIZE 256

void assert(bool expr, string msg) {
  if (!expr) {
    cout << "ASSERT ERROR: " + msg;
    exit(1);
  }
}

class CPU {
  array<int, ROM_SIZE> ROM;
  array<int, RAM_SIZE> RAM;
  int PC;
  bool zero, overflow, eq, less, greater;
  int R0, R1;

  void increment_PC() { PC = PC == 256 ? 0 : PC + 1; }

  void clear_flags() {
    zero = false;
    overflow = false;
    eq = false;
    less = false;
    greater = false;
  }

  void execute_current_instruction(int instruction_code) {
    const int data_size = 8;
    const int instruction_id = instruction_code >> data_size;
    const int instruction_value = (data_size - 1) & instruction_code;

    switch (instruction_id) {
    case LOAD_A_R0:
      R0 = RAM[instruction_value];
      clear_flags();
      break;
    case LOAD_A_R1:
      R1 = RAM[instruction_value];
      clear_flags();
      break;
    case LOAD_C_R0:
      R0 = instruction_value;
      clear_flags();
      break;
    case LOAD_C_R1:
      R1 = instruction_value;
      clear_flags();
      break;
    case ADD_R0_R1:
      R0 += R1;
      clear_flags();
      if (R0 > 255) {
        overflow = true;
      }
      break;
    case CMP_LT_RO:
      clear_flags();
      if (R0 < instruction_value) {
        less = true;
      }
      break;
    case CMP_EQ_RO:
      clear_flags();
      if (R0 == instruction_value) {
        eq = true;
      }
      break;
    case CMP_GT_RO:
      clear_flags();
      if (R0 < instruction_value) {
        greater = true;
      }
      break;
    case JMP_LT:
      if (less) {
        PC = instruction_value;
      }
      clear_flags();
      break;
    case JMP_EQ:
      if (eq) {
        PC = instruction_value;
      }
      clear_flags();
      break;
    case JMP_GT:
      if (greater) {
        PC = instruction_value;
      }
      clear_flags();
      break;
    case JMP_N:
      if (!less && !eq && !less) {
        PC = instruction_value;
      }
      clear_flags();
      break;

    default:
      cout << "Unable to decode instruction! " << instruction_id << endl;
      break;
    }
  }

  void step_program() {}

  int read_program(string file_name, bool is_RAM) {
    ifstream file;
    file.open(file_name);
    if (file.is_open()) {
      int line;
      unsigned int i = 0;
      while (file >> line) {
        if (is_RAM)
          RAM[i++] = line;
        else
          ROM[i++] = line;
      }
      file.close();
      return 1;
    } else {
      return -1;
    }
  }

public:
  CPU(string ROM_file, string RAM_file) {
    if (read_program(ROM_file, false) != 1) {
      cout << "ERROR: ROM file not found!\n";
      exit(1);
    }
    if (read_program(RAM_file, true) != 1) {
      cout << "ERROR: ROM file not found!\n";
      exit(1);
    }
  }

  void run_for_n(unsigned int num_of_cycles) {
    for (unsigned int i = 0; i < num_of_cycles; i++) {
      const int current_instruction = ROM[PC];
      execute_current_instruction(current_instruction);
    }
  }
};

#endif