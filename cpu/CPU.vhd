LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

USE work.instruction_pkg.ALL;
-- memory regions
-- 128B program
-- 64B external IO
-- 64B RAM

ENTITY CPU IS
  GENERIC (
    DATA_WIDTH_C : INTEGER := 8);
  PORT (
    rst_n, clk   : IN std_logic;
    d_out        : OUT std_logic_vector(DATA_WIDTH_C - 1 DOWNTO 0);
    d_in         : IN std_logic_vector(DATA_WIDTH_C - 1 DOWNTO 0);
    addr_out     : OUT std_logic_vector(DATA_WIDTH_C - 3 DOWNTO 0);
    read_write_n : OUT std_logic
  );
END ENTITY CPU;

ARCHITECTURE RTL OF CPU IS
  CONSTANT FULL_WIDTH_C : INTEGER := DATA_WIDTH_C + INSTRUCTION_WIDTH;

  SIGNAL PC : unsigned(DATA_WIDTH_C - 1 DOWNTO 0);

  SIGNAL ROM_address : std_logic_vector(DATA_WIDTH_C - 3 DOWNTO 0);
  SIGNAL RAM_address : std_logic_vector(DATA_WIDTH_C - 2 DOWNTO 0);

  SIGNAL data_from_ROM : std_logic_vector(FULL_WIDTH_C - 1 DOWNTO 0);
  SIGNAL data_from_RAM, data_to_RAM : std_logic_vector(DATA_WIDTH_C - 1 DOWNTO 0);
  SIGNAL RAM_read_write : std_logic;

  CONSTANT PC_WAIT_CLK_C : INTEGER := 8;
  SIGNAL pc_counter : NATURAL RANGE 0 TO PC_WAIT_CLK_C - 1;

  SIGNAL CPU_instruction : std_logic_vector(INSTRUCTION_WIDTH - 1 DOWNTO 0);
  SIGNAL CPU_data : std_logic_vector(DATA_WIDTH_C - 1 DOWNTO 0);

  SIGNAL data_to_ALU, data_from_ALU : std_logic_vector(DATA_WIDTH_C - 1 DOWNTO 0);
  SIGNAL ALU_cmd_valid : std_logic;

  COMPONENT ROM IS
    GENERIC (
      ROM_BITS : INTEGER := 7;
      ROM_WIDTH : INTEGER := 12);
    PORT (
      clk     : IN std_logic;
      d_out   : OUT std_logic_vector(ROM_WIDTH - 1 DOWNTO 0);
      addr_in : IN std_logic_vector(ROM_BITS - 1 DOWNTO 0)
    );
  END COMPONENT ROM;

  COMPONENT RAM IS
    GENERIC (
      RAM_BITS : INTEGER := 7;
      RAM_WIDTH : INTEGER := 12);
    PORT (
      clk          : IN std_logic;
      d_in         : IN std_logic_vector(RAM_WIDTH - 1 DOWNTO 0);
      d_out        : OUT std_logic_vector(RAM_WIDTH - 1 DOWNTO 0);
      addr_in      : IN std_logic_vector(RAM_BITS - 1 DOWNTO 0);
      read_write_n : IN std_logic
    );
  END COMPONENT RAM;

  COMPONENT ALU IS
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
  END COMPONENT ALU;

  -- returns rom address generated from PC
  FUNCTION get_ROM_address(SIGNAL PC : unsigned)
    RETURN std_logic_vector IS
    VARIABLE v_ROM_addr : std_logic_vector(DATA_WIDTH_C - 1 DOWNTO 0);
  BEGIN
    v_ROM_addr := std_logic_vector(PC);
    RETURN v_ROM_addr(DATA_WIDTH_C - 3 DOWNTO 0);
  END FUNCTION get_ROM_address;

  -- returns RAM address generated from PC
  FUNCTION get_RAM_address(SIGNAL PC : unsigned)
    RETURN std_logic_vector IS
    VARIABLE v_ROM_addr : std_logic_vector(DATA_WIDTH_C - 1 DOWNTO 0);
  BEGIN
    v_ROM_addr := std_logic_vector(PC);
    RETURN v_ROM_addr(DATA_WIDTH_C - 2 DOWNTO 0);
  END FUNCTION get_RAM_address;

  -- returns instruction name from ROM data
  FUNCTION get_CPU_instruction(SIGNAL data_from_ROM : std_logic_vector) RETURN
    std_logic_vector IS
  BEGIN
    RETURN data_from_ROM(FULL_WIDTH_C - 1 DOWNTO DATA_WIDTH_C);
  END FUNCTION get_CPU_instruction;

  -- returns data from ROM data
  FUNCTION get_CPU_data(SIGNAL data_from_ROM : std_logic_vector) RETURN
    std_logic_vector IS
  BEGIN
    RETURN data_from_ROM(DATA_WIDTH_C - 1 DOWNTO 0);
  END FUNCTION get_CPU_data;

  -- selects data to ALU
  FUNCTION select_RAM_data(SIGNAL data_from_ROM, data_from_RAM, cpu_instruction : std_logic_vector) RETURN
    std_logic_vector IS
  BEGIN
    IF (cpu_instruction /= LOAD_C) THEN
      RETURN data_from_ROM;
    ELSE
      RETURN data_from_RAM;
    END IF;
  END FUNCTION select_RAM_data;

  -- increment PC
  PROCEDURE increment_PC(SIGNAL PC : INOUT unsigned) IS
  BEGIN
    IF (PC /= 2 ** (DATA_WIDTH_C - 2) - 1) THEN
      PC <= PC + 1;
    ELSE
      PC <= (OTHERS => '0');
    END IF;
  END PROCEDURE increment_PC;
