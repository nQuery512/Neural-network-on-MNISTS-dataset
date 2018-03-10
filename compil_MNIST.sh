#!/bin/sh

clear
rm MNIST
gcc -std=c99 -Wall -lm main.c data.c formulas.c neural_map.c MNIST_parser.c -o MNIST
if [ $? -ne 0 ]
then 
    echo 'Compilation failure';
    exit 1
else 
    echo 'Compilation succeded';
fi

