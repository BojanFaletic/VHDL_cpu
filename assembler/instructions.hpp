#ifndef INSTRUCTIONS_HPP
#define INSTRUCTIONS_HPP

const int LOAD = 0;
const int STORE = 1;

// Arithmetic operations:
const int ADD = 2;
const int SUB = 3;

// Logic operations:
const int AND = 4;
const int OR = 5;
const int SHIFT_L = 6;
const int SHIFT_R = 7;

// Comparison:
const int JMP_EQ = 8;
const int JMP_NEQ = 9;

// Compares value in accumulator (from previous instruction or return )
const int CMP_EQ = 10;
const int CMP_LT = 11;
const int CMP_GT = 12;

// Jumping instructions:
const int JMP = 13;

// Stack operations:
const int POP = 14;
const int PUSH = 15;

// immediate instruction
const int LOAD_I = 16;
const int STORE_I = 17;

// Arithmetic operations:
const int ADD_I = 18;
const int SUB_I = 19;

// Compares value in accumulator (from previous instruction or return )
const int CMP_EQ_I = 20;
const int CMP_LT_I = 21;
const int CMP_GT_I = 22;


#endif