#include <iostream>

#include "CPU.hpp"

using namespace std;

int main(){

  CPU P("rom.hex", "ram.hex");

  P.run_for_n(5);

  return 0;
}