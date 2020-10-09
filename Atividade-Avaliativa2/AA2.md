## Questão 1 - Explique e exemplifique o que é ótimo local, ótimo global e sensibilidade à solução inicial em uma busca local

Ótimo local é uma solução no espaço de busca a qual não possui nenhum vizinho que melhora a função objetivo, não sendo necessariamente a melhor solução da instância do problema, mas pode acontecer. Já o ótimo global é a melhor solução no espaço de busca da instância. E a sensibilidade na busca local é o fato da solução poder variar conforme a entrada escolhida para o problema, ou seja, ela é afetada pela solução inicial na instância. 


Na imagem a seguir é possível visualizar exemplos ótimos locais das vizinhanças em amarelo, e a vizinhança que possui o ótimo global está com o valor deste ótimo marcado em vermelho, também é possível verificar a sensibilidade na busca local, pois tendo como solução inicial um vizinho qualquer é possível encontrar um ótimo local e este ótimo local pode não ser o ótimo global, por exemplo, começando a partir do vizinho 01423 é possível encontrar o ótimo local de valor 153, dependendo da busca local aplicada, como por exemplo o primeiro aprimorante, esta pode ser a solução do algoritmo, mas caso este tivesse começado pelo vizinho 01243, a solução encontrada por acaso teria sido o ótimo global, sendo assim sensível à escolha da solução inicial. 

![alt text](https://raw.githubusercontent.com/Niehaus/heuristicas-metaheuristicas/master/Atividade-Avaliativa2/Screenshot_2020-10-09%20aula5%20pptx%20-%20aula5%20pdf.png)

## Questão 2 - O  problema  do  empacotamento  (Bin  Packing  Problem-BPP)consiste  em  empacotar  um conjunto  de nobjetos  de  diferentes  tamanhos  em  recipientes  ou  caixas  de  tamanho  fixo V, minimizando o número de caixas utilizadas.

### a) Desenvolva uma representação para o problema:


   
