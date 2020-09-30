#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <iostream>
#include <limits.h>
#include <float.h>
#include "arraylist.h"

#define MAX(x,y) ((x)<(y) ? (y) : (x))

typedef struct{
	int id;
	double peso;        // peso do objeto
	double utilidade;   // utilidade do objeto
	double profit;      // profit do objeto (utilidade/peso)
} Objeto;

// Menus
int menu_principal(void);
int menu_construtivo(void);
int menu_busca_local(void);
int menu_metaheuristicas(void);

// Util
void le_arquivo(const char *nomearq, double *vetor);
double calcula_fo(int *s, int num_objetos, double *p, double *w, double b);
void imprime_solucao(int *s, int num_objetos, double *p, double *w, double b);
const Boolean obj_equals(const Object object_1, const Object object_2);
void troca_bit(int *s, int j);

// Lista encadeada
Arraylist cria_lista_objetos(int n, int *s, double *p, double *w);
Arraylist cria_lista_objetos_ordenada(int n, int *s, double *p, double *w);
void imprime_lista(Arraylist lista);

// Contrutivos
void constroi_solucao(int n, int *s, double *p, double *w, double b, double percentual);
void constroi_solucao_aleatoria(int n, int *s, double *p, double *w, double b);

// Busca Local
void busca_local_primeiro_aprimorante(int n, int *s, double *p, double *w, double b);
void busca_local_melhor_aprimorante(int n, int *s, double *p, double *w, double b);
void busca_local_randomica(int n, int *s, double *p, double *w, double b, int iter_max);
