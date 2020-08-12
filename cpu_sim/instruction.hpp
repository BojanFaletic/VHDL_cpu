#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP


// load instruction

const int LOAD_C_R0 = 0;
const int LOAD_C_R1 = 1;

const int LOAD_A_R0 = 2;
const int LOAD_A_R1 = 3;

// store instruction

const int STORE_R0_A = 4;
const int STORE_R1_A = 5;

// Arithmetic

const int ADD_R0_R1 = 6; // store sum in R0
const int SUB_R0_R1 = 7; // subtract R0 = R0-R1
// Comparison

const int CMP_LT_RO = 8; //  if sum is less than R0
const int CMP_EQ_RO = 9; //  if sum is equal R0
const int CMP_GT_RO = 10; //  if sum is more  than R0

// Jump
const int JMP_LT = 11; // jump if CMP was successfull
const int JMP_EQ = 12; // jump if CMP was successfull
const int JMP_GT = 13; // jump if CMP was successfull
const int JMP_N = 14; // jump if CMP was unsuccessfull


#endif