//Réseau de neuronne Self Organizing Map
//data.h
#ifndef H_DATA
#include <math.h>
#include <sys/types.h>
#include <stdint.h>
#include "MNIST_parser.h"
#define H_DATA

void normalisation(IDX_STRUCT*);
int * shuffle2(size_t);

#endif
