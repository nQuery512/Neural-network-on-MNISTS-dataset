#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "data.h"
#include "formulas.h"
#include "neural_map.h"
#include <string.h>
#define couleur(param) printf("\033[%sm",param)


//Initialise le nbre de ligne/colonne
grille initGrid(int nb_neurone)
{   
    int nb_column = 10;
    int nb_ligne;
    double tmp;
    
    while(nb_neurone - nb_column >0) 
        nb_column *= 10;    
    nb_column /= 10;    
    if(nb_column > 10)
        nb_column = nb_column/10;
    else if(nb_column > 100)
        nb_column = nb_column/100;
    else if(nb_column > 1000)
        nb_column = nb_column/1000;
    else if(nb_column > 10000)
        nb_column = nb_column/10000;    
    tmp = (double)nb_neurone/nb_column;
    nb_ligne = (int) ceil(tmp);
    
    grille test;
    test.nb_voisin = malloc(sizeof(size_t));
    test._rect = (int **)malloc(sizeof(int*)*nb_ligne);
    test.nb_line = nb_ligne;
    test.nb_column = nb_column;
    int y, i, z;
    
    for(i = 0, z = 0; i < test.nb_line; i++)
    {
        test._rect[i] = (int*)malloc(sizeof(int)*nb_column);
        for(y = 0; y < test.nb_column; y++)
        {
            test._rect[i][y] = (int) z++;
        }
    }
    return test;
}

void resetGrid(int** grid, int nb_ligne, int nb_colonne)
{
    int y, i, z;
    for(i = 0, z = 0; i < nb_ligne; i++)
    { 
        for(y = 0; y < nb_colonne; y++)
        {
           grid[i][y] = z;
           z++;
        }
    }
}

void printGrid(int** grid, int nb_ligne, int nb_colonne)
{
    int y, i;
    for(i = 0; i < nb_ligne; i++)
    {
        if (i == 1)
            printf("  ");
        printf("\n");
        for(y = 0; y < nb_colonne; y++)
        {
            printf("%d ", grid[i][y]);
        }
    }
}

void initNeuralMap(neural_m** neural_map, uint8_t* vec_moyen, int nb_neurones, long int nb_elem)
{
    for(int i = 0; i < nb_neurones; i++)
    {
        neural_map[i] = malloc(sizeof(neural_m)*nb_neurones);
        neural_map[i]->mem = malloc(sizeof(double) * nb_elem);
        //neural_map[i]->etiquette = malloc(sizeof(char)* 1);
        for(int y = 0; y < nb_elem; y++)
            neural_map[i]->mem[y] = rand_double(vec_moyen[y], 0.02, 0.05);
    }
}



void printVecNeuralMap(neural_m** neural_map, int nb_neurones, long int nb_elem)
{
    printf("\nDONNEES DES NEURONES:\n");
   
    for(int i = 0; i < nb_neurones; i++)
    {   
        printf("n%d\n ", i+1);
        for(int y = 0; y < nb_elem; y++)
        {
            printf("%0.1f ", neural_map[i]->mem[y]);
        }
        printf("\n");
    }
}

void printEtiq(neural_m** neural_map, int nb_neurones, int nb_column)
{
	for(int i = 0; i < nb_neurones; i++)
	{
		if(i%nb_column == 0)
			printf("\n");
		/*if(neural_map[i]->etiquette == 0)
			couleur("31");	
		else if(strcmp(neural_map[i]->etiquette, "vir") == 0)
			couleur("32");	
		else if(strcmp(neural_map[i]->etiquette, "ver") == 0)
			couleur("34");	*/
		printf("%d ", neural_map[i]->etiquette);
		//couleur("0");
	}
	printf("\n");
}

void printIntVec(int* indice_voisins, size_t size)
{
    printf("\n");
    for(int i = 0;i < size; i++)
    {
        if(i%5 == 0)
            printf("\n");
        printf("%d ", indice_voisins[i]);
    }
}

