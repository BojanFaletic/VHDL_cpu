#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "instruction.hpp"

using namespace std;

template <typename T> void write_file(ofstream &f_name, T &content) {
  if (content.size() > 0) {
    for (pair<int, int> el : content) {
      const int data = (el.first << 8) | el.second;
      f_name << data << endl;
    }
  }
  f_name.close();
}

template <typename T> void gen_memory(T rom_content, T ram_content) {
  ofstream rom_file("rom.hex");
  ofstream ram_file("ram.hex");

  write_file(rom_file, rom_content);
  write_file(ram_file, ram_content);
}

int main() {

  const vector<pair<int, int>> prog_ROM = {{LOAD_C_R0, 5}};

  const vector<pair<int, int>> prog_RAM = {{}};

  gen_memory(prog_ROM, prog_RAM);

  return 0;
}