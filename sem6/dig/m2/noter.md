# Noter til digital design m2

Configurable element
:   I think the same as logic block

Island type architecture:
:   How to interconnect the configurable busses between Logic blocks
:   This can be done as either DISJOINT, UNIVERSAL or WILTON

## VHDL

Her bruger man rigtig meget `ENTITY` i stedet for verilog module.

```vhdl
ENTITY nor_gate IS
    PORT (
        x: IN STD_LOGIC;
        y: IN STD_LOGIC;
        z: OUT STD_LOGIC;
        );
END nor_gate;
```

Here semicolon is a seperator.
`STD_LOGIC` is for boolean values.

`Architecture implements the ENTITY`.

```vhdl
ARCHITECTURE sample OF nor_gate IS
BEGIN
    z <= x NOR y;
END sample;
```

`INOUT` can be used have an input and output, so *bi-directional*.

Different types, these come with IEEE libraries.

- `STD_LOGIC`: boolean (`1`, `0`, `Z`), with Z being high impedance

    THere are more options here but chose were not covered.
- `STD_LOGIC_VECTOR`: Sequence of values.

```
STD_LOGIC_VECTOR(7 DOWNTO 0): for MSB
```

`SIGNAL` is a wire inside the design.

```
SIGNAL x: STD_LOGIC
```

Okay so `COMPONENTS` are the equivilent of functions.
