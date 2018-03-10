#!/bin/sh

clear
gcc -std=c99 -pedantic -Wall main.c data.c neural_map.c formulas.c MNIST_parser.c -lm -o som
if [ $? -ne 0 ]
then 
    echo 'Compilation failure';
else 
    echo 'Compilation suceeded';
fi

