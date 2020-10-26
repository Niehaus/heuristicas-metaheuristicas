# Adaptação Grasp com Path Relinking 

Para rodar este trabalho basta utilizar `./runme.sh`, talvez seja necessário conceder a ele permissão atráves do comando `chmod +x ./runme.sh`. Ele irá gerar resultados para 3 conjuntos de instâncias disponíveis no link http://artemisa.unicauca.edu.co/~johnyortega/instances_01_KP/ para `Large scale 0/1 knapsack problems`

## Questão 1
### Forma de integração
 Como etapa de pós-otimização entre pares de soluções elite
 Como etapa de intensificação entre um ótimo local e uma solução elite
### Conjunto Elite
 - Tamanho fixo: 10
 - Critério de entrada de uma solução no conjunto: Desde que seja uma solução aprimorante ela deve entrar no conjunto
 - Critério de saída de uma solução do conjunto: Pior solução do conjunto já existente sairá da lista para que outro candidato entre.
### Direção
- Regressiva: Tendo em vista que é uma função de maximização - do pior para o melhor - é escolhida a menor FO dentre os dois caminhos inicial e final que entram no PR
 
### Características escolhidas para o GRASP nas duas abordagens
 - Valor de alfa: 0.7
 - LRC por cardinalidade ou valor: Valor
 - Algoritmo de Busca Local usado:  Melhor aprimorante

## Questão 2

### Primeiro Conjunto de Instancias: Uncorrelated data instances
![](https://raw.githubusercontent.com/Niehaus/heuristicas-metaheuristicas/master/AA3/pyplots/conjunto1/plot_media.png)
![](https://raw.githubusercontent.com/Niehaus/heuristicas-metaheuristicas/master/AA3/pyplots/conjunto1/plot_time.png)
### Segundo Conjunto de Instancias: Weakly correlated instances
![](https://raw.githubusercontent.com/Niehaus/heuristicas-metaheuristicas/master/AA3/pyplots/conjunto2/plot_media02.png)
![](https://raw.githubusercontent.com/Niehaus/heuristicas-metaheuristicas/master/AA3/pyplots/conjunto2/plot_time02.png)
### Terceiro Conjunto de Instancias: Strongly correlated instances
![](https://raw.githubusercontent.com/Niehaus/heuristicas-metaheuristicas/master/AA3/pyplots/conjunto3/plot_media03.png)
![](https://raw.githubusercontent.com/Niehaus/heuristicas-metaheuristicas/master/AA3/pyplots/conjunto3/plot_time03.png)
