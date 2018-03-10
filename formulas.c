//Réseau de neuronne Self Organizing Map
//formulas.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include "data.h"

//fonction moyenne des vecteurs de données (ici iris_data)
void average(IDX_STRUCT *database)
{
    //Calcul du vecteur moyen
	for(int i = 0; i < database->_dim_size[0]; i++)
	{
	    database->_vec_moyen[i] = 0;
	    for(int y = 0; y < database->nb_elem; y++)
      {
		    database->_vec_moyen[i] += database->data[i]._data[y];
        //printf("%d ", database->_vec_moyen[i]);
      }

		database->_vec_moyen[i] /= (uint8_t) database->nb_elem;
		//printf("\n%d:\t%u", i+1, database->_vec_moyen[i]);
	}
}

double norme(uint8_t* _data, uint32_t* size, long int nb_elem)
{
	double n = 0.0f;
	for(int i = 0; i < nb_elem; i++)	
		n += (_data[i] * _data[i]);
	return sqrt(n);
}

  	/*            ___________________________________________________
   // F(p,q) :  \/ (|p0-q0|)² + (|p1-q1|)² + (|p2-q2|)² + (|p3-q3|)² \ */
double euclidean_distance(double* neurone_vec, uint8_t* data_vec, long nb_elem)
{	
    double res = 0.0f;
    double n = 0.0f;
    for(int i = 0; i < nb_elem; i++)
    {
      if(neurone_vec[i] > data_vec[i])
        n = neurone_vec[i] - data_vec[i];
      else
         n = data_vec[i] - neurone_vec[i];
    	//n = fabs(neurone_vec[i] - data_vec[i]);
    	//printf("\n%d\t %f  %u = %f", i, neurone_vec[i], data_vec[i], n);
      n = n*n;
      res+=n;
    }   
	return res;
}

//DONE
double rand_double(double n, double min, double max)
{
    double max_n = n + max;
    double min_n = n - min;

    double res = -1;
    while(res < 0)
   		res = (rand()/(double)RAND_MAX) * (max_n-min_n) + min_n;
	return res;
} 
/*
int rand_int(int min, int max)
{
	int rand_value = (int)rand() / RAND_MAX;
	return min + rand_value * (max - min);
}*/
