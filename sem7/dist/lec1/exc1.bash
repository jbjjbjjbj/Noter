#!/usr/bin/env bash
set -e

if [ "$#" -lt 2 ]; then
    echo Not enough arguments, use $0 inputfile outputfile
    exit 1
fi

inputfile=$1

if [[ ! -f "$inputfile" ]]; then
    echo File $inputfile does not exist
    exit 1
fi

outputfile=$2

echo Sending file $inputfile into $outputfile

# Open a server
nc -l -p 8080 > $outputfile &

# Connect with client and send file
nc -c 127.0.0.1 8080 < $inputfile

echo Done
