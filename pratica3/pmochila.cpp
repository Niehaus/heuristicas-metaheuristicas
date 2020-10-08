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
			case 2: /* Busca Local */
				switch (menu_busca_local()) {
					case 1: /* Primeiro aprimorante */
						busca_local_primeiro_aprimorante(n,s,p,w,b);
						printf("Solucao refinada pela busca local do Primeiro Aprimorante:\n");
						imprime_solucao(s,n,p,w,b);
						break;
					case 2: /* Melhor aprimorante */
						busca_local_melhor_aprimorante(n,s,p,w,b);
						printf("Solucao refinada pela busca local do Melhor Aprimorante:\n");
						imprime_solucao(s,n,p,w,b);
						break;
					case 3: /* Randomica */
						busca_local_randomica(n,s,p,w,b,10);
						printf("Solucao refinada pela busca local Randomica:\n");
						imprime_solucao(s,n,p,w,b);
						break;
					default:
						break;
				}
				break;
			case 3: /* Metaheuristicas */
				switch (menu_metaheuristicas()) {
					case 1: /* VND */
						VND(n,s,p,w,b);
						printf("Solucao do VND:\n");
						imprime_solucao(s,n,p,w,b);
						break;
					case 2: /* VNS */
						VNS(n,s,p,w,b, 100);
						printf("Solucao do VNS:\n");
						imprime_solucao(s,n,p,w,b);
						break;
					default:
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

/* aplica busca local pela estrategia do melhor aprimorante */
void melhor_vizinho_N1(int n, int *s, double *p, double *w, double b) {
    double fo_original;
    double fo_max;
    double fo_vizinho;
    int melhor_bit;


	 	fo_original = calcula_fo(s, n, p, w, b);
	
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
            fo_original = fo_max;
			printf("Vizinho melhor! FO = %lf\n", fo_max);
		}
}

/* aplica busca local pela estrategia do melhor aprimorante */
void melhor_vizinho_N2(int n, int *s, double *p, double *w, double b) {
    double fo_max, fo_vizinho, fo_original;
    int melhor_bit_1, melhor_bit_2;
		
		fo_original = calcula_fo(s, n, p, w, b);

		fo_max = -DBL_MAX;
		
		for (int j = 0; j < n; j++) {
			
        	troca_bit(s, j);

			for (int i = j + 1; i < n; i++) {

				troca_bit(s , i);

            	fo_vizinho = calcula_fo(s,n,p,w,b);
	
				// armazena melhor vizinho
				if (fo_vizinho > fo_max) {
					melhor_bit_1 = j;
					melhor_bit_2 = i;
                	fo_max = fo_vizinho;
           		}
			
				// volta a solucao inicial
				troca_bit(s, i);			
			}

			 // volta a solucao inicial
        		troca_bit(s, j);
		}

		// se encontrou algum vizinho melhor
		if (fo_max > fo_original) {
			troca_bit(s, melhor_bit_1);
			troca_bit(s, melhor_bit_2);
			printf("Vizinho melhor em N1! FO = %lf\n", fo_max);
		}
	
}

void vizqqN1(int n, int *s, double *p, double *w, double b) {
	troca_bit(s,((float)rand()/RAND_MAX) * n);	
    printf("Vizinho qq N1 - FO = %lf\n", calcula_fo(s, n, p, w, b));
}

