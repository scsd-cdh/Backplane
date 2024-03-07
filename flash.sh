#!/bin/bash

# Compilation
msp430-gcc -mmcu=msp430fr5969 -o build/Backplane.elf main.c

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful."
else
    echo "Compilation failed."
    exit 1
fi


# Flashing
mspdebug tilib "prog build/Backplane.elf"

if [ $? -eq 0 ]; then
    echo "Flashing successful."
else
    echo "Flashing failed."
    exit 1
fi