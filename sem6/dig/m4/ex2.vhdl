-- TEST_START{"inputs": ["sw0"], "outputs": ["o,3,0"], "clk": "bt0", "testin": "010111110000001100"}TEST_STOP
library ieee;
use ieee.std_logic_1164.all;

entity ex2 is
    port (
        sw0: in std_logic;
        bt0: in std_logic;
        o: out std_logic_vector(3 downto 0)
    );
end ex2;

architecture impl of ex2 is
    signal state: std_logic_vector(3 downto 0) := "0000";
    signal next_state: std_logic_vector(3 downto 0) := "0000";
begin
    -- Implement shifting
    next_state(3 downto 1) <= state(2 downto 0);
    next_state(0) <= sw0;

    process (bt0)
        variable bit_count : integer range 0 to 3;
    begin
        if (bt0'event and bt0 = '1') then
            state <= next_state;

            if (bit_count = 3) then
                o <= next_state;
                bit_count := 0;
            else
                bit_count := bit_count + 1;
            end if;
        end if;
    end process;
end impl;
