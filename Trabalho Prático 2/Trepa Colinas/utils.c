#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"
#include <string.h>

//// Leitura do ficheiro de input
//// Recebe: nome do ficheiro, numero de vertices (ptr), numero de iteracoes (ptr)
//// Devolve a matriz de adjacencias
int* init_dados(char *nome, int *n, int *nVerMax){
    FILE    *f;
    int     *p;
    int     i, j, lig, lin, col;
    char    str[100];

    f=fopen(nome, "r");

    if(!f){
        printf("Erro no acesso ao ficheiro dos dados\n");
        exit(1);
    }

    fscanf(f, "%s %d",str,nVerMax);

    while(strcmp(str,"edge")){
        fscanf(f,"%s",str);         //// edge numero_vertices numero_arestas
    }
    fscanf(f, "%d", n);             //// NÚMERO DE VÉRTICES
    fscanf(f, "%d", &lig);          //// NÚMERO DE ARESTAS

    p = malloc(sizeof(int)*(*n)*(*n));      //// p = Ponteiro para a matriz (ainda vazia)
    if(!p){
        printf("Erro na alocacao de memoria\n");
        exit(1);
    }
    for(i=0; i<*n; i++)
        for(j=0; j<*n; j++)
            *(p+(*n)*i+j)=0;

    for(i=0; i<lig; i++)
    {
        fscanf(f, " e %d %d", &lin, &col);      //// PREENCHER ARESTAS COM OS 2 VÉRTICES
        *(p+(*n)*(lin-1)+col-1)=1;
        *(p+(*n)*(col-1)+lin-1)=1;
    }
    fclose(f);
    return p;
}

// Gera a solucao inicial
// Parametros: solucao, numero de vertices
void gera_sol_inicial(int *sol, int v, int k)
{
    int i, x;

    for(i=0; i<v; i++)
        sol[i]=0;
    for(i=0; i<k; i++)
    {
        do
            x = random_l_h(0, v-1);
        while(sol[x] != 0);
        sol[x]=1;
    }
}

// Escreve solucao
// Parametros: solucao e numero de vertices
void escreve_sol(int *sol, int vert)
{
    int i;

    printf("\nConjunto A: ");
    for(i=0; i<vert; i++)
        if(sol[i]==0)
            printf("%2d  ", i);
    printf("\nConjunto B: ");
    for(i=0; i<vert; i++)
        if(sol[i]==1)
            printf("%2d  ", i);
    printf("\n");
}

//// copia vector b para a (tamanho n)
//// void substitui(int a[], int b[], int n)
void substitui(int a[], int b[], int n){
    int i;
    for (i = 0; i < n; i++)
        a[i] = b[i];
}

//// // Inicializa o gerador de numeros aleatorios
void init_rand(){
    srand((unsigned)time(NULL));
}

//// Devolve valor inteiro aleatorio entre min e max
int random_l_h(int min, int max){
    return min + rand() % (max - min + 1);
}

//// Devolve um valor real aleatorio do intervalo [0, 1]
float rand_01(){
    return ((float)rand()) / RAND_MAX;
}

void imprime_matriz(int *grafo, int vert){
    for (int i = 0; i < vert; i++) {            // MATRIZ 6x6 (teste.txt)
        printf("\n");
        for (int j = 0; j < vert; j++) {
            printf("%d ", grafo[i*vert+j]);
        }
    }
}