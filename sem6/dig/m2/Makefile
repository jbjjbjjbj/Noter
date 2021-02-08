
INPUTFILES=nor_gate

all: $(INPUTFILES)

.PHONY: all clean

%.o: %.vhdl
	ghdl -a $^

$(INPUTFILES): %: %.o
	ghdl -e $@

test_%.vhdl: %.vhdl generate_test_file.py
	./generate_test_file.py $< $@

test_$(INPUTFILES): %: %.o
	ghdl -e $@

run_%: %
	ghdl -r $^

sim_%: test_% %
	-./$< --vcd=out.vcd

clean:
	ghdl --clean
	rm -f work*.cf
	rm -f test_*.vhdl

