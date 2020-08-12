LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

USE work.instruction_pkg.ALL;
USE work.function_pkg.ALL;
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
    addr_out     : OUT std_logic_vector(DATA_WIDTH_C - 2 DOWNTO 0);
    read_write_n : OUT std_logic
  );
END ENTITY CPU;

ARCHITECTURE RTL OF CPU IS
  SIGNAL alu_cmd : std_logic_vector(INSTRUCTION_WIDTH - 1 DOWNTO 0);
  SIGNAL alu_data_w, alu_data_r : std_logic_vector(DATA_WIDTH_C - 1 DOWNTO 0);
  SIGNAL alu_flags : std_logic_vector(4 DOWNTO 0);
  SIGNAL alu_active : std_logic;
BEGIN
  alu_inst : ENTITY work.ALU
    GENERIC MAP(
      INST_WIDTH => INSTRUCTION_WIDTH,
      DATA_WIDTH => DATA_WIDTH_C)
    PORT MAP(
      clk => clk, rst_n => rst_n,
      cmd_in       => alu_cmd,
      d_in         => alu_data_w,
      d_out        => alu_data_r,
      cmd_valid_in => alu_active,
      flags        => alu_flags
    );

  single_cycle_inst : ENTITY work.run_one_cycle
    PORT MAP(
      clk => clk, rst_n => rst_n,
      IO_addr   => addr_out,
      IO_data_w => d_out,
      IO_data_r => d_in,

      -- ALU interface
      alu_cmd    => alu_cmd,
      alu_data_w => alu_data_w,
      alu_data_r => alu_data_r,
      alu_flags  => alu_flags,
      alu_active => alu_active
    );
END ARCHITECTURE RTL;