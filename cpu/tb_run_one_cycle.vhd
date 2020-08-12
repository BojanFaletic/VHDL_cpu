LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY tb_run_one_cycle IS
END ENTITY;

ARCHITECTURE Behav OF tb_run_one_cycle IS
  SIGNAL clk, rst_n : std_logic := '0';


BEGIN


  p_clk : process
  begin
    clk <= '1';
    wait for 10 ns;
    clk <= '0';
    wait for 10 ns;
  end process p_clk;

  p_stim : process
  begin
    wait for 100 ns;

    wait;

  end process p_stim;

  inst_run_one_cycle : ENTITY work.run_one_cycle
    PORT MAP(
      clk => clk, rst_n => rst_n,
      IO_addr   => OPEN,
      IO_data_w => OPEN,
      IO_data_r => x"00",

      -- ALU interface
      alu_cmd    => open,
      alu_data_w => open,
      alu_data_r => x"00",
      alu_flags => "00000", 
      alu_active => open
    );
END ARCHITECTURE Behav;