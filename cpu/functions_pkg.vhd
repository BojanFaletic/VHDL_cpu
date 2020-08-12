LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

use work.instruction_pkg.all;

PACKAGE function_pkg IS
 
  -- returns rom address generated from PC
  FUNCTION get_ROM_address(SIGNAL PC : unsigned
  ) RETURN std_logic_vector;

  -- returns RAM address generated from PC
  FUNCTION get_RAM_address(SIGNAL PC : unsigned
  ) RETURN std_logic_vector;

  -- returns instruction name from ROM data
  FUNCTION get_CPU_instruction(SIGNAL data_from_ROM : std_logic_vector
  ) RETURN std_logic_vector;
  -- returns data from ROM data

  FUNCTION get_CPU_data(SIGNAL data_from_ROM : std_logic_vector
  ) RETURN std_logic_vector;

  -- selects data to ALU
  FUNCTION select_RAM_data(SIGNAL data_from_ROM, data_from_RAM, cpu_instruction : std_logic_vector
  ) RETURN std_logic_vector;

  -- increment PC
  PROCEDURE increment_PC(SIGNAL PC : INOUT unsigned);

END PACKAGE function_pkg;

PACKAGE BODY function_pkg IS
  FUNCTION get_ROM_address(SIGNAL PC : unsigned)
    RETURN std_logic_vector IS
    VARIABLE v_ROM_addr : std_logic_vector(DATA_WIDTH_C - 1 DOWNTO 0);
  BEGIN
    v_ROM_addr := std_logic_vector(PC);
    RETURN v_ROM_addr(DATA_WIDTH_C - 3 DOWNTO 0);
  END FUNCTION get_ROM_address;

  FUNCTION get_RAM_address(SIGNAL PC : unsigned)
    RETURN std_logic_vector IS
    VARIABLE v_ROM_addr : std_logic_vector(DATA_WIDTH_C - 1 DOWNTO 0);
  BEGIN
    v_ROM_addr := std_logic_vector(PC);
    RETURN v_ROM_addr(DATA_WIDTH_C - 2 DOWNTO 0);
  END FUNCTION get_RAM_address;

  FUNCTION get_CPU_instruction(SIGNAL data_from_ROM : std_logic_vector) RETURN
    std_logic_vector IS
  BEGIN
    RETURN data_from_ROM(FULL_WIDTH_C - 1 DOWNTO DATA_WIDTH_C);
  END FUNCTION get_CPU_instruction;

  FUNCTION get_CPU_data(SIGNAL data_from_ROM : std_logic_vector) RETURN
    std_logic_vector IS
  BEGIN
    RETURN data_from_ROM(DATA_WIDTH_C - 1 DOWNTO 0);
  END FUNCTION get_CPU_data;

  FUNCTION select_RAM_data(SIGNAL data_from_ROM, data_from_RAM, cpu_instruction : std_logic_vector) RETURN
    std_logic_vector IS
  BEGIN
    IF false THEN
      RETURN data_from_ROM;
    ELSE
      RETURN data_from_RAM;
    END IF;
  END FUNCTION select_RAM_data;

  PROCEDURE increment_PC(SIGNAL PC : INOUT unsigned) IS
  BEGIN
    IF (PC /= 2 ** (DATA_WIDTH_C - 2) - 1) THEN
      PC <= PC + 1;
    ELSE
      PC <= (OTHERS => '0');
    END IF;
  END PROCEDURE increment_PC;

END PACKAGE BODY function_pkg;