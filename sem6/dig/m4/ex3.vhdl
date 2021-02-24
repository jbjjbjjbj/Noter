-- TEST_START{"inputs": ["input,3,0", "write", "read"], "outputs": ["output,3,0"], "testin": [["0000", 0, 0], ["0000", 0, 1], ["1010", 1, 0], ["0000", 0, 1], ["1100", 1, 1], ["0011", 1, 1]]}TEST_STOP
library ieee;
use ieee.std_logic_1164.all;

entity ex3 is
    port (
        input: in std_logic_vector(3 downto 0);
        write: in std_logic;
        read: in std_logic;
        output: out std_logic_vector(3 downto 0)
    );
end ex3;

architecture impl of ex3 is
    signal stuff: std_logic_vector(3 downto 0) := "0000";
begin
    output <= stuff when read = '1' else "ZZZZ";
    stuff <= input when write = '1' else stuff;

end impl;
