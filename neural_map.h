//Réseau de neuronne Self Organizing Map
//Neural_map header

#ifndef H_NEURAL_MAP
#define H_NEURAL_MAP

//Grille 

typedef struct grille
{
    int nb_column;
    int nb_line;
    int **_rect; // Grille de neurone
    size_t* nb_voisin;
}grille;

//vecteur de neurones
typedef struct neural_m
{
	double *mem;  // Vecteur de poids
	double act;   // Distance euclidienne
	int etiquette; //Etiquette = digit
}neural_m;

typedef struct BMU
{
	int* best_indice;
	int nb_bmu;
}BMU;

grille initGrid(int);
void resetGrid(int**, int, int);
void printGrid(int**, int, int);
void initNeuralMap(neural_m**, uint8_t*, int, long int);
void printIntVec(int *, size_t);
void printVecNeuralMap(neural_m**, int, long int);
int * voisinage(int, int, grille);
void apprendre(neural_m**, uint8_t*, double, int*, size_t, long int);
BMU* getBMU(neural_m**, uint8_t*, int, long int);
void readll(BMU*);
void printEtiq(neural_m**, int, int);
#endif
