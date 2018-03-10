//Réseau de neuronne Self Organizing Map
//Ce code est fait pour fonctionner sous Linux
//Remplacer le parser pour multi-plateforme
//main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "data.h"
#include "formulas.h"
#include "MNIST_parser.h"
#include "neural_map.h"


/* TODO: - Normalisation! DISTANCE EUCLIDIENNE RESOLU.
		 - Observer l'étiquetage lors d'une longue sessions d'apprentissage
*/

int main(int argc, char *argv[])
{
    FILE *datafile = fopen(argv[1], "rb");
    FILE *labelfile = fopen(argv[2], "rb");
    if(!datafile || !labelfile)
    {
    	printf("Error while opening files");
    	return 0;
    }
    IDX_STRUCT database;
    IDX_LABEL label;
    srand((unsigned)getpid());

    //Initialisation de la base de donnée
	init(datafile, &database);
	initLabel(labelfile, &label);
	database.data = malloc(sizeof(DATABASE) * database._dim_size[0]); //NB_ELEM * sizeof one_element
    parser(datafile, &database);
    parserLabel(labelfile,&database, &label);

    //test BDD ici
    printf("\nData type:\t\t\t<0x%0X> \n", database.data_type);
	printf("Data size:\t\t\t%d \n", database.data_size);
	printf("nb_dimension:\t\t\t%u\n", database.nb_dim);
	printf("nb_image:\t\t\t%u\n", database._dim_size[0]);
    printf("nb pix/image:\t\t\t%ld\n________________\n", database.nb_elem);
    printf("Label Data type:\t\t<0x%0X> \n", label.data_type);
	printf("Label Data size:\t\t%d \n", label.data_size);
	printf("Label nb_dimension:\t\t%u\n", label.nb_dim);
	printf("Label nbelem:\t\t\t%u\n________________\n", label._dim_size[0]);
    //La NORME peut-etre a revoir
    normalisation(&database);
    //for(int i=0; i < database._dim_size[0]; i++)
    	//printf("%d = %d\n",i, database.data[i].nom);

    //Initialisation du vecteur moyen
    database._vec_moyen = malloc(sizeof(uint8_t) * database.nb_elem);
	average(&database);

	//Initialisation de la grille
	database.nb_neurone = sqrt(database._dim_size[0]);
	grille grid;
	grid = initGrid(database.nb_neurone);
	database.nb_neurone = (grid.nb_line*grid.nb_column); //TODO: a adapter
	printf("\nnb_neurone:\t%d", database.nb_neurone);

    //Initialisation reseau neurones  
    neural_m** neural_map = malloc(database.nb_neurone * sizeof(neural_m*));
	initNeuralMap(neural_map, database._vec_moyen, database.nb_neurone, database.nb_elem);
	//printVecNeuralMap(neural_map, database.nb_neurone, database.nb_elem);
	//printData(database);
    //printGraph(database);
	//printVecNeuralMap(neural_map, database.nb_neurone, database.nb_elem);
	//Initialisation de l'apprentissage
    BMU* bmu_list;
    int * indice_voisins;
    int rayon = ceil(sqrt(database.nb_neurone/2)/2);
    int i_ite = 0;
    int i_etiquette;
    double alpha;
    double alpha_init = 0.8f;
    double rapport;
    int nb_iteration = 100;
    int phase2 = nb_iteration/4;
	
    int labelcount[database.nb_neurone][10];

    for(int i = 0; i < database.nb_neurone; i++)
	{
		for(int y = 0; y < 10; y++)
		{
			labelcount[i][y] = 0;
		}
	}

	while(i_ite < nb_iteration)
	{ 
	    grid.nb_voisin[0] = (int) (rayon*2+1) * rayon;
	    //printf("\nNB_VOISIN ESTIME:\t\t%d", grid.nb_voisin[0]);
	    //printf("\nRAYON_VOISIN ESTIME:\t\t%d", rayon);
	    if(i_ite == phase2/3 && rayon > 1)
	    	rayon--;
	    else if(i_ite == phase2/2 && rayon > 1)
	    	rayon--;
	    else if(i_ite == phase2 && rayon > 1)
	    {
	    	rayon--;
	    	alpha_init = 0.08f;
	    }
	   	else
	   	{
	    	rapport = (double) (i_ite+1.0f)/nb_iteration;
	    	alpha = alpha_init * (1.0f- rapport);
	    	////printf("\nAlpha:\t\t\t\t%lf", alpha);
	    } 
	    int* tmp_ind = shuffle2(10000);
	    printf("\n");
	    for(int i = 0; i < 1000; i++)
	    {
			//MEILLEUR NEURONES
			bmu_list = getBMU(neural_map, database.data[tmp_ind[i]]._data, database.nb_neurone, database.nb_elem);
			i_etiquette = rand()%bmu_list->nb_bmu;
			labelcount[bmu_list->best_indice[i_etiquette]][database.data[tmp_ind[i]].nom]++;
			//printf("bmu %d vecdata: %d\n", bmu_list->best_indice[i_etiquette], tmp_ind[i]);
			//ETIQUETAGE Du BMU
			neural_map[bmu_list->best_indice[i_etiquette]]->etiquette = database.data[tmp_ind[i]].nom;
			indice_voisins = voisinage(rayon, bmu_list->best_indice[i_etiquette], grid);
			/*printf("NB_VOISIN REEL:\t\t\t%d\n", grid.nb_voisin[0]);
			printf("\nLISTE DES VOISINS");
			for(int i = 0; i < grid.nb_voisin[0];i++)
			{
				if(i%10 == 0)
					printf("\n");
				printf("%d ",indice_voisins[i]);
			}*/

			//printData(database);
			resetGrid(grid._rect, grid.nb_line, grid.nb_column);
			apprendre(neural_map, database.data[tmp_ind[i]]._data, alpha, indice_voisins, grid.nb_voisin[0], database.nb_elem);
        }
        i_ite++;
        printf("\nProgression: %f%%", rapport*100);
        printf("alpha: %lf rayon: %d, nb_voisin: %zu\n ",alpha, rayon, grid.nb_voisin[0]);
	}
	printVecNeuralMap(neural_map, 2, database.nb_elem);
	printEtiq(neural_map, database.nb_neurone, grid.nb_column);
	//printGraph2(database, neural_map);
	//ECRITURE BINAIRE OBLIGATOIRE AVEC FWRITE + CAST INT + suizeof(uint8_t) 
	FILE* output = fopen("MNIST_neurones.txt", "wb+");
	FILE* label_out = fopen("MNIST_labels.txt", "wb+");

	//ECRITURE DE LA MEMOIRE DES NEURONES
	for(int y = 0; y < database.nb_neurone; y++)
	{
		printf("\n\n");
		int tmp[28*28];
		for(int i = 0; i < 28*28;i++)
		{
			tmp[i] = (int) neural_map[y]->mem[i];
			fwrite(&tmp[i], sizeof(uint8_t), 1, output);
			//printf("%d %X|", tmp[i], (uint8_t) tmp[i]);
		}
	}

	//ECRITURE DES LABELS
	for(int i = 0; i < database.nb_neurone; i++)
	{
		fwrite(&neural_map[i]->etiquette, sizeof(uint8_t), 1, label_out);
	}

	//STATS DE DECLENCHEMENT
	for(int i = 0; i < database.nb_neurone; i++)
	{
		printf("\n neurones %d:\t", i);
		for(int y = 0; y < 10; y++)
		{
			printf("%d,", labelcount[i][y]);
		}
		printf("\n");
	}

	fclose(label_out);
	fclose(output);

	char commande[] = "python MNIST_viewer.py 100";
	system(commande);
	fclose(datafile);
	fclose(labelfile);
	return 0;	
}
