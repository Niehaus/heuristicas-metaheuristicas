#include "pmochila.h"
#include <string.h>
#include <time.h> //clock(), CLOCKS_PER_SEC e clock_t


int main(int argc, char **argv) {
	int n;              // numero de objetos
	double b;           // capacidade da mochila
	int *s;             // vetor solucao corrente
	int *s_star;        // vetor melhor solucao
	double *w;          // vetor de peso de cada objeto
	double *p;          // vetor de utilidade de cada objeto
	double fo;          // funcao objetivo corrente
	double fo_star;     // melhor funcao objetivo
	
	int choice;
	
	n = atoi(argv[1]); // numero de objetos
	const char *file_b = argv[2]; // arquivo de capacidade
	const char *file_w = argv[3]; // arquivo de pesos
	const char *file_p = argv[4]; // arquivo de utilidades
	
	srand((unsigned) time(NULL)); // pega a hora do relogio como semente
	
	// Cria os vetores
	s = (int *) malloc(n * sizeof(int));
	s_star = (int *) malloc(n * sizeof(int));
	w = (double *) malloc(n * sizeof(double));
	p = (double *) malloc(n * sizeof(double));
	
	// Le os arquivos da instancia a ser testada
	le_arquivo(file_b, &b); // capacidade
	le_arquivo(file_w, w); // peso
	le_arquivo(file_p, p); // utilidade
	fo_star = - DBL_MAX; // inicializa FO da melhor solucao

	clock_t t; //variável para armazenar tempo
	FILE *fp; 
	fp = fopen("resultados03.txt", "a+"); 
	

	fprintf(fp, "%d,", n);
	t = clock(); //armazena tempo
	grasp_pr(n, s, p, w, b, 50, 0.7, fp);
	t = clock() - t; //tempo final - tempo inicial
	// printf("Tempo de execucao Grasp Pr: %lf\n", ((double)t) / ((CLOCKS_PER_SEC / 1000))); //conversão para double - imprime o tempo na tela
	fprintf(fp, "%lf",((double)t) / ((CLOCKS_PER_SEC / 1000)));


	t = clock(); //armazena tempo
	grasp(n, s, p, w, b, 50, 0.7, fp);
	t = clock() - t; //tempo final - tempo inicial
	fprintf(fp, ", %lf\n",((double)t) / ((CLOCKS_PER_SEC / 1000)));
	// printf("Tempo de execucao Grasp: %lf\n", ((double)t) / ((CLOCKS_PER_SEC / 1000))); 	//imprime o tempo na tela

	// Libera memoria
	free(s);
	free(s_star);
	free(w);
	free(p);
	fclose(fp);
	return 0;
	
}

// Leitura do arquivo
void le_arquivo(const char *nomearq, double *vetor)
{
	int j;
	double valor;
	FILE *arquivo;
	
	arquivo = fopen(nomearq,"r");
	if (!arquivo) {
		printf("O Arquivo %s nao pode ser aberto.\n", nomearq);
		getchar();
		exit(1);
	}
	j = 0;
	while (!feof(arquivo)){
		if (!fscanf(arquivo, "%lf\n", &valor)) {
			printf("Falha na leitura!\n");
			exit(1);
		}
		vetor[j] = valor;
		j++;
	}
	fclose(arquivo);
}

// Calcula fo
double calcula_fo(int *s, int num_objetos, double *p, double *w, double b)
{
	double fo;
	double utilidade = 0, peso = 0, penalidade = 0;
	
	for (int i = 0; i < num_objetos; i++) {
		if (s[i]) {
			utilidade += p[i];
			peso += w[i];
		}
		penalidade += w[i];
	}
	
	// FO e a soma das utilidades dos objetos na mochila
	// menos o excesso de peso na mochila x penalidade
	fo = utilidade - penalidade * MAX(0, peso - b);
	
	return fo;
}

// Imprime solucao
void imprime_solucao(int *s, int num_objetos, double *p, double *w, double b)
{
	double fo;
	double utilidade = 0, peso = 0, penalidade = 0;
	
	for (int i = 0; i < num_objetos; i++) {
		if (s[i]) {
			utilidade += p[i];
			peso += w[i];
		}
		penalidade += w[i];
	}
	
	// FO e a soma das utilidades dos objetos na mochila
	// menos o excesso de peso na mochila x penalidade
	fo = utilidade - penalidade * MAX(0, peso - b);
	
	
	printf("FO = %.2lf\n", fo);
    printf("Peso = %.2lf\n", peso);
    printf("Utilidade = %.2lf\n", utilidade);
    for (int j=0; j<num_objetos; j++) printf("s[%2d]=%d \n",j,s[j]);
}

