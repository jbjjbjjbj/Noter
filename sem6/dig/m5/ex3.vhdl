-- TEST_START{"inputs": [], "outputs": ["output,6,0"], "clk": "clk", "testcount": 1000}TEST_STOP
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity ex3 is
    port (
        clk: in std_logic;
        output: out std_logic_vector(6 downto 0)
    );
end ex3;

architecture impl of ex3 is
    signal value: unsigned(6 downto 0) := "0000000";
begin
    output <= std_logic_vector(value);

    process (clk)
    begin
        if (clk'event and clk = '1') then
            if (value = 59) then
                value <= "0000000";
            else
                value <= value + 1;
            end if;
        end if;
    end process;

end impl;
