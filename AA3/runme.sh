#!/bin/bash

# Barbara - Out 2020

echo "Compilando Programa"
echo "$(g++ arraylist.cc pmochila-barbara.cpp -o main)"
echo "Ok.."
cat arguments.txt | while read line 
do
    echo "$line"
	n=1 #executa cada entrada 10x
	while [ $n -le 5 ]
	do
        echo "$($line)"
		n=$(( n+1 )) #incrementa n
	done
done