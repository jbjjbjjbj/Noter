-- TEST_START{"inputs": ["sw1", "sw2", "sw3", "sw4"], "outputs": ["l1", "l2", "l3", "l4"], "testin": ["0000", "0001", "0101", "1101", "1010"]}TEST_STOP
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.all;

ENTITY ex1 IS
    PORT(
        sw1: IN STD_LOGIC;
        sw2: IN STD_LOGIC;
        sw3: IN STD_LOGIC;
        sw4: IN STD_LOGIC;
        l1: OUT STD_LOGIC;
        l2: OUT STD_LOGIC;
        l3: OUT STD_LOGIC;
        l4: OUT STD_LOGIC);
END ex1;

ARCHITECTURE impl OF ex1 IS
BEGIN
    l1 <= sw1;
    l2 <= sw2;
    l3 <= sw3;
    l4 <= sw4;
END impl;
