LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;
USE STD.textio.ALL;
USE ieee.std_logic_textio.ALL;

--USE work.instruction_pkg.ALL;
ENTITY debug_ROM IS
  GENERIC (
    ROM_BITS : INTEGER := 7;
    ROM_WIDTH : INTEGER := 13);
  PORT (
    clk     : IN std_logic;
    d_out   : OUT std_logic_vector(ROM_WIDTH - 1 DOWNTO 0);
    addr_in : IN std_logic_vector(ROM_BITS - 1 DOWNTO 0)
  );
END ENTITY debug_ROM;

ARCHITECTURE Behavior OF debug_ROM IS
  TYPE t_rom IS ARRAY(0 TO 2 ** ROM_WIDTH - 1) OF std_logic_vector(ROM_WIDTH - 1 DOWNTO 0);
  SIGNAL ROM : t_rom:= (OTHERS => (OTHERS => '0'));

  FILE file_VECTORS : text;
BEGIN

  p_init_rom : PROCESS
    VARIABLE LINE_v : line;
    VARIABLE ram_d : integer;
    VARIABLE ram_idx : INTEGER := 0;
  BEGIN
      file_open(file_VECTORS, "/home/bojan/FPGA_projects/CPU/cpu/ROM.hex", read_mode);
      WHILE NOT endfile(file_VECTORS) LOOP
        readline(file_VECTORS, LINE_v);
        read(LINE_v, ram_d);
        ROM(ram_idx) <= std_logic_vector(to_unsigned(ram_d, ROM_WIDTH));
        ram_idx := ram_idx + 1;
      END LOOP;
      file_close(file_VECTORS);
    wait;
  END PROCESS p_init_rom;

  p_rom : PROCESS (clk)
  BEGIN
    IF (rising_edge(clk)) THEN
      d_out <= ROM(to_integer(unsigned(addr_in)));
    END IF;
  END PROCESS p_rom;

END ARCHITECTURE Behavior;