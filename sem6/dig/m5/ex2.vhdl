-- TEST_START{"inputs": [], "outputs": ["output,23,0", "leds,7,0"], "clk": "clk", "testcount": 1000}TEST_STOP
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity ex2 is
    port (
        clk: in std_logic;
        output: out std_logic_vector(23 downto 0);
        leds: out std_logic_vector(7 downto 0)
    );
end ex2;

architecture impl of ex2 is
    signal value: unsigned(23 downto 0) := "000000000000000000000000";
    signal output_int: std_logic_vector(23 downto 0);
begin
    output_int <= std_logic_vector(value);
    output <= output_int;
    leds <= output_int(7 downto 0);

    process (clk)
    begin
        if (clk'event and clk = '1') then
            value <= value + 1;
        end if;
    end process;

end impl;

-- The first bit of the leds blinks in the same frequency as clock.
-- The second bit will have a full cycle in two first bit cycles, so clock / 2.
-- The third bit will have clock / 2 / 2 og clock / (2 * 2).
-- The general form is clock / (2 ^ n) where n is the bit index starting at 0.
