-- TEST_START{"inputs": ["cin", "a,3,0", "b,3,0"], "outputs": ["carry", "output,3,0"], "testin": [["0", "0001", "0001"], ["0", "0101", "1010"], ["0", "1111", "1111"], ["1", "0000", "0000"]]}TEST_STOP
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.all;

ENTITY ex6 IS
    PORT(
        a : IN STD_LOGIC_VECTOR(3 downto 0);
        b : IN STD_LOGIC_VECTOR(3 downto 0);
        cin: IN STD_LOGIC;
        output: OUT STD_LOGIC_VECTOR(3 downto 0);
        carry : OUT STD_LOGIC
    );
END ex6;

ARCHITECTURE impl OF ex6 IS
    SIGNAL c1 : STD_LOGIC;
    SIGNAL c2 : STD_LOGIC;
    SIGNAL c3 : STD_LOGIC;
    SIGNAL c4 : STD_LOGIC;

BEGIN

    add1 : ENTITY work.ex5
    PORT MAP (
                 a => a(0),
                 b => b(0),
                 cin => cin,
                 o => output(0),
                 cout => c1
             );

    add2 : ENTITY work.ex5
    PORT MAP (
                 a => a(1),
                 b => b(1),
                 cin => c1,
                 o => output(1),
                 cout => c2
             );

    add3 : ENTITY work.ex5
    PORT MAP (
                 a => a(2),
                 b => b(2),
                 cin => c2,
                 o => output(2),
                 cout => c3
             );

    add4 : ENTITY work.ex5
    PORT MAP (
                 a => a(3),
                 b => b(3),
                 cin => c3,
                 o => output(3),
                 cout => carry
             );
END impl;

