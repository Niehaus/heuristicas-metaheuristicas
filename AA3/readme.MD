# Adaptação Grasp com Path Relinking 

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
 Valor de alfa: 0.7
 LRC por cardinalidade ou valor: Valor
 Algoritmo de Busca Local usado:  Melhor aprimorante

## Questão 2

### Primeiro Conjunto de Instancias: Uncorrelated data instances

### Segundo Conjunto de Instancias: Weakly correlated instances

### Terceiro Conjunto de Instancias: Strongly correlated instances