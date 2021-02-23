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

\\newtheorem{definition}{Definition}
\\newtheorem{lemma}{Lemma}
\\newtheorem{theorem}{Theorem}

{% if p is not none %}
\\title{ {{title}} }
{% endif %}

\\setlength{\parindent}{0cm}
\\setlength{\parskip}{0.3em}

\\begin{document}
    {% if title is not none %}
    \maketitle
    {% endif %}

    {{content}}
\\end{document}
"""

parser = argparse.ArgumentParser()
parser.add_argument("file", help="The file to load")

args = parser.parse_args()

# Load the file
content = []
title = None
with open(args.file, "r") as f:
    for line in f:
        m = re.findall("\\\\title\{(.*)\}", line)
        if m:
            title = m[0]
        else:
            content.append(line)

content = "".join(content)
print(content)

# Write to output
tmpl = jinja2.Template(tex_template)
output = tmpl.render(title=title,content=content)

# Create build folder
if not os.path.exists("render_build"):
    os.mkdir("render_build")

os.chdir("render_build")
with open("input.tex", "w") as f:
    f.write(output)

subprocess.call(["pdflatex", "input.tex"])
