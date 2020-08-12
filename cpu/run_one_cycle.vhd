
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

USE work.instruction_pkg.ALL;
USE work.function_pkg.ALL;

-- alu_flags:
-- 0 = zero
-- 1 = low
-- 2 = eq
-- 3 = high
-- 4 = ov

ENTITY run_one_cycle IS
  PORT (
    clk, rst_n : IN std_logic;
    IO_addr    : OUT std_logic_vector(DATA_WIDTH_C - 2 DOWNTO 0);
    IO_data_w  : OUT std_logic_vector(DATA_WIDTH_C - 1 DOWNTO 0);
    IO_data_r  : IN std_logic_vector(DATA_WIDTH_C - 1 DOWNTO 0);

    -- ALU interface
    alu_cmd    : OUT std_logic_vector(INSTRUCTION_WIDTH - 1 DOWNTO 0);
    alu_data_w : OUT std_logic_vector(DATA_WIDTH_C - 1 DOWNTO 0);
    alu_data_r : IN std_logic_vector(DATA_WIDTH_C - 1 DOWNTO 0);
    alu_flags  : IN std_logic_vector(4 DOWNTO 0);
    alu_active : OUT std_logic
  );
END run_one_cycle;

ARCHITECTURE RTL OF run_one_cycle IS
  TYPE t_state IS (fetch_instruction, fetch_RAM, execute, store);
  SIGNAL state : t_state;

  SIGNAL ROM_address : std_logic_vector(DATA_WIDTH_C - 1 DOWNTO 0);
  SIGNAL data_from_ROM : std_logic_vector(FULL_WIDTH_C - 1 DOWNTO 0);
  SIGNAL data_to_RAM, data_from_RAM : std_logic_vector(DATA_WIDTH_C - 1 DOWNTO 0);
  SIGNAL RAM_address : std_logic_vector(DATA_WIDTH_C - 2 DOWNTO 0);
  SIGNAL RAM_read_write : std_logic;

  SIGNAL PC : unsigned(DATA_WIDTH_C - 1 DOWNTO 0) := (OTHERS => '0');

  FUNCTION is_jump(instruction, alu_flags : IN std_logic_vector) RETURN BOOLEAN IS
  BEGIN
    IF (instruction = JMP_LT AND alu_flags(1) = '1') THEN
      RETURN true;
    ELSIF (instruction = JMP_EQ AND alu_flags(2) = '1') THEN
      RETURN true;
    ELSIF (instruction = JMP_GT AND alu_flags(3) = '1') THEN
      RETURN true;
    ELSIF (instruction = JMP_N AND alu_flags = "00000") THEN
      RETURN true;
    ELSE
      RETURN false;
    END IF;
  END FUNCTION is_jump;

  FUNCTION is_store(instruction : IN std_logic_vector) RETURN BOOLEAN IS
  BEGIN
    IF (instruction = STORE_R0_A OR instruction = store_R1_A) THEN
      RETURN true;
    ELSE
      RETURN false;
    END IF;
  END FUNCTION is_store;

  FUNCTION is_RAM_address(instruction : IN std_logic_vector) RETURN BOOLEAN IS
  BEGIN
    IF (instruction = LOAD_A_R0 OR instruction = LOAD_A_R1) THEN
      RETURN true;
    ELSE
      RETURN false;
    END IF;
  END FUNCTION is_RAM_address;

BEGIN

  p_run : PROCESS (clk)
  BEGIN
    IF (rising_edge(clk)) THEN
      IF (rst_n = '0') THEN
        state <= fetch_instruction;
      ELSE
        -- defaults
        RAM_read_write <= '0';

        CASE(state) IS
          WHEN fetch_instruction =>
          ROM_address <= std_logic_vector(PC);
          state <= fetch_RAM;
          WHEN fetch_RAM =>
          RAM_address <= data_from_ROM(DATA_WIDTH_C - 2 DOWNTO 0);
          state <= execute;
          WHEN execute =>
          alu_active <= '1';
          alu_cmd <= data_from_ROM(FULL_WIDTH_C - 1 DOWNTO DATA_WIDTH_C);

          -- choose data from ROM or RAM, dependent on instruction type
          -- for now always use ROM
          IF (is_RAM_address(data_from_ROM(FULL_WIDTH_C - 1 DOWNTO DATA_WIDTH_C))) THEN
            alu_data_w <= data_from_RAM;
          ELSE
            alu_data_w <= data_from_ROM(DATA_WIDTH_C - 1 DOWNTO 0);
          END IF;
          state <= store;
          WHEN store =>
          alu_active <= '0';

          -- handle jump
          IF (is_jump(data_from_ROM(FULL_WIDTH_C - 1 DOWNTO DATA_WIDTH_C), alu_flags)) THEN
            PC <= unsigned(data_from_rom(DATA_WIDTH_C - 1 DOWNTO 0));
          ELSE
            increment_PC(PC);
          END IF;

          -- handle store
          IF (is_store(data_from_ROM(FULL_WIDTH_C - 1 DOWNTO DATA_WIDTH_C))) THEN
            RAM_read_write <= '1';
            RAM_address <= data_from_rom(DATA_WIDTH_C - 2 DOWNTO 0);
          END IF;

          state <= fetch_instruction;

          WHEN OTHERS =>
          state <= fetch_instruction;
        END CASE;
      END IF;
    END IF;
  END PROCESS p_run;

  -- data to RAM can only be written via ALU
  data_to_RAM <= alu_data_r;

  inst_ROM : ENTITY work.ROM
    GENERIC MAP(
      ROM_BITS => DATA_WIDTH_C,
      ROM_WIDTH => FULL_WIDTH_C)
    PORT MAP(
      clk     => clk,
      d_out   => data_from_ROM,
      addr_in => ROM_address
    );

  inst_RAM : ENTITY work.RAM
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

END ARCHITECTURE;