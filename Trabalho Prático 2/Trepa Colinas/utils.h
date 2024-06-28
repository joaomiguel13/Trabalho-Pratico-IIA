#ifndef TREPACOLINAS_UTILS_H
#define TREPACOLINAS_UTILS_H

int* init_dados(char *nome, int *n, int *nVerMax);
void gera_sol_inicial(int *sol, int v, int k);
void escreve_sol(int *sol, int vert);
void substitui(int a[], int b[], int n);
void init_rand();
int random_l_h(int min, int max);
float rand_01();
int flip();
void imprime_matriz(int *grafo, int vert);

#endif //TREPACOLINAS_UTILS_H