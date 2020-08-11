LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY tb_CPU IS
END ENTITY;

ARCHITECTURE Behav OF tb_CPU IS
  SIGNAL clk, rst_n : std_logic;

  COMPONENT CPU IS
    GENERIC (
      DATA_WIDTH_C : INTEGER := 8);
    PORT (
      rst_n, clk   : IN std_logic;
      d_out        : OUT std_logic_vector(DATA_WIDTH_C - 1 DOWNTO 0);
      d_in         : IN std_logic_vector(DATA_WIDTH_C - 1 DOWNTO 0);
      addr_out     : OUT std_logic_vector(DATA_WIDTH_C - 3 DOWNTO 0);
      read_write_n : OUT std_logic
    );
  END COMPONENT CPU;

BEGIN

  p_clk : PROCESS
  BEGIN
    clk <= '1';
    WAIT FOR 10 ns;
    clk <= '0';
    WAIT FOR 10 ns;
  END PROCESS p_clk;

  p_stim : PROCESS
  BEGIN
    rst_n <= '0';
    wait for 100 ns;
    rst_n <= '1';

    wait for 100 ns;
    wait;
  END PROCESS p_stim;

  DUT : CPU
  PORT MAP(
    rst_n => rst_n, clk => clk,
    d_out        => OPEN,
    d_in         => x"00",
    addr_out     => OPEN,
    read_write_n => OPEN
  );
  end ARCHITECTURE Behav;