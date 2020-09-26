# Atividade Avaliativa Nº 1

Nome: Bárbara Belize Moreira Boechat 
## Questão 1
  ### Letra A) 
  Um vetor solução s de tamanho n, sendo n o número de vértices, sendo as cidades numeradas de 1 a n. Para assim, armazenar a rota solução que o algoritmo deve gerar, o retorno à origem é subentendido.  
  
  ### Letra B)
  
    
 ### Letra C)
  - Forma-se um vetor de cidades e o ordena de a 1 n, inicia o algoritmo a partir do primeiro item do vetor;
  - Utiliza o vizinho mais próximo para determinar o ciclo, porém para garantir que a rota de um ciclo será quebrada, deve-se somar um valor AMAX às arestas que não pertencerem ao mesmo grupo, este valor pode ser estipulado com base nos pesos das arestas da instância, usando por exemplo a maior aresta de todo o grafo;
  - Após formar o ciclo, o calculo da Fo deve ser feito pelo caminho contrário, ou seja, pela subtração do valor AMAX aos ij não pertencentes ao mesmo grupo.

## Questão 2
O algoritmo poderá incluir itens na mochila de forma linear, ou seja, seguindo item a item do vetor de profit dado pela razão ui/wi. Já que segundo a característica de ordenção dada na questão, uma busca linear até completar a capacidade W já garante o resultado ótimo, pois quanto mais se avança na lista, maiores são os pesos e menores as utilidades de cada item. 