// Verifica se objetos sao iguais
const Boolean obj_equals(const Object object_1, const Object object_2){
	
	Objeto *o1 = (Objeto*)object_1;
	Objeto *o2 = (Objeto*)object_2;
	
	if (o1->id == o2->id) return TRUE;
	else return FALSE;
}

// Cria lista dos objetos 
Arraylist cria_lista_objetos(int n, int *s, double *p, double *w)
{
	Objeto* o;
	Arraylist objetos;
	objetos = arraylist_create(obj_equals);
	   
	// Cria lista de objetos
	for (int i = 0; i < n; i++) {
		o = (Objeto*)malloc(sizeof(Objeto));
		o->id = i;
		o->peso = w[i];
		o->utilidade = p[i];
		o->profit = p[i]/w[i];
		arraylist_add(objetos, o);
	}
	return objetos;
}

// Criar lista dos objetos ordenada
Arraylist cria_lista_objetos_ordenada(int n, int *s, double *p, double *w)
{
	int pos;
	double maior;
	Objeto* o;
	
	Arraylist objetos = cria_lista_objetos(n,s,p,w);
	Arraylist objetosOrd = arraylist_create(obj_equals);
	   
	// Cria lista de objetos ordenada
	while (arraylist_size(objetos) > 0) {
		
		// Busca objeto com maior profit
        maior = -1;
		for (int i = 0; i < arraylist_size(objetos); i++) {
			if ( ((Objeto*)arraylist_get(objetos, i))->profit > maior) {
                maior = ((Objeto*)arraylist_get(objetos, i))->profit;
                pos = i;
			}
		}
        
		// Insere objeto na lista ordenada
		o = (Objeto*) arraylist_remove_index(objetos, pos);
		arraylist_add(objetosOrd, o);
	}
	return objetosOrd;
}

// Imprime lista
void imprime_lista(Arraylist lista){
	
	int size;
	Objeto *o;
	
	if(lista != NULL){
		printf("[ID]\tUtilidade\tPeso\tProfit\n");
		size = arraylist_size(lista);
		for (int i = 0; i < size; i++)
		{
			o = (Objeto*)arraylist_get(lista, i);
			printf("[%d]\t%lf\t%lf\t%lf\n", o->id, o->utilidade, o->peso, o->profit);
		}
		printf("\n");
	}
}

// Insere ou retira o objeto j da mochila
void troca_bit(int *s, int j)
{
    if (s[j])
	s[j] = 0;
    else
	s[j] = 1;
}

// Constroi uma solucao inicial
void constroi_solucao_grasp(int n, int *s, double *p, double *w, double b, double alfa) {
	double peso = 0;
	double capacidade = 0;
	int j, tamRestrito;
    	double value;
	Objeto *o, *o1, *o2;
	
	// Limpa solucao
	for (int j=0; j<n; j++) s[j] = 0;
	
	// Cria lista de objetos ordenados
	Arraylist objetosOrd = cria_lista_objetos_ordenada(n,s,p,w);
	//imprime_lista(objetosOrd);
	
	// Constroi solucao elemento a elemento, verificando se cada objeto cabe na capacidade residual da mochila
	while (arraylist_size(objetosOrd) > 0 && peso < b) {
		
		// Zera tam restrito
		tamRestrito = 0;
	
		// Define o tamanho da lista restrita, ou seja, os alfa % mais interessantes
	
		// Recupera objeto
		o1 = (Objeto*)arraylist_get(objetosOrd, 0);
		o2 = (Objeto*)arraylist_get(objetosOrd, arraylist_size(objetosOrd)-1);
		//printf("cmax: %.2lf   cmin: %.2lf\n", );
		value = o1->profit - alfa * (o1->profit - o2->profit);
		//printf("Valor referencia: %.2lf\n", value);
	
		for (int i = 0; i < arraylist_size(objetosOrd); i++) {
				o = (Objeto*)arraylist_get(objetosOrd, i);
				if (o->profit >= value) tamRestrito++;
				else break;
		}
		//printf("Tam restrito: %d\n", tamRestrito);
		
		// Sorteia posicao aleatoria da lista residual
		j = (int)((float)rand()/RAND_MAX * tamRestrito);
        
		// Recupera objeto
		o = (Objeto*)arraylist_get(objetosOrd, j);
		
		// Se objeto ainda nao esta na mochila e cabe nela, adiciona objeto a mochila
		if (s[o->id] != 1 && peso + o->peso <= b) {
			s[o->id] = 1;
			peso += o->peso;
		}
		
		// Remove objeto da lista, pois ja foi testado
		arraylist_remove_index(objetosOrd, j);
	}
}

