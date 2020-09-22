#include "pmochila.h"

/******************************************************************************************/
/*										MAIN											  */
/******************************************************************************************/
int main(int argc, char **argv)
{
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
	
	do {
		choice = menu_principal();
		switch (choice) {
			case 1: /* Geracao de uma solucao inicial */
				switch(menu_construtivo()) {
					case 1: /* Geracao gulosa de uma solucao inicial */
						constroi_solucao(n,s,p,w,b,0);
						printf("Solucao construida de forma gulosa:\n");
						imprime_solucao(s,n,p,w,b);
						break;
					case 2: /* Geracao parcialmente gulosa de uma solucao inicial */
						constroi_solucao(n,s,p,w,b,0.50);
						printf("Solucao construida de forma parcialmente gulosa:\n");
						imprime_solucao(s,n,p,w,b);
						break;
					case 3: /* Geracao aleatoria de uma solucao inicial viavel */
						constroi_solucao(n,s,p,w,b,1);
						printf("Solucao viavel construida de forma aleatoria:\n");
						imprime_solucao(s,n,p,w,b);
						break;
					case 4: /* Geracao aleatoria de uma solucao inicial */
						constroi_solucao_aleatoria(n,s,p,w,b);
						printf("Solucao construida de forma aleatoria:\n");
						imprime_solucao(s,n,p,w,b);
						break;
				}
				break;
			default:
				break;
		}
	} while (choice != 0);
	
	// Libera memoria
	free(s);
	free(s_star);
	free(w);
	free(p);
	return 0;
	
}

/******************************************************************************************/
/*				MENUS							  */
/******************************************************************************************/

// Menu principal
int menu_principal(void)
{
	int escolha;
	
	do {
		printf("\n************************************************* \n");
		printf("         1. Gere solucao inicial \n");
		printf("         2. Busca Local \n");
		printf("         3. Metaheuristicas \n");
		printf("         0. Sair \n");
		printf("         Escolha: ");
		if (!scanf("%d",&escolha)) printf("Falha na leitura!\n");
	} while (escolha < 0 || escolha > 3);
	return escolha;
}

// Menu de geracao de uma solucao inicial
int menu_construtivo(void)
{
    int escolha;
    
    do {
        printf("\nGERACAO DA SOLUCAO INICIAL: \n");
        printf("                  1. Gulosa \n");
        printf("                  2. Parcialmente gulosa\n");
        printf("                  3. Aleatoria viavel\n");
        printf("                  4. Aleatoria\n");
        printf("                  escolha: ");
        if (!scanf("%d",&escolha)) printf("Falha na leitura!\n");
    } while (escolha < 1 || escolha > 4);
    return escolha;
}

/******************************************************************************************/
/*				UTIL							  */
/******************************************************************************************/

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
		//printf("[ID]\tUtilidade\tPeso\tProfit\n");
		size = arraylist_size(lista);
		for (int i = 0; i < size; i++)
		{
			o = (Objeto*)arraylist_get(lista, i);
			//printf("[%d]\t%lf\t%lf\t%lf\n", o->id, o->utilidade, o->peso, o->profit);
		}
		//printf("\n");
	}
}

/******************************************************************************************/
/*				CONSTRUTIVOS						  */
/******************************************************************************************/

// Constroi uma solucao inicial
void constroi_solucao(int n, int *s, double *p, double *w, double b, double percentual) {
	double peso = 0;
	double capacidade = 0;
	int j, tamRestrito;
	Objeto *o;

	//Limpa solução 
	for (int i = 0; i < n; i++)	s[i] = 0;

	// Cria lista de objetos ordenados
	Arraylist objtOrdenados = cria_lista_objetos_ordenada(n, s, p, w);
	//imprime_lista(objtOrdenados);

	printf("C: %lf\n", b);
	
	// Constroi solucao elemento a elemento, verificando se cada objeto cabe na capacidade residual da mochila
	while (arraylist_size(objtOrdenados) > 0 && peso < b) { //Enquanto houver objetos na lista, e peso for menor que a capacidade max
		
		// Define o tamanho da lista restrita, ou seja, o percentual mais interessantes
		tamRestrito = percentual * arraylist_size(objtOrdenados);
				
		// Sorteia posicao aleatoria da lista residual
		j = (int) ((float) rand()/RAND_MAX * tamRestrito);

		// Recupera objeto
		o = (Objeto*) arraylist_get(objtOrdenados, j);

		// Se objeto ainda nao esta na mochila e cabe nela, adiciona objeto a mochila
		if (s[o->id] !=  1 && peso + o->peso <= b) {
			s[o->id] = 1;
			peso += o->peso;
		}
		
		// Remove objeto da lista, pois ja foi testado
		arraylist_remove_index(objtOrdenados, j);
	}		
}

// Constroi uma solucao inicial aleatoria
void constroi_solucao_aleatoria(int n, int *s, double *p, double *w, double b)
{	
	// Limpa solucao
	for (int i = 0; i < n; i++)	s[i] = 0;
		
	// Insere objetos aleatoriamente
	for (int i = 0; i < n; i++)	s[i] = ((float) rand()/RAND_MAX * 2);

		
}
