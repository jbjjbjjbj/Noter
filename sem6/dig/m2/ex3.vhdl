-- TEST_START{"inputs": ["a", "b"], "outputs": ["o"], "testin": ["00", "01", "10", "11"]}TEST_STOP
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.all;

ENTITY ex3 IS
    PORT(
        a: IN STD_LOGIC;
        b: IN STD_LOGIC;
        o: OUT STD_LOGIC);
END ex3;

ARCHITECTURE impl OF ex3 IS
BEGIN
    o <= a and b;
END impl;
