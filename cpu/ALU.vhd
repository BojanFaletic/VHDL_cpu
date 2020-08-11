LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

USE work.instruction_pkg.ALL;

ENTITY ALU IS
  GENERIC (
    INST_WIDTH : INTEGER := 4;
    DATA_WIDTH : INTEGER := 8);
  PORT (
    clk, rst_n   : IN std_logic;
    cmd_in       : IN std_logic_vector(INST_WIDTH - 1 DOWNTO 0);
    d_in         : IN std_logic_vector(DATA_WIDTH - 1 DOWNTO 0);
    d_out        : OUT std_logic_vector(DATA_WIDTH - 1 DOWNTO 0);
    cmd_valid_in : IN std_logic
  );
END ENTITY ALU;

ARCHITECTURE RTL OF ALU IS
  SIGNAL accumulator : unsigned(DATA_WIDTH - 1 DOWNTO 0);
BEGIN

  p_ALU : PROCESS (clk)
  BEGIN
    IF rising_edge(clk) THEN
      IF (rst_n = '0') THEN
        accumulator <= (OTHERS => '0');
      ELSE
        IF (cmd_valid_in = '1') THEN
          IF (cmd_in = LOAD_I_C) or cmd_in = LOAD_C THEN
            accumulator <= unsigned(d_in);
          ELSIF (cmd_in = STORE_I_C) THEN
            d_out <= std_logic_vector(accumulator);
          ELSIF (cmd_in = ADD_I_C) THEN
            accumulator <= unsigned(d_in) + accumulator;
          END IF;
        END IF;
      END IF;
    END IF;
  END PROCESS p_ALU;

END ARCHITECTURE RTL;