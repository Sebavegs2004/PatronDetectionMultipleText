#!/bin/bash

# Imprimimos una cabecera para nuestro archivo CSV
echo "ejecutable;tamañoPatron;tiempo"

for (( c=1; c<=20; c++ ))
do
    ./patternsearch DNA 1 patrones_inexistentes_100.txt
done

for (( c=1; c<=20; c++ ))
do
    ./patternsearch DNA 1 patrones_inexistentes_200.txt
done

for (( c=1; c<=20; c++ ))
do
    ./patternsearch DNA 1 patrones_inexistentes_300.txt
done

for (( c=1; c<=20; c++ ))
do
    ./patternsearch DNA 1 patrones_inexistentes_500.txt
done

for (( c=1; c<=20; c++ ))
do
    ./patternsearch DNA 1 patrones_inexistentes_1000.txt
done

for (( c=1; c<=20; c++ ))
do
    ./patternsearch DNA 1 patrones_inexistentes_2000.txt
done
