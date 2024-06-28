//
// Created by Hugo on 16/01/2022.
//

#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "algoritmo.h"
#include "utils.h"
#include <string.h>

void imprime_matriz(int *grafo, int vert)
{
    for (int i = 0; i < vert; i++)
    {
        printf("\n");
        for (int j = 0; j < vert; j++)
        {
            printf("%d ", grafo[i*vert+j]);
        }
    }
}

void init_rand(){
    srand((unsigned)time(NULL));
}


void init_data(char *filename, int *mat, struct  info *x ){

    FILE    *f;
    char    str[100];
    int     i, j, lin, col;
    int     nrligacoes, nrVertices;

    // Leitura dos parametros do problema


    f=fopen(filename, "r");
    if(!f){
        printf("Erro no acesso ao ficheiro dos dados\n");
        exit(1);
    }

    fscanf(f,"k %d",&x->capacity);

    while(strcmp(str,"edge"))
        fscanf(f,"%s %d %d",str, &x->numGenes, &nrligacoes);


    if (x->numGenes > MAX_OBJ)
    {
        printf("Number of itens is superior to MAX_OBJ\n");
        exit(1);
    }

    // Preenchimento da matriz
    for(i=0; i<x->numGenes; i++)
        for(j=0; j<x->numGenes; j++)
            *(mat+(x->numGenes)*i+j)=0;
    for(i=0; i<nrligacoes; i++)
    {
        fscanf(f, " e %d %d", &lin, &col);
        *(mat+x->numGenes*(lin-1)+col-1)=1;
        *(mat+x->numGenes*(col-1)+lin-1)=1;
    }
    fclose(f);

}

int flip(){
    if ((((float)rand()) / RAND_MAX) < 0.5)
        return 0;
    else
        return 1;
}


pchrom init_pop(struct info d){
    int     i, j;
    pchrom  indiv;

    indiv = malloc(sizeof(chrom)*d.popsize);
    if (indiv==NULL)
    {
        printf("Erro na alocacao de memoriaaa\n");
        exit(1);
    }
    for (i=0; i<d.popsize; i++)
    {
        for (j=0; j<d.numGenes; j++)
            indiv[i].p[j] = flip();
    }



    return indiv;
}

chrom get_best(pchrom pop, struct info d, chrom best){
    int i;

    for (i=0; i<d.popsize; i++)
    {
        if (best.fitness < pop[i].fitness)
            best=pop[i];
    }
    return best;
}

int random_l_h(int min, int max){
    return min + rand() % (max-min+1);
}

float rand_01(){
    return ((float)rand())/RAND_MAX;
}


void write_best(chrom x, struct info d){
    int i;

    printf("\nBest individual: %4.1f\n", x.fitness);
    for (i=0; i<d.numGenes; i++)
        printf("%d", x.p[i]);
    putchar('\n');
}
