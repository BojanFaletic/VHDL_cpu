LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;
-- RAM_BITS : depth of ROM
-- RAM_WIDTH : width of ROM

ENTITY RAM IS
  GENERIC (
    RAM_BITS : INTEGER := 7;
    RAM_WIDTH : INTEGER := 12);
  PORT (
    clk   : IN std_logic;
    d_in         : IN std_logic_vector(RAM_WIDTH - 1 DOWNTO 0);
    d_out        : OUT std_logic_vector(RAM_WIDTH - 1 DOWNTO 0);
    addr_in      : IN std_logic_vector(RAM_BITS - 1 DOWNTO 0);
    read_write_n : IN std_logic
  );
END ENTITY RAM;

ARCHITECTURE RTL OF RAM IS
  TYPE t_RAM IS ARRAY(0 TO 2 ** RAM_BITS - 1) OF std_logic_vector(RAM_WIDTH - 1 DOWNTO 0);
  SIGNAL RAM : t_RAM := (OTHERS => (OTHERS => '0'));
BEGIN

  p_RAM : PROCESS (clk)
  BEGIN
    IF (rising_edge(clk)) THEN
      IF (read_write_n = '1') THEN
        RAM(to_integer(unsigned(addr_in))) <= d_in;
      ELSE
        d_out <= RAM(to_integer(unsigned(addr_in)));
      END IF;
    END IF;
  END PROCESS;

END ARCHITECTURE RTL;