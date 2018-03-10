//Réseau de neuronne Self Organizing Map
//Ce code est fait pour fonctionner sous Linux
//data.c
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>

#include "data.h"
#include "formulas.h"

//Retourne une grille d'indice de taille arg1 melangée
int* shuffle2(size_t nb_neurone)
{
	int *indices = malloc(sizeof(int)*nb_neurone);
	int rand_i;
	for(int i = 0; i < nb_neurone; i++)
	{
		indices[i] = i;
		rand_i = rand()%nb_neurone;
		indices[rand_i] = rand_i;
		indices[i] += indices[rand_i];
		indices[rand_i] = indices[i]-indices[rand_i];
		indices[i] -= indices[rand_i];
	}
	return indices;
}

void normalisation(IDX_STRUCT* database)
{	
    for(int y = 0; y < database->_dim_size[0]; y++)
        database->data[y]._norme = norme(database->data[y]._data, database->_dim_size, database->nb_elem);
    
}

//Affichage d'1 données
/*void printData(data_v* data)
{
	printf(" %.%.5lf %.5lf | name: %s | norme: %.1lf \n", data->vec[0], data->vec[1], data->vec[2], data->vec[3], data->nom, data->norme);
}*/