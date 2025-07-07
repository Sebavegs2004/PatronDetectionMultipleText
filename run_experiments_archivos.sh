#!/bin/bash


echo "corto"
# Imprimimos una cabecera para nuestro archivo CSV
echo "ejecutable;tamañoPatron;tiempo"

for (( c=1; c<=20; c++ ))
do
    ./patternsearch DNA 1 patrones_chico_100.txt
done

for (( c=1; c<=20; c++ ))
do
    ./patternsearch DNA 1 patrones_chico_200.txt
done

for (( c=1; c<=20; c++ ))
do
    ./patternsearch DNA 1 patrones_chico_300.txt
done

for (( c=1; c<=20; c++ ))
do
    ./patternsearch DNA 1 patrones_chico_500.txt
done

for (( c=1; c<=20; c++ ))
do
    ./patternsearch DNA 1 patrones_chico_1000.txt
done

for (( c=1; c<=20; c++ ))
do
    ./patternsearch DNA 1 patrones_chico_2000.txt
done


echo "largo"




for (( c=1; c<=20; c++ ))
do
    ./patternsearch DNA 1 patrones_grande_100.txt
done

for (( c=1; c<=20; c++ ))
do
    ./patternsearch DNA 1 patrones_grande_200.txt
done

for (( c=1; c<=20; c++ ))
do
    ./patternsearch DNA 1 patrones_grande_300.txt
done

for (( c=1; c<=20; c++ ))
do
    ./patternsearch DNA 1 patrones_grande_500.txt
done

for (( c=1; c<=20; c++ ))
do
    ./patternsearch DNA 1 patrones_grande_1000.txt
done

for (( c=1; c<=20; c++ ))
do
    ./patternsearch DNA 1 patrones_grande_2000.txt
done

