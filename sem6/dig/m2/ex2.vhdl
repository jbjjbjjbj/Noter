-- TEST_START{"inputs": ["sw1", "sw2", "sw3", "sw4"], "outputs": ["LED"], "testin": ["0000", "0001", "0101", "1101"]}TEST_STOP
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.all;

ENTITY ex2 IS
    PORT(
        sw1: IN STD_LOGIC;
        sw2: IN STD_LOGIC;
        sw3: IN STD_LOGIC;
        sw4: IN STD_LOGIC;
        led: OUT STD_LOGIC);
END ex2;

ARCHITECTURE impl OF ex2 IS
BEGIN
    led <= (sw1 AND sw2) OR NOT(sw3 AND sw4);
END impl;
