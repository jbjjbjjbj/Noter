#!/usr/bin/env python
# WOW THIS IS TERRIBLE
import json
import argparse
import re
import sys
import os
import jinja2 as j2

test_define_re = re.compile("TEST_START(.*)TEST_STOP")

parser = argparse.ArgumentParser()
parser.add_argument("file", help="vhdl file to read from")
parser.add_argument("output", help="vhdl file to save to")

args = parser.parse_args()

def load_file_def(fname):
    filecontent = ""
    with open(fname, "r") as f:
        filecontent = f.read()

    groups = test_define_re.search(filecontent).groups()
    if groups:
        return json.loads(groups[0])
    else:
        print("No def in file", f=sys.stderr)

test_def = load_file_def(args.file)
name = os.path.splitext(args.file)[0]

def generate_vhdl_file(f, td, name):
    def tof(s):
        f.write(s)

    tof(f"""
library IEEE;
use IEEE.STD_LOGIC_1164.all;

entity test_{name} is
end test_{name};

architecture behavior of test_{name} is
    component {name} is
        port (
    """)

    # Generate PORT section
    first = True
    if "clk" in td:
        tof(f"{td['clk']}: IN STD_LOGIC")
        first = False
    for i in td["inputs"]:
        if not first:
            tof(";\n")
        first = False
        args = i.split(",")
        if len(args) > 1:
            tof(f"{args[0]} : IN STD_LOGIC_VECTOR({args[1]} downto {args[2]})")
        else:
            # Not a vector
            tof(f"{args[0]} : IN STD_LOGIC")
    for o in td["outputs"]:
        if not first:
            tof(";\n")
        first = False
        args = o.split(",")
        if len(args) > 1:
            tof(f"{args[0]} : OUT STD_LOGIC_VECTOR({args[1]} downto {args[2]})")
        else:
            # Not a vector
            tof(f"{args[0]} : OUT STD_LOGIC")
    tof(");\nend component;\n");

    # Define signals
    if "clk" in td:
        tof(f"signal in_{td['clk']}: STD_LOGIC;\n")
    for i in td["inputs"]:
        args = i.split(",")
        if len(args) > 1:
            tof(f"signal in_{args[0]} : STD_LOGIC_VECTOR({args[1]} downto {args[2]});\n")
        else:
            # Not a vector
            tof(f"signal in_{args[0]} : STD_LOGIC;\n")
    for i in td["outputs"]:
        args = i.split(",")
        if len(args) > 1:
            tof(f"signal out_{args[0]} : STD_LOGIC_VECTOR({args[1]} downto {args[2]});\n")
        else:
            # Not a vector
            tof(f"signal out_{args[0]} : STD_LOGIC;\n")
    tof(f"""\nbegin
        uut: {name} port map(\n""")

    first = True
    if "clk" in td:
        tof(f"{td['clk']} => in_{td['clk']}")
        first = False
    for i in td["inputs"]:
        if not first:
            tof(",\n")
        first = False
        args = i.split(",")
        tof(f"{args[0]} => in_{args[0]}")
    for i in td["outputs"]:
        if not first:
            tof(",\n")
        first = False
        args = i.split(",")
        tof(f"{args[0]} => out_{args[0]}")
    tof(");\n\nstim_proc: process\nbegin\n")

    def wait():
        tof(f"wait for {td.get('teststep', 1)} fs;")

    for tindex, t in enumerate(td["testin"]):
        # Add clock
        if "clk" in td:
            tof(f"in_{td['clk']} <= '0';")
        for index, i in enumerate(td["inputs"]):
            args = i.split(",")
            if len(args) > 1:
                tof(f"in_{args[0]} <= \"{t[index]}\";")
            else:
                tof(f"in_{args[0]} <= '{t[index]}';")
        wait()
        if "clk" in td:
            tof(f"in_{td['clk']} <= '1';")
        wait()
    tof("wait;\nend process;\nend;")


with open(args.output, "w") as f:
    generate_vhdl_file(f, test_def, name)

