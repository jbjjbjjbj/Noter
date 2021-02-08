-- TEST_START{"inputs": ["a", "b"], "outputs": ["o"], "testin": ["00", "10", "01", "11"]}TEST_STOP
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.all;

ENTITY nor_gate IS
    PORT(
            a: IN STD_LOGIC;
            b: IN STD_LOGIC;
            o: OUT STD_LOGIC);
END nor_gate;

ARCHITECTURE sample OF nor_gate IS
BEGIN
    o <= a NOR b;
END sample;