void vizqqN2(int n, int *s, double *p, double *w, double b) {
    
	int pos1, pos2;

	pos1 = ((float)rand()/RAND_MAX) * n;
	pos2 = ((float)rand()/RAND_MAX) * n;
	while (pos1 == pos2) {
		pos2 = ((float)rand()/RAND_MAX) * n;
	}
	
    printf("Vizinho qq N2 - FO = %lf\n", calcula_fo(s, n, p, w, b));
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

// Menu de busca local
int menu_busca_local(void)
{
	int escolha;
	
	do {
		printf("\nBUSCA LOCAL: \n");
		printf("                  1. Primeiro Aprimorante \n");
		printf("                  2. Melhor Aprimorante\n");
		printf("                  3. Randomica\n");
		printf("                  escolha: ");
		if (!scanf("%d",&escolha)) printf("Falha na leitura!\n");
	} while (escolha < 1 || escolha > 3);
	return escolha;
}

// Menu de metaheuristicas
int menu_metaheuristicas(void)
{
	int escolha;
	
	do {
		printf("\nMETAHEURISTICAS: \n");
		printf("                  1. VND \n");
		printf("                  2. VNS\n");
		printf("                  escolha: ");
		if (!scanf("%d",&escolha)) printf("Falha na leitura!\n");
	} while (escolha < 1 || escolha > 2);
	return escolha;
}

/******************************************************************************************/
/*				CONSTRUTIVOS						  */
/******************************************************************************************/

// Constroi uma solucao inicial
void constroi_solucao(int n, int *s, double *p, double *w, double b, double percentual)
{
	double peso = 0;
	double capacidade = 0;
	int j, tamRestrito;
	Objeto *o;
	
	// Limpa solucao
	for (int j=0; j<n; j++) s[j] = 0;
	
	// Cria lista de objetos ordenados
	Arraylist objetosOrd = cria_lista_objetos_ordenada(n,s,p,w);
	imprime_lista(objetosOrd);

	printf("C: %lf\n", b);
	
	// Constroi solucao elemento a elemento, verificando se cada objeto cabe na capacidade residual da mochila
	while (arraylist_size(objetosOrd) > 0 && peso < b) {
		
		
		// Define o tamanho da lista restrita, ou seja, o percentual mais interessantes
		tamRestrito = percentual * arraylist_size(objetosOrd);
		
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

// Constroi uma solucao inicial aleatoria
void constroi_solucao_aleatoria(int n, int *s, double *p, double *w, double b)
{	
	// Limpa solucao
	for (int j=0; j<n; j++) s[j] = 0;
	
	// Insere objetos aleatoriamente
	for (int j=0; j<n; j++) s[j] = ((float)rand()/RAND_MAX) * 2;
	
}

/******************************************************************************************/
/*				BUSCA LOCAL						  */
/******************************************************************************************/

/* aplica busca local pela estrategia do primeiro aprimorante */
void busca_local_primeiro_aprimorante(int n, int *s, double *p, double *w, double b)
{
	int melhoria = 1;
	double fo_original;
    double fo_vizinho;
    
    fo_original = calcula_fo(s, n, p, w, b);
	
	// Enquanto melhoria
	while (melhoria) {
		melhoria = 0;
				
		for (int j = 0; j < n; j++) {
			
			// cria vizinho
			troca_bit(s, j);
            
            fo_vizinho = calcula_fo(s,n,p,w,b);
			
			// se vizinho > melhor, migra para ele
			if (fo_vizinho > fo_original) {
				melhoria = 1;
                fo_original = fo_vizinho;
				printf("Vizinho melhor! FO = %lf\n", calcula_fo(s,n,p,w,b));
				break;
			}
			else {
				troca_bit(s,j);
			}
		}
	}	
}

/* aplica busca local pela estrategia do melhor aprimorante */
void busca_local_melhor_aprimorante(int n, int *s, double *p, double *w, double b)
{

	printf("\n\n***************** VIZINHANCA N1 *****************\n\n");

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

/* aplica busca local pela estrategia randomica */
void busca_local_randomica(int n, int *s, double *p, double *w, double b, int iter_max)
{
	int pos;
	double fo_original, fo_vizinho;
	int iter = 0;
    
    fo_original = calcula_fo(s, n, p, w, b);
	
	while (iter < iter_max) {
		
		// incrementa numero de iteracoes
		iter = iter + 1;
		
		// gera vizinho aleatorio
		pos = ((float)rand()/RAND_MAX) * n;
		troca_bit(s,pos);
		
        	// calcula fo vizinho
        	fo_vizinho = calcula_fo(s,n,p,w,b);

		// se vizinho e melhor
		if (fo_vizinho > fo_original) {
			// zera o contador de iteracoes
			iter = 0;
            		fo_original = fo_vizinho;
			printf("Vizinho melhor! FO = %lf\n", fo_vizinho);
		}
		else {
			troca_bit(s,pos);
		}
	}
}

/******************************************************************************************/
/*				METAHEURISTICAS						  */
/******************************************************************************************/

/* aplica metaheuristica VND */
void VND(int n, int *s, double *p, double *w, double b) {
	
	double fo_s;
	int k;
	
	k = 1;

	while (k <= 2)	{
		fo_s = calcula_fo(s, n, p , w, b);

		switch(k) {
			case 1: 
				melhor_vizinho_N1(n, s, p, w, b);
				break;
			case 2: 
				melhor_vizinho_N2(n, s, p, w, b);
				break;
			default:
				break;
		}

		if (calcula_fo(s, n, p, w, b) > fo_s) {
		k = 1;
		}else {
			k++;
		}
	}
}

/* aplica metaheuristica VNS */
void VNS(int n, int *s, double *p, double *w, double b, int iter_max) {
	int iter = 0, k;
	double fo_original;
	int *sl = (int *)malloc(n * sizeof(int));

	fo_original = calcula_fo(s, n , p, w, b);

	while (iter < iter_max)	{
		k = 1;
		while (k <= 2) {
			for (int i = 0; i < n; i++) sl[i] = s[i];
			switch (k) {
			case 1:
				vizqqN1(n , sl, p, w, b);
				break;
			case 2: 
				vizqqN2(n, sl, p, w, b);
				break;
			default:
				break;
			}

			busca_local_melhor_aprimorante(n, sl, p, w, b);

			if (calcula_fo(sl, n, p, w, b) > fo_original) {
				for (int i = 0; i < n; i++) s[i] = sl[i];
				fo_original = calcula_fo(sl, n, p, w, b);
				iter = 0;
				k = 1;
			}else{
				k++;
			}
			
		}
		iter++;
	}
}