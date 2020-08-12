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
    cmd_valid_in : IN std_logic;
    flags        : OUT std_logic_vector(4 DOWNTO 0)
  );
END ENTITY ALU;

ARCHITECTURE RTL OF ALU IS
  SIGNAL R0, R1 : unsigned(DATA_WIDTH - 1 DOWNTO 0);
  SIGNAL zero, low, eq, high, ov : std_logic;


BEGIN

  flags <= zero & low & eq & high & ov;

  p_ALU : PROCESS (clk)
  variable sum_v : unsigned(DATA_WIDTH downto 0);
  BEGIN
    IF rising_edge(clk) THEN
      IF (rst_n = '0') THEN
        R0 <= (OTHERS => '0');
        R1 <= (OTHERS => '0');
      ELSE
        IF (cmd_valid_in = '1') THEN
          ov <= '0';
          zero <= '0';
          low <= '0';
          eq <= '0';
          high <= '0';
          IF (cmd_in = LOAD_C_R0 OR cmd_in = LOAD_A_R0) THEN
            R0 <= unsigned(d_in);
          ELSIF (cmd_in = LOAD_C_R1 OR cmd_in = LOAD_A_R1) THEN
            R1 <= unsigned(d_in);
          ELSIF (cmd_in = STORE_R0_A) THEN
            d_out <= std_logic_vector(R0);
          ELSIF (cmd_in = STORE_R1_A) THEN
            d_out <= std_logic_vector(R1);
          ELSIF (cmd_in = ADD_R0_R1) THEN
            sum_v := resize(R0, DATA_WIDTH+1) + resize(R1, DATA_WIDTH+1);
            R0 <= sum_v(DATA_WIDTH-1 downto 0);
            ov <= sum_v(DATA_WIDTH);
          END IF;
        END IF;
      END IF;
    END IF;
  END PROCESS p_ALU;

END ARCHITECTURE RTL;