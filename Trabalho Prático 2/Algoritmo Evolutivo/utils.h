//
// Created by Hugo on 16/01/2022.
//

#ifndef EVOLUTIVO_UTILS_H
#define EVOLUTIVO_UTILS_H
void imprime_matriz(int *grafo, int vert);

int* init_dados(char *nome, int *n,int *lig);

void init_data(char *filename, int *mat, struct  info *x );

pchrom init_pop(struct info);

void print_pop(pchrom, struct info);

chrom get_best(pchrom, struct info, chrom);

void write_best(chrom, struct info);

void init_rand();

int random_l_h(int, int);

float rand_01();

int flip();

#endif //EVOLUTIVO_UTILS_H
