#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include "MNIST_parser.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

//IDX parser (ubyte)

//Return the first byte in file 
uint8_t getUByte(FILE* fd)
{
	uint8_t c;
	fread(&c, sizeof(c), 1, fd);
	return c;
}

uint32_t getUInt32(FILE* fd)
{
	uint8_t c1;
	uint8_t c2;
	uint8_t c3;
	uint8_t c4;
	fread(&c1, sizeof(c1), 1, fd);
	fread(&c2, sizeof(c2), 1, fd);
	fread(&c3, sizeof(c3), 1, fd);
	fread(&c4, sizeof(c4), 1, fd);

	//Shift
	uint32_t v;
	v = (c1<<24)|(c2<<16)|(c3<<8)|(c4);
	
	return v;
}

//skip nb_byte in file
void skipUByte(FILE* fd, int nb_byte)
{
	uint8_t c;
	int i = 0;
	while(i < nb_byte)
	{
		fread(&c, sizeof(c), 1, fd);
		i++;
	}
}

//Store magic_number + n_size 
void init(FILE* fd, IDX_STRUCT* data)
{
	int i = 0;
	skipUByte(fd, 2);
	data->data_type = getUByte(fd);
	data->nb_dim = getUByte(fd);
	data->_dim_size = malloc(sizeof(uint32_t)* data->nb_dim);
	data->nb_elem = 1;
	//Fill the dimension array  
	while(i < data->nb_dim)
	{
		data->_dim_size[i] = getUInt32(fd);
		if(i != 0)
			data->nb_elem *= data->_dim_size[i];
		i++;
	}
	//UNSIGNED BYTE
	if((int)data->data_type == 8)
		data->data_size = sizeof(uint8_t);
	else if((int)data->data_type == 9)
		data->data_size = sizeof(int8_t);
	else if((int)data->data_type == 11)
		data->data_size = sizeof(int16_t);
	else if((int)data->data_type == 12)
		data->data_size = sizeof(uint32_t);
	else if((int)data->data_type == 13)
		data->data_size = sizeof(int32_t);
	else if((int)data->data_type == 14)
		data->data_size = sizeof(int64_t);
	else
	{
		printf("\nERROR\n");
		return ;
	}
}

void initLabel(FILE* fd, IDX_LABEL* data)
{
	int i = 0;
	skipUByte(fd, 2);
	data->data_type = getUByte(fd);
	data->nb_dim = getUByte(fd);
	data->_dim_size = malloc(sizeof(uint32_t)* data->nb_dim);
	data->nb_elem = 1;
	//Fill the dimension array  
	while(i < data->nb_dim)
	{
		data->_dim_size[i] = getUInt32(fd);
		if(i != 0)
			data->nb_elem *= data->_dim_size[i];
		i++;
	}
	//UNSIGNED BYTE
	if((int)data->data_type == 8)
		data->data_size = sizeof(uint8_t);
	else if((int)data->data_type == 9)
		data->data_size = sizeof(int8_t);
	else if((int)data->data_type == 11)
		data->data_size = sizeof(int16_t);
	else if((int)data->data_type == 12)
		data->data_size = sizeof(uint32_t);
	else if((int)data->data_type == 13)
		data->data_size = sizeof(int32_t);
	else if((int)data->data_type == 14)
		data->data_size = sizeof(int64_t);
	else
	{
		printf("\nERROR\n");
		return ;
	}
}

void printData(IDX_STRUCT database) 
{
	for(int i = 0;i<database._dim_size[0];i++)
		{
			int y = 0;
			printf("IMAGE %u\n", database.data[i].nom);
			while(y < database.nb_elem)
			{
				printf("%u ", database.data[i]._data[y]);
				y++;
			}
			printf("\n____________________________________________________________________________\n\n");
			
		}
}

void printGraph(IDX_STRUCT database)
{
	int i = 0;
	while(i < database._dim_size[0]) //SIZE[0] = NB_IMAGE
	{
		int y = 0;
		switch(rand()%5)
		{
			case 0:
				printf(ANSI_COLOR_RED);
				break;
			case 1:
				printf(ANSI_COLOR_CYAN);
				break;
			case 2:
				printf(ANSI_COLOR_YELLOW);
				break;
			case 3:
				printf(ANSI_COLOR_BLUE);
				break;
			case 4:
				printf(ANSI_COLOR_GREEN);
				break;
			default:
				printf("\n ERROR\n");
				break;
		};

		printf("\nlabel : %u", database.data[i].nom);
		while(y < database.nb_elem)
		{
			if(y%database._dim_size[1] == 0)
				printf("\n");
			if(database.data[i]._data[y] == 0)
				printf("  ");
			else
				printf("**");
				
			y++;
		}
		puts("Appuyez sur ENTREE pour continuer...");
   		getchar();
		i++;
		printf(ANSI_COLOR_RESET);
	}
}

void printGraph2(IDX_STRUCT database, neural_m** neuralmap)
{
	int i = 0;
	while(i < database.nb_neurone) //SIZE[0] = NB_IMAGE
	{
		int y = 0;
		switch(rand()%5)
		{
			case 0:
				printf(ANSI_COLOR_RED);
				break;
			case 1:
				printf(ANSI_COLOR_CYAN);
				break;
			case 2:
				printf(ANSI_COLOR_YELLOW);
				break;
			case 3:
				printf(ANSI_COLOR_BLUE);
				break;
			case 4:
				printf(ANSI_COLOR_GREEN);
				break;
			default:
				printf("\n ERROR\n");
				break;
		};

		printf("\nlabel : %u", database.data[i].nom);
		while(y < database.nb_elem)
		{
			if(y%database._dim_size[1] == 0)
				printf("\n");
			else
				printf("%f ", database.data[y]);
				
			y++;
		}
		puts("Appuyez sur ENTREE pour continuer...");
   		getchar();
		i++;
		printf(ANSI_COLOR_RESET);
	}
}

void parser(FILE* fd, IDX_STRUCT* database)
{
	int i = 0;
	int count;
	while(i < database->_dim_size[0])
	{		
		database->data[i]._data = malloc(sizeof(uint8_t) * database->nb_elem);
		count = fread(database->data[i]._data, database->data_size*database->nb_elem, 1, fd);
		if(count == 0)
		{
			printf("\nERROR\n");
			break;
		}
		i++;
	}
}

void parserLabel(FILE* fd, IDX_STRUCT* database, IDX_LABEL* label)
{
	int i = 0;
	int count;
	while(i < database->_dim_size[0])
	{		
		count = fread(&database->data[i].nom, database->data_size, 1, fd);
		if(count == 0)
		{
			printf("\nERROR\n");
			break;
		}
		//printf("\nLABEL %u", database->data[i].nom);
		i++;
	}
}