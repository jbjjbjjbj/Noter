#!/usr/bin/env python3
# Render a single document

import argparse
import os
import jinja2
import subprocess
import re

tex_template = """\\documentclass[12pt]{article}
\\usepackage{amsmath}
\\usepackage{amsfonts}
\\usepackage{mdframed}
\\usepackage{float}

\\usepackage{tikz}
\\usetikzlibrary{automata, positioning, arrows}

\\newtheorem{definition}{Definition}
\\newtheorem{lemma}{Lemma}
\\newtheorem{theorem}{Theorem}

{% for thing in before %}
{{thing}}
{% endfor %}

\\setlength{\parindent}{0cm}
\\setlength{\parskip}{0.3em}

\\begin{document}
    {% if title is not none %}
    \maketitle
    {% endif %}

    {{content}}
\\end{document}
"""

beforewhitelist = ["title", "date"]

parser = argparse.ArgumentParser()
parser.add_argument("file", help="The file to load")

args = parser.parse_args()

# Load the file
content = []
before = []
with open(args.file, "r") as f:
    for line in f:
        m = re.findall("\\\\([a-zA-Z]*)\{.*\}", line)
        if m and m[0] in beforewhitelist:
            before.append(line)
        else:
            content.append(line)

content = "".join(content)

# Write to output
tmpl = jinja2.Template(tex_template)
output = tmpl.render(before=before,content=content)
print(output)

# Create build folder
if not os.path.exists("render_build"):
    os.mkdir("render_build")

os.chdir("render_build")
with open("input.tex", "w") as f:
    f.write(output)

subprocess.call(["pdflatex", "input.tex"])