//Retourne la liste des voisins du BMU choisi
int* voisinage(int rayon, int bmu, grille neural_grid)
{
    int i_bmu, y_bmu;
   /* for(int i = 0; i < neural_grid.nb_line; i++)
    {
        for(int y = 0; y < neural_grid.nb_column; y++, bmu--)
            if(bmu == 0)
            {
                i_bmu = i;
                y_bmu = y;
            }  
    } */
    i_bmu = bmu / neural_grid.nb_column;
    y_bmu = bmu % neural_grid.nb_column;
               
    int c = 0;
    int d = 0;
    int *_v = malloc(sizeof(int)*pow(rayon*2+1, 2));
    int vi = 0;
    while(c != rayon+1)
    {
        while(d != rayon+1)
        {        
            if(i_bmu+c < neural_grid.nb_line && y_bmu+d < neural_grid.nb_column && neural_grid._rect[i_bmu+c][y_bmu+d] != -4)
            {
                _v[vi] = neural_grid._rect[i_bmu+c][y_bmu+d];
                neural_grid._rect[i_bmu+c][y_bmu+d] = -4;
            }
            if(i_bmu-c >= 0 && y_bmu-d >= 0 && neural_grid._rect[i_bmu-c][y_bmu-d] != -4)
            {   
                _v[vi] = neural_grid._rect[i_bmu-c][y_bmu-d];
                 neural_grid._rect[i_bmu-c][y_bmu-d] = -4;
                
            }    
            if(i_bmu+c < neural_grid.nb_line && y_bmu-d >= 0 && neural_grid._rect[i_bmu+c][y_bmu-d] != -4)
            {
                _v[vi] = neural_grid._rect[i_bmu+c][y_bmu-d];
                neural_grid._rect[i_bmu+c][y_bmu-d] = -4;
                
            }
            if(i_bmu-c >= 0 && y_bmu+d < neural_grid.nb_column && neural_grid._rect[i_bmu-c][y_bmu+d] != -4)
            {
                _v[vi] = neural_grid._rect[i_bmu-c][y_bmu+d];
                neural_grid._rect[i_bmu-c][y_bmu+d] = -4;
                  
            } 
            vi++;
            d++;    
        }
        d = 0; 
        c++;
    }
    neural_grid.nb_voisin[0] = vi;
    return _v;
          
}


//DEBUT APPRENTISSAGE
void apprendre(neural_m** neural_map, uint8_t* data, double alpha, int* voisins, size_t nb_voisin, long nb_elem)
{
    //printVecNeuralMap(neural_map, 500, nb_elem);
	for(int i = 0; i < nb_voisin;i++)
	{
	    for(int y = 0;y<nb_elem;y++)
	    {
            //printf("i=%d y=%d %.02lf \n",i,y, neural_map[voisins[i]]->mem[y]);
	        neural_map[voisins[i]]->mem[y] += alpha * ((double)data[y] - neural_map[voisins[i]]->mem[y]);
	    }
	}
}

//Retourne les meilleurs neurones
BMU* getBMU(neural_m** neural_map, uint8_t* one_data, int nb_neurones, long int nb_elem)
{
    double min = DBL_MAX;
  
    //ici on fais la distance eulidienne et calcul de la + petite distance
    for(int i=0; i < nb_neurones; i++)
    {
        neural_map[i]->act = euclidean_distance(neural_map[i]->mem, one_data, nb_elem);
        //printf(" distance = %lf\n", neural_map[i]->act);
        if(neural_map[i]->act < min)
            min = neural_map[i]->act;
    }

   
 	BMU* bmu = malloc(sizeof(BMU));
 	bmu->best_indice = malloc(sizeof(int)*nb_neurones);
 	bmu->nb_bmu = 0;
    int y= 0;
    //Attribution DES meilleurs neurones
    for(int i=0; i < nb_neurones; i++)
    {
        if(neural_map[i]->act == min)
        {   
            //printf("\nBMU FOUND\n");
            bmu->best_indice[y] = i;
            y++;
            bmu->nb_bmu++;
        }
    }
    return bmu;
}

void readll(BMU* bmu_list)
{
    for(int i = 0; i < bmu_list->nb_bmu; i++)
    {
    	printf("\nBMU n%d:\t\t\t\t%d\n", i, bmu_list->best_indice[i]);
    }
}



