-- TEST_START{"inputs": ["input,7,0", "write", "read"], "outputs": ["output,7,0"], "testin": [["00000000", 0, 0], ["00000000", 0, 1], ["10101010", 1, 0], ["00000000", 0, 1], ["00000000", 0, 0], ["00000000", 0, 1], ["11001010", 1, 1], ["00111111", 1, 1]]}TEST_STOP
library ieee;
use ieee.std_logic_1164.all;

entity ex4 is
    port (
        input: in std_logic_vector(7 downto 0);
        write: in std_logic;
        read: in std_logic;
        output: out std_logic_vector(7 downto 0)
    );
end ex4;

architecture impl of ex4 is
begin

    mem_low : ENTITY work.ex3
    PORT MAP (
                input => input(3 downto 0),
                write => write,
                read => read,
                output => output(3 downto 0)
             );

    mem_high : ENTITY work.ex3
    PORT MAP (
                input => input(7 downto 4),
                write => write,
                read => read,
                output => output(7 downto 4)
             );
end impl;
