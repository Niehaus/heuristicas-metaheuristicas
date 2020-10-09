
## Questão 1 - Explique e exemplifique o que é ótimo local, ótimo global e sensibilidade à solução inicial em uma busca local

Ótimo local é uma solução no espaço de busca a qual não possui nenhum vizinho que melhora a função objetivo, não sendo necessariamente a melhor solução da instância do problema, mas pode acontecer. Já o ótimo global é a melhor solução no espaço de busca da instância. E a sensibilidade na busca local é o fato da solução poder variar conforme a entrada escolhida para o problema, ou seja, ela é afetada pela solução inicial na instância. 


Na imagem a seguir é possível visualizar exemplos ótimos locais das vizinhanças em amarelo, e a vizinhança que possui o ótimo global está com o valor deste ótimo marcado em vermelho, também é possível verificar a sensibilidade na busca local, pois tendo como solução inicial um vizinho qualquer é possível encontrar um ótimo local e este ótimo local pode não ser o ótimo global, por exemplo, começando a partir do vizinho 01423 é possível encontrar o ótimo local de valor 153, dependendo da busca local aplicada, como por exemplo o primeiro aprimorante, esta pode ser a solução do algoritmo, mas caso este tivesse começado pelo vizinho 01243, a solução encontrada por acaso teria sido o ótimo global, sendo assim sensível à escolha da solução inicial. 

![alt text](https://raw.githubusercontent.com/Niehaus/heuristicas-metaheuristicas/master/Atividade-Avaliativa2/Screenshot_2020-10-09%20aula5%20pptx%20-%20aula5%20pdf.png)

## Questão 2 - O  problema  do  empacotamento  (Bin  Packing  Problem-BPP) consiste  em  empacotar  um conjunto  de nobjetos  de  diferentes  tamanhos  em  recipientes  ou  caixas  de  tamanho  fixo V, minimizando o número de caixas utilizadas.

### a) Desenvolva uma representação para o problema:

Uma representação seria um vetor S, sendo Si = 1 se o pacote i foi usado e uma matriz X, para guardar qual item j foi guardado no pacote i sendo j, fazendo Xij = 1, 
caso não haja pacote Xij = 0.

### b) Proponha  uma fórmula para  o  cálculo  da  função  objetivo  do  problema,  com  uso  de penalização se necessário.

Dado um conjunto de pacotes S, cada um de mesma capacidade C, e uma lista de n itens de tamanhos t1,...,tn a serem empacotados, deve-se se encontrar P pacotes tal que ![alt text](https://raw.githubusercontent.com/Niehaus/heuristicas-metaheuristicas/master/Atividade-Avaliativa2/math-20201009(1).png). 

Sendo assim uma possível fórmula para cálculo da função objetivo é: 


![alt text](https://raw.githubusercontent.com/Niehaus/heuristicas-metaheuristicas/master/Atividade-Avaliativa2/math-20201009(2).png)

### c) Proponha uma heurística construtiva para o problema:
Uma heurística construtiva para o problema pode ser:  
- Ordena-se os objetos em ordem de tamanho de forma decrescente, realiza uma iteração sobre os objetos, inserindo-os no primeiro pacote em que este objeto couber, caso contrário, cria-se um novo pacote e aloca este objeto no novo pacote até que todos os objetos tenham sido alocados. 


### d) Proponha  duas  estruturas  de  vizinhança  para  o  problema. Explique  em  detalhes  o movimento  a  ser  aplicado em uma solução  para  geração  das  soluções  vizinhas.  Explique  a complexidade dasvizinhanças propostas:
  
#### Estrutura de vizinhança 1:
Nesta vizinhança o movimento a ser aplicado consiste em trocar o um item aleatorio para outro pacote diferente do que ele já está e sorteado aleatoriamente. Exemplo: Para 4 caixas com capacidade C = 5, um vetor S = [1, 0, 1, 1], deseja-se alocar 5 itens de tamanho t = 2 cada, de modo que uma solução inicial seria:

| X | 1 | 2 | 3 | 4 |
|--|--|--|--|--|
| 1 | 1 | 0 | 0 | 0 |
| 2 | 0 | 0 | 1 | 0 |
| 3 | 0 | 0 | 0 | 1 |
| 4 | 0 | 0 | 1 | 0 |
| 5 | 1 | 0 | 0 | 0 |

e aplicação de um movimento tendo sorteado o item 1 para inserir  no pacote 4 resultaria no vizinho:
| X | 1 | 2 | 3 | 4 |
|--|--|--|--|--|
| 1 | 0 | 0 | 0 | 1 |
| 2 | 0 | 0 | 1 | 0 |
| 3 | 0 | 0 | 0 | 1 |
| 4 | 0 | 0 | 1 | 0 |
| 5 | 1 | 0 | 0 | 0 |
	  
  Dessa forma, foi retirado o primeiro item do pacote 1 e colocado no pacote 4. A ordem de complexidade dessa vizinhança é: O(n * número de caixas usadas).
#### Estrutura de vizinhança 2: 
Nesta vizinhança o movimento a ser aplicado seria sortear dois pacotes diferentes aleatoriamente e trocá-los de pacote. Sendo que o primeiro irá para o pacote do segundo, e do contrário também.

Exemplo: Para 4 caixas com capacidade C = 5, um vetor S = [1, 0, 1, 1], deseja-se alocar 5 itens de tamanho t = 2 cada, de modo que uma solução inicial seria:

| X | 1 | 2 | 3 | 4 |
|--|--|--|--|--|
| 1 | 1 | 0 | 0 | 0 |
| 2 | 0 | 0 | 1 | 0 |
| 3 | 0 | 0 | 0 | 1 |
| 4 | 0 | 0 | 1 | 0 |
| 5 | 1 | 0 | 0 | 0 |

e aplicação de um movimento tendo sorteado o item 1 e o item 3:
| X | 1 | 2 | 3 | 4 |
|--|--|--|--|--|
| 1 | 0 | 0 | 0 | 1 |
| 2 | 0 | 0 | 1 | 0 |
| 3 | 1 | 0 | 0 | 0 |
| 4 | 0 | 0 | 1 | 0 |
| 5 | 1 | 0 | 0 | 0 |
   
Dessa forma, o item 1 foi para o pacote número 4, onde estava o pacote 3 anteriormente, e este foi para o pacote 1, onde o item 1 estava anteriormente. A ordem de complexidade desta vizinhança é O(n * (n - 1)/2). 