/* aplica busca local pela estrategia do melhor aprimorante */
void busca_local_melhor_aprimorante(int n, int *s, double *p, double *w, double b)
{

	// printf("\n\n***************** VIZINHANCA N1 *****************\n\n");

	int melhoria = 1;
	double fo_original;
	double fo_max;
    double fo_vizinho;
	int melhor_bit;
    
    fo_original = calcula_fo(s, n, p, w, b);
	
	// Enquanto melhoria
	while (melhoria) {
		melhoria = 0;
		fo_max = -DBL_MAX;
				
		for (int j = 0; j < n; j++) {
			
			// cria vizinho
			troca_bit(s, j);
            
            fo_vizinho = calcula_fo(s,n,p,w,b);
	
			// armazena melhor vizinho
			if (fo_vizinho > fo_max) {
				melhor_bit = j;
                fo_max = fo_vizinho;
           	}
			
			// volta a solucao inicial
			troca_bit(s,j);
		}
		
		// se encontrou algum vizinho melhor
		if (fo_max > fo_original) {
			troca_bit(s,melhor_bit);
			melhoria = 1;
            		fo_original = fo_max;
			printf("Vizinho melhor! FO = %lf\n", fo_max);
		}
	}	
}

// /* aplica metaheuristica GRASP SUMIKA*/
void grasp(int n, int *s, double *p, double *w, double b, int iter_max, double alfa, FILE* fp) {
	int *sl;
	double fo_star = -DBL_MAX;
	
	// cria solucao auxiliar
	sl = (int *) malloc(n * sizeof(int));
	
	// Enquanto melhoria
	for (int i = 0; i < iter_max; i++) {
		
		// Constroi solucao parcialmente gulosa
		constroi_solucao_grasp(n,sl,p,w,b,alfa);
		
		// Aplica busca local na solucao construida
		busca_local_melhor_aprimorante(n, sl, p, w, b);
		// Atualiza melhor solucao
		if (calcula_fo(sl, n, p, w, b) > fo_star) {

			// copia em s a melhor solucao
			for (int i = 0; i < n; i++) s[i] = sl[i];
			
			// atualiza fo
			fo_star = calcula_fo(sl,n,p,w,b);
		}
	}

	// printf("Solucao: %lf\n", calcula_fo(s, n, p, w, b));
	fprintf(fp, ",%lf", fo_star);
}

int dist_simetrica(int *x_inicial, int *x_objetivo, int n) {
	int dist = 0;
	
	for (int i = 0; i < n; i++) {
		if (x_inicial[i] != x_objetivo[i]) {
			dist += 1;
		}
	}

	return dist;
}

int calc_pos(int *x, int *xt, int n, int last_index) {
	
	int i = last_index;

	for (i = 0; i < n; i++) {
		if (x[i] != xt[i]) {			
			last_index = i;
			return i;
		}
	}

	return -1;
}

void imprime_caminho(int *x, int *xt, int n) {
	printf("aplica mov:");
	for (int i = 0; i < n; i++)
		printf(" %d", x[i]);
	printf(" -> ");
	printf("objetivo:");
	for (int i = 0; i < n; i++)
		printf(" %d", xt[i]);
	printf("\n");
}

using namespace std;
void path_relinking(int *xs, int *xt, int n, double *p, double *w, double b) {

	int fo_min, pos = 0, last_index = -1;
	int *x_fo_min;
	int *x;

	x_fo_min = (int *)malloc(n * sizeof(int));
	x = (int *)malloc(n * sizeof(int));

	//Reconexão por caminhos regressiva
	fo_min = min(calcula_fo(xs, n, p, w, b), calcula_fo(xt, n, p, w, b));
	if (calcula_fo(xs, n, p, w, b) == fo_min) { 
	 	for (int i = 0; i < n; i++)
	 		x_fo_min[i] = xs[i];
	 }else {
	 	for (int i = 0; i < n; i++)
			x_fo_min[i] = xt[i];
	 }

	// copia xs para x
	for (int j = 0; j < n; j++)
		x[j] = xs[j];

	// last_index = dist_simetrica(x, xt, n);
	while (dist_simetrica(x, xt, n) != 0) {
		
		last_index += 1;
		troca_bit(x, last_index = calc_pos(x, xt, n, last_index));

		// imprime_caminho(x, xt, n);
		if (calcula_fo(x, n, p, w, b) > fo_min)	{
			fo_min = calcula_fo(x, n, p, w, b);
			for (int i = 0; i < n; i++) x_fo_min[i] = x[i];
		}
	}
	for (int i = 0; i < n; i++) xs[i] = x_fo_min[i]; //atualiza solução aprimorante xs
}

