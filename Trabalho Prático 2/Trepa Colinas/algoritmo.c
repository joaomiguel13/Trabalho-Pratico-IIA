#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"

#define PROB 0.01
#define TMAX 0.99
#define TMIN 0.0001


void gera_vizinho(int a[], int b[], int n){
    int i, p1, p2;


    for(i = 0; i < n; i++)
        b[i] = a[i];
//// Encontra posicao com valor 0
    do
        p1=random_l_h(0, n-1);
    while(b[p1] != 0);
//// Encontra posicao com valor 0
    do
        p2=random_l_h(0, n-1);
    while(b[p2] != 1);
//// Troca
    b[p1] = 1;
    b[p2] = 0;
}

void gera_vizinho2(int a[], int b[], int n){
    int i, p1, p2, p3, p4;

    // Copia a solução atual para a solução vizinha
    for(i = 0; i < n; i++)
        b[i] = a[i];
    // Encontra aleatoriamente a posição de um vértice com valor 0
    do
        p1 = random_l_h(0, n-1);
    while(b[p1] != 0);
    // Encontra aleatoriamente a posição de um vértice com valor 1
    do
        p2 = random_l_h(0, n-1);
    while(b[p2] != 1);
    // Troca os valores dos vértices das posições encontradas
    b[p1] = 1;
    b[p2] = 0;
    // Encontra aleatoriamente a posição de um vértice, que não seja igual a p2, com valor 0
    do
        p3 = random_l_h(0, n-1);
    while(b[p3] != 0 || p3 == p2);
    // Encontra aleatoriamente a posição de um vértice, que não seja igual a p1, com valor 1
    do
        p4 = random_l_h(0, n-1);
    while(b[p4] != 1 || p4 == p1);
    // Troca os valores dos vértices das posições encontradas
    b[p3] = 1;
    b[p4] = 0;
}

// Trepa colinas first-choice
// Parametros: solucao, matriz de adjacencias, numero de vertices e numero de iteracoes
// Devolve o custo da melhor solucao encontrada
int trepa_colinas(int sol[], int *mat, int vert, int num_iter)
{
    int *nova_sol, custo, custo_viz, i;

    nova_sol = malloc(sizeof(int)*vert);
    if(nova_sol == NULL)
    {
        printf("Erro na alocacao de memoria");
        exit(1);
    }
//// Avalia solucao inicial
    custo = calcula_fit(sol, mat, vert);
    for(i=0; i<num_iter; i++)
    {
//// Gera vizinho
        gera_vizinho(sol, nova_sol, vert);
//// Avalia vizinho
        custo_viz = calcula_fit(nova_sol, mat, vert);
//// Aceita vizinho se o custo aumentar (problema de maximização)
        if(custo_viz > custo)  ////Aceitar custos iguais >= ??
        {
            substitui(sol, nova_sol, vert);
            custo = custo_viz;
        }
    }
    free(nova_sol);
    return custo;
}

int trepa_colinas_probabilistico(int sol[], int *mat, int vert, int num_iter)
{
    int *nova_sol, custo, custo_viz, i;

    nova_sol = malloc(sizeof(int)*vert);
    if (nova_sol == NULL)
    {
        printf("Erro na alocacao de memoria");
        exit(1);
    }

    custo = calcula_fit(sol, mat, vert);
    for(i = 0; i < num_iter; i++)
    {
////Na aula usamos gera_vizinho
////gera_vizinho(sol, nova_sol, vert);
        gera_vizinho(sol, nova_sol, vert);
        custo_viz = calcula_fit(nova_sol, mat, vert);

//// ACEITA CUSTOS IGUAIS >= ??
        if (custo_viz >= custo)
        {
            substitui(sol, nova_sol, vert);
            custo = custo_viz;
        }
        else
        {
            if (rand_01() < PROB)
            {
                substitui(sol, nova_sol, vert);
                custo = custo_viz;
            }
        }
    }

    free(nova_sol);
    return custo;
}
