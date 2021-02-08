#!/usr/bin/env python
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

# Generate test file, by running all inputs TODO make this more configurable

testbed_template = j2.Template("""
library IEEE;
use IEEE.STD_LOGIC_1164.all;

entity test_{{name}} is
end test_{{name}};

architecture behavior of test_{{name}} is
    component {{name}} is
        port (
            {% for input in inputs %}{{input}}: in std_logic;
            {% endfor %}{% for output in outputs %}{{output}}: out std_logic{% if not loop.last %};{% endif %}
            {% endfor %});
    end component;
    signal input  : std_logic_vector({{ num_inputs - 1 }} downto 0);
    signal output : std_logic_vector({{ num_inputs - 1 }} downto 0);
begin
    uut: {{name}} port map (
        {% for input in inputs %}{{input}} => input({{loop.index-1}}),
        {% endfor %}{% for output in outputs %}{{output}} => output({{loop.index-1}}){% if not loop.last %},{% endif %}{% endfor %}
    );

    stim_proc: process
    begin
        {% for test in testin %}
        input <= "{{test}}"; wait for 1 fs;
        {% endfor %}
        wait;
    end process;
end;
""")

render = testbed_template.render(
    name=name,
    inputs=test_def["inputs"],
    num_inputs=len(test_def["inputs"]),
    outputs=test_def["outputs"],
    num_outputs=len(test_def["outputs"]),
    testin=test_def["testin"]
    )

with open(args.output, "w") as f:
    print(render, file=f)

