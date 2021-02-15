-- TEST_START{"inputs": ["a", "b", "cin"], "outputs": ["o", "cout"], "testin": ["000", "010", "100", "110", "011", "111"]}TEST_STOP
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.all;

ENTITY ex5 IS
    PORT(
        a: IN STD_LOGIC;
        b: IN STD_LOGIC;
        cin: IN STD_LOGIC;
        o: OUT STD_LOGIC;
        cout: OUT STD_LOGIC);
END ex5;

ARCHITECTURE impl OF ex5 IS
BEGIN
    o <= (a XOR b) XOR cin;
    cout <= (a AND b) OR (cin AND (a OR b));
END impl;
