//Réseau de neuronne Self Organizing Map
#ifndef H_FORMULAS //formulas.h
#include "data.h"
#include "MNIST_parser.h"
#define H_FORMULAS

void average(IDX_STRUCT* database);
double rand_double(double, double, double); 
int rand_int(int, int);
double norme(uint8_t*, uint32_t*, long int);
double euclidean_distance(double*, uint8_t*, long int);

#endif
