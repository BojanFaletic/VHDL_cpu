LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

-- each command has 4b instruction + 8b address
PACKAGE instruction_pkg IS
  CONSTANT INSTRUCTION_WIDTH : INTEGER := 5;
  CONSTANT DATA_WIDTH_C : INTEGER := 8;
  CONSTANT FULL_WIDTH_C : INTEGER := DATA_WIDTH_C + INSTRUCTION_WIDTH;

  CONSTANT LOAD_C_R0 : std_logic_vector(INSTRUCTION_WIDTH - 1 DOWNTO 0) := "00000";
  CONSTANT LOAD_C_R1 : std_logic_vector(INSTRUCTION_WIDTH - 1 DOWNTO 0) := "00001";
  CONSTANT LOAD_A_R0 : std_logic_vector(INSTRUCTION_WIDTH - 1 DOWNTO 0) := "00010";
  CONSTANT LOAD_A_R1 : std_logic_vector(INSTRUCTION_WIDTH - 1 DOWNTO 0) := "00011";

  CONSTANT STORE_R0_A : std_logic_vector(INSTRUCTION_WIDTH - 1 DOWNTO 0) := "00100";
  CONSTANT STORE_R1_A : std_logic_vector(INSTRUCTION_WIDTH - 1 DOWNTO 0) := "00101";

  CONSTANT ADD_R0_R1 : std_logic_vector(INSTRUCTION_WIDTH - 1 DOWNTO 0) := "00110";
  CONSTANT SUB_R0_R1 : std_logic_vector(INSTRUCTION_WIDTH - 1 DOWNTO 0) := "00111";

  CONSTANT CMP_LR_R0 : std_logic_vector(INSTRUCTION_WIDTH - 1 DOWNTO 0) := "01000";
  CONSTANT CMP_EQ_R0 : std_logic_vector(INSTRUCTION_WIDTH - 1 DOWNTO 0) := "01001";
  CONSTANT CMP_GT_R0 : std_logic_vector(INSTRUCTION_WIDTH - 1 DOWNTO 0) := "01010";

  CONSTANT JMP_LT : std_logic_vector(INSTRUCTION_WIDTH - 1 DOWNTO 0) := "01011";
  CONSTANT JMP_EQ : std_logic_vector(INSTRUCTION_WIDTH - 1 DOWNTO 0) := "01100";
  CONSTANT JMP_GT : std_logic_vector(INSTRUCTION_WIDTH - 1 DOWNTO 0) := "01101";
  CONSTANT JMP_N : std_logic_vector(INSTRUCTION_WIDTH - 1 DOWNTO 0) := "01110";


  -- NOT implemented !!
  CONSTANT PUSH_C : std_logic_vector(INSTRUCTION_WIDTH - 1 DOWNTO 0) := "01111";
  -- immediate instruction
  CONSTANT LOAD_I_C : std_logic_vector(INSTRUCTION_WIDTH - 1 DOWNTO 0) := "10000";
  CONSTANT STORE_I_C : std_logic_vector(INSTRUCTION_WIDTH - 1 DOWNTO 0) := "10001";

  -- Arithmetic operations:
  CONSTANT ADD_I_C : std_logic_vector(INSTRUCTION_WIDTH - 1 DOWNTO 0) := "10010";
  CONSTANT SUB_I_C : std_logic_vector(INSTRUCTION_WIDTH - 1 DOWNTO 0) := "10011";

END PACKAGE instruction_pkg;