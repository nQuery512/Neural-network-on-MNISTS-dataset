#ifndef H_DATA
#include <stdint.h>
#include "neural_map.h"
#define H_DATA

//typedef void* data;

typedef struct DATABASE
{
	uint8_t *_data;
	double _norme;
	uint8_t nom; //Le chiffre
}DATABASE;

typedef struct IDX_STRUCT
{
	DATABASE* data;
	uint8_t* _vec_moyen;
	long nb_elem;
	uint32_t* _dim_size;//size of each dimensions
	short data_size;//The size of one element
	uint8_t data_type;//Data code in hex
	uint8_t nb_dim;//Number of dimensions
	int nb_neurone;
}IDX_STRUCT;

typedef struct IDX_LABEL
{
	uint32_t* _dim_size;//size of each dimensions
	short data_size;//The size of one element
	uint8_t data_type;//Data code in hex
	uint8_t nb_dim;//Number of dimensions
	long nb_elem;
}IDX_LABEL;

void init(FILE*, IDX_STRUCT*);
void initLabel(FILE*, IDX_LABEL*);
void printGraph(IDX_STRUCT);
void printGraph2(IDX_STRUCT, neural_m**);
void printData(IDX_STRUCT);
void parser(FILE*, IDX_STRUCT*);
void parserLabel(FILE*, IDX_STRUCT*, IDX_LABEL*);
void skipUByte(FILE*, int);
uint8_t getUByte(FILE*);
uint32_t getUInt32(FILE*);

#endif