BEGIN
  p_cpu_tick : PROCESS (clk)
  BEGIN
    IF (rising_edge(clk)) THEN
      IF (rst_n = '0') THEN
        pc_counter <= 0;
      ELSE
        IF (pc_counter /= PC_WAIT_CLK_C - 1) THEN
          pc_counter <= pc_counter + 1;
        ELSE
          pc_counter <= 0;
        END IF;
      END IF;
    END IF;
  END PROCESS p_cpu_tick;

  p_CPU : PROCESS (clk)
  BEGIN
    IF rising_edge(clk) THEN
      IF (rst_n = '0') THEN
        PC <= (OTHERS => '0');
      ELSE
        IF (pc_counter = PC_WAIT_CLK_C - 1) THEN
          -- JMP instruction
          IF (CPU_instruction = JMP_C) THEN
            PC <= unsigned(CPU_data);
          ELSE
            increment_pc(PC);
          END IF;
        ELSIF (pc_counter = 2) THEN
          -- memory controlled operations
          IF (CPU_instruction = STORE_I_C) THEN
            RAM_read_write <= '1';
          END IF;
        ELSE
          RAM_read_write <= '0';
        END IF;
      END IF;
    END IF;
  END PROCESS p_CPU;

  ROM_address <= get_ROM_address(PC);
  CPU_instruction <= get_CPU_instruction(data_from_ROM);
  CPU_data <= get_CPU_data(data_from_ROM);

  data_to_ALU <= select_RAM_data(CPU_data, data_from_RAM, CPU_instruction);

  ALU_cmd_valid <= '1' WHEN pc_counter = 2 ELSE
    '0';

  data_to_RAM <= data_from_ALU;
  RAM_address <= CPU_data(DATA_WIDTH_C - 2 DOWNTO 0);

  
  inst_ROM : entity work.debug_ROM
  GENERIC MAP(
    ROM_BITS => DATA_WIDTH_C - 2,
    ROM_WIDTH => FULL_WIDTH_C)
  PORT MAP(
    clk     => clk,
    d_out   => data_from_ROM,
    addr_in => ROM_address
  );

  inst_RAM : RAM
  GENERIC MAP(
    RAM_BITS => DATA_WIDTH_C - 1,
    RAM_WIDTH => DATA_WIDTH_C)
  PORT MAP(
    clk          => clk,
    d_in         => data_to_RAM,
    d_out        => data_from_RAM,
    addr_in      => RAM_address,
    read_write_n => RAM_read_write
  );

  inst_ALU : ALU
  GENERIC MAP(
    INST_WIDTH => INSTRUCTION_WIDTH,
    DATA_WIDTH => DATA_WIDTH_C)
  PORT MAP(
    clk => clk, rst_n => rst_n,
    cmd_in       => CPU_instruction,
    d_in         => data_to_ALU,
    d_out        => data_from_ALU,
    cmd_valid_in => ALU_cmd_valid
  );

END ARCHITECTURE RTL;