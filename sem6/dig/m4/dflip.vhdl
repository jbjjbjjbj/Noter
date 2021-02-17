LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.all;

ENTITY dflip IS
    PORT(
            d: IN STD_LOGIC;
            clk: IN STD_LOGIC;
            q: OUT STD_LOGIC;
            nq: OUT STD_LOGIC
        );
END dflip;

ARCHITECTURE impl OF dflip IS
    SIGNAL qi : STD_LOGIC;
BEGIN
    nq <= NOT qi;
    q <= qi;
    PROCESS (clk)
    BEGIN
    -- Check if high edge
        if (clk'event and clk = '1') then
            qi <= d;
        end if;
    END PROCESS;
END IMPL;