Boolean esta_na_lista(Arraylist lista_elite, int *sl, int n) {
	int dif = 0;

	for (int k = 0; k < arraylist_size(lista_elite); k++) {
		for (int i = 0; i < n; i++) { 
			if ( ((int *)arraylist_get(lista_elite, k))[i] == sl[i] ) {
				dif += 1;
			}
		}
		if (dif == n) {
			return true;
		}
		else {
			dif = 0;
		}
	}
	return false;
}

void add_lista_elite(Arraylist lista_elite, int *sl, int n, double *p, double *w, double b) {
	int *aux, pior_index;
	double pior_fo = DBL_MAX;

	//auxiliar para add solução elite
	aux = (int *)malloc(n * sizeof(int));
		
	for (int j = 0; j < n; j++)
		aux[j] = sl[j];

	if (arraylist_size(lista_elite) < 10) {
		
		if(!esta_na_lista(lista_elite, sl, n)) {
			arraylist_add(lista_elite, aux);
		}
		
	}
	else if (!esta_na_lista(lista_elite, sl, n)) {
		
		for (int k = 0; k < arraylist_size(lista_elite); k++) {
			if (calcula_fo((int *)arraylist_get(lista_elite, k), n, p, w, b) < pior_fo) {
				pior_fo = calcula_fo((int *)arraylist_get(lista_elite, k), n, p, w, b);
				pior_index = k;
			}
		}
		
		if (pior_fo < calcula_fo(sl, n, p, w, b)) {
			arraylist_remove_index(lista_elite, pior_index);
			arraylist_add(lista_elite, aux);
		}
	}
}

/*
void pos_otimizacao(Arraylist lista_elite, int n, int *s, double *p, double *w, double b) {
	for (int i = 0; i < arraylist_size(lista_elite); i++) {
		for (int j = i + 1; j < arraylist_size(lista_elite); j++) {
			// printf("%d: %lf até %d: %lf \n",i, calcula_fo((int *)arraylist_get(lista_elite, i), n, p, w, b),j, calcula_fo((int *)arraylist_get(lista_elite, j), n, p, w, b));
			path_relinking((int *)arraylist_get(lista_elite, i), (int *)arraylist_get(lista_elite, j), n, p, w, b);
			add_lista_elite(lista_elite, (int *)arraylist_get(lista_elite, i), n, p, w, b);
			if (calcula_fo((int *)arraylist_get(lista_elite, i), n, p, w, b) > calcula_fo(s, n, p, w, b) ) {
				for (int k = 0; k < n; k++){
					s[k] = ((int *)arraylist_get(lista_elite, i))[k];
				}
			}
		}
 	}
} */

/* aplica metaheuristica GRASP COM PR */
void grasp_pr(int n, int *s, double *p, double *w, double b, int iter_max, double alfa, FILE* fp) {
	
	int *sl;
	double fo_star = -DBL_MAX, melhor_fo = -DBL_MAX;
	Arraylist lista_elite;
	lista_elite = arraylist_create(obj_equals);
	
	// cria solucao auxiliar
	sl = (int *)malloc(n * sizeof(int));

	// Enquanto melhoria
	for (int i = 0; i < iter_max; i++)	{
		
		// Constroi solucao parcialmente gulosa
		constroi_solucao_grasp(n, sl, p, w, b, alfa);
		
		// Aplica busca local na solucao construida
		busca_local_melhor_aprimorante(n, sl, p, w, b);

		if (i > 0) {
			for (int k_sol = 0; k_sol < arraylist_size(lista_elite); k_sol++) {
				
				path_relinking(sl, (int *)arraylist_get(lista_elite, k_sol), n, p, w, b);
				
				if (calcula_fo(sl, n, p, w, b) > fo_star) {
				 	for (int i = 0; i < n; i++) s[i] = sl[i];
				 	fo_star = calcula_fo(s, n, p, w, b);
				}
			}
		}
		add_lista_elite(lista_elite, sl, n, p, w, b);
	}
	
	// printf("Solucao: %lf\n", fo_star);
	fprintf(fp, "%lf,", fo_star);
}
