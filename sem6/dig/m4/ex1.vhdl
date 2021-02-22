-- TEST_START{"inputs": ["clk"], "outputs": [],"teststep": 10, "testin": "0101010101010101010101010101010"}TEST_STOP
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.all;

ENTITY ex1 IS
    PORT(
            clk: IN STD_LOGIC
        );
END ex1;

ARCHITECTURE impl OF ex1 IS
    SIGNAL state: std_logic_vector(3 downto 0) := "0001";
    signal next_state: std_logic_vector(3 downto 0) := "0000";

begin
    -- First program the nextstate logic
    next_state(3 downto 1) <= state(2 downto 0);
    next_state(0) <= state(2) xor state(3);

    -- Implement latching on clock
    process (clk)
    begin
        if (clk'event and clk = '1') then
            state <= next_state;
        end if;
    end process;
END impl;
