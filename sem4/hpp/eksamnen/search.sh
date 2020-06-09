#!/usr/bin/env bash

if [[ ! -f "superHPP.txt" ]]
then
    pdftotext superHPP.pdf
fi

if [[ ! -f "superHPPindex.txt" ]]
then
    ./placelinenums.rb superHPP.txt superHPPindex.txt
fi

okular -p $(cat superHPPindex.txt | fzf | awk '{print $1}') superHPP.pdf
