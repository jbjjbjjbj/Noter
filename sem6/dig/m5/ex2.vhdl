-- TEST_START{"inputs": [], "outputs": ["output,23,0"], "clk": "clk", "testcount": 100}TEST_STOP
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity ex2 is
    port (
        clk: in std_logic;
        output: out std_logic_vector(23 downto 0)
    );
end ex2;

architecture impl of ex2 is
    signal value: unsigned(23 downto 0) := "000000000000000000000000";
begin
    output <= std_logic_vector(value);

    process (clk)
    begin
        if (clk'event and clk = '1') then
            value <= value + 1;
        end if;
    end process;

end impl;
