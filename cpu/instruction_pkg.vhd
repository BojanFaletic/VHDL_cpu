LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

-- each command has 4b instruction + 8b address
PACKAGE instruction_pkg IS
  constant INSTRUCTION_WIDTH : integer := 5;

  CONSTANT LOAD_C : std_logic_vector(INSTRUCTION_WIDTH-1 DOWNTO 0) := "00000";
  CONSTANT STORE_C : std_logic_vector(INSTRUCTION_WIDTH-1 DOWNTO 0) := "00001";

  -- Arithmetic operations:
  CONSTANT ADD_C : std_logic_vector(INSTRUCTION_WIDTH-1 DOWNTO 0) := "00010";
  CONSTANT SUB_C : std_logic_vector(INSTRUCTION_WIDTH-1 DOWNTO 0) := "00011";

  -- Logic operations:
  CONSTANT AND_C : std_logic_vector(INSTRUCTION_WIDTH-1 DOWNTO 0) := "00100";
  CONSTANT OR_C : std_logic_vector(INSTRUCTION_WIDTH-1 DOWNTO 0) := "00101";
  CONSTANT SHIFT_L_c : std_logic_vector(INSTRUCTION_WIDTH-1 DOWNTO 0) := "00110";
  CONSTANT SHIFT_R_c : std_logic_vector(INSTRUCTION_WIDTH-1 DOWNTO 0) := "00111";

  -- Comparison:
  CONSTANT JMP_EQ_c : std_logic_vector(INSTRUCTION_WIDTH-1 DOWNTO 0) := "01000";
  CONSTANT JMP_NEQ_c : std_logic_vector(INSTRUCTION_WIDTH-1 DOWNTO 0) := "01001";

  -- Compares value in accumulator (from previous instruction or return )
  CONSTANT CMP_EQ_C : std_logic_vector(INSTRUCTION_WIDTH-1 DOWNTO 0) := "01010";
  CONSTANT CMP_LT_C : std_logic_vector(INSTRUCTION_WIDTH-1 DOWNTO 0) := "01011";
  CONSTANT CMP_GT_C : std_logic_vector(INSTRUCTION_WIDTH-1 DOWNTO 0) := "01100";

  -- Jumping instructions:
  CONSTANT JMP_C : std_logic_vector(INSTRUCTION_WIDTH-1 DOWNTO 0) := "01101";

  -- Stack operations:
  CONSTANT POP_C : std_logic_vector(INSTRUCTION_WIDTH-1 DOWNTO 0) := "01110";
  CONSTANT PUSH_C : std_logic_vector(INSTRUCTION_WIDTH-1 DOWNTO 0) := "01111";


  -- immediate instruction
  CONSTANT LOAD_I_C : std_logic_vector(INSTRUCTION_WIDTH-1 DOWNTO 0) := "10000";
  CONSTANT STORE_I_C : std_logic_vector(INSTRUCTION_WIDTH-1 DOWNTO 0) := "10001";

  -- Arithmetic operations:
  CONSTANT ADD_I_C : std_logic_vector(INSTRUCTION_WIDTH-1 DOWNTO 0) := "10010";
  CONSTANT SUB_I_C : std_logic_vector(INSTRUCTION_WIDTH-1 DOWNTO 0) := "10011";

END PACKAGE instruction_pkg;
