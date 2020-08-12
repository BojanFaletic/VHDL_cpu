LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

USE work.instruction_pkg.ALL;

-- ROM_BITS : depth of ROM
-- ROM_WIDTH : width of ROM

ENTITY ROM IS
  GENERIC (
    ROM_BITS : INTEGER := 7;
    ROM_WIDTH : INTEGER := 12);
  PORT (
    clk : IN std_logic;
    d_out      : OUT std_logic_vector(ROM_WIDTH - 1 DOWNTO 0);
    addr_in    : IN std_logic_vector(ROM_BITS - 1 DOWNTO 0)
  );
END ENTITY ROM;

ARCHITECTURE RTL OF ROM IS
  TYPE t_rom IS ARRAY(0 TO 2 ** ROM_WIDTH - 1) OF std_logic_vector(ROM_WIDTH - 1 DOWNTO 0);
  SIGNAL ROM : t_rom := (
    LOAD_A_R0 & x"00",
    LOAD_C_R1 & x"01",
    ADD_R0_R1 & x"00",
    STORE_R0_A & x"00",
    JMP_N & x"00",  
    OTHERS => (OTHERS => '0'));
BEGIN

  p_rom : PROCESS (clk)
  BEGIN
    IF (rising_edge(clk)) THEN
      d_out <= ROM(to_integer(unsigned(addr_in)));
    END IF;
  END PROCESS p_rom;

END ARCHITECTURE RTL;