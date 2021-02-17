-- TEST_START{"inputs": ["clk"], "outputs": [],"teststep": 10, "testin": "101010101010101010101010101010"}TEST_STOP
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.all;

ENTITY ex1 IS
    PORT(
            clk: IN STD_LOGIC
        );
END ex1;

ARCHITECTURE impl OF ex1 IS
    SIGNAL seed : STD_LOGIC := '1';
    SIGNAL a : STD_LOGIC := '0';
    SIGNAL first_out : STD_LOGIC := '0';
    SIGNAL b : STD_LOGIC := '0';
    SIGNAL c : STD_LOGIC := '0';
    SIGNAL d : STD_LOGIC := '0';
    SIGNAL lp : STD_LOGIC := '0';

BEGIN
    lp <= c XOR d;
    a <= seed OR first_out;

    flip1 : ENTITY work.dflip
    PORT MAP (
                 d => lp,
                 q => first_out,
                 clk => clk
             );

    flip2 : ENTITY work.dflip
    PORT MAP (
                 d => a,
                 q => b,
                 clk => clk
             );

    flip3 : ENTITY work.dflip
    PORT MAP (
                 d => b,
                 q => c,
                 clk => clk
             );

    flip4 : ENTITY work.dflip
    PORT MAP (
                 d => c,
                 q => d,
                 clk => clk
             );

    process (clk)
    begin
        if (clk = '0' AND seed = '1') then
            seed <= '0';
        end if;
    end process;

END impl;
