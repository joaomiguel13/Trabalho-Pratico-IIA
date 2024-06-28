#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algoritmo.h"
#include "utils.h"
#include "funcao.h"

#define DEFAULT_RUNS 1000   //// 30?

int main(int argc, char *argv[])
{
    char    nome_fich[100];
    int     vert,  num_iter = 5000, k, runs, custo, best_custo, nVertMax;
    int     *grafo, *sol, *best;
    float   mbf = 0.0;

    printf("Nome do Ficheiro: ");
    gets(nome_fich);

    printf("\n");

    printf("Numero de runs: ");
    scanf("%d", &runs);

    if (runs <= 0)
        return 0;

    init_rand();

    //// Preenche matriz de adjacencias
    grafo = init_dados(nome_fich, &vert, &nVertMax);

    imprime_matriz(grafo, vert);       // Imprimir matriz

    sol = malloc(sizeof(int)*vert);
    best = malloc(sizeof(int)*vert);

    if(sol == NULL || best == NULL)
    {
        printf("Erro na alocacao de memoria");
        exit(1);
    }

    for(k=0; k<runs; k++)
    {
        gera_sol_inicial(sol, vert, nVertMax);
        puts("\n");
        printf("\nSolucao Inicial %d:", k);
        escreve_sol(sol, vert);

//// TREPA COLINAS
        custo = trepa_colinas_probabilistico(sol, grafo, vert, num_iter);

//// Escreve resultados da repeticao k
        printf("\nRepeticao %d:", k);
        escreve_sol(sol, vert);
        printf("\nCusto final: %2d\n", custo);
        mbf += custo;

        if(k==0 || best_custo <= custo)
        {
            best_custo = custo;
            substitui(best, sol, vert);
        }

    }

//// Escreve resultados globais
    printf("\n\nMBF: %f\n", mbf/k);
    printf("\nMelhor solucao: ");
    escreve_sol(best, vert);
    printf("\nCusto final: %2d\n", best_custo);
    puts("\n");

    free(grafo);
    free(sol);
    free(best);
    return 0;
}