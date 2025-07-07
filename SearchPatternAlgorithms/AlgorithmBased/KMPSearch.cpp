// Codigo extraido de https://www.geeksforgeeks.org/dsa/kmp-algorithm-for-pattern-searching/
#include "../../searchpattern_lib.h"
#include <iostream>
#include <string>
#include <vector>

#include <sys/resource.h>


// Funcion que construye el arreglo LPS (Longest Prefix Suffix)
// El arreglo LPS indica el largo del prefijo mas largo que tambien es sufijo
// para cada posición del patrón, lo que permite saltar comparaciones innecesarias
void constructLps(std::string &pat, std::vector<int> &lps) {

    int len = 0; // longitud del prefijo mas largo que tambien es sufijo para el indice previo
    lps[0] = 0; // El primer valor de LPS siempre es 0

    int i = 1;
    while (i < pat.length()) {
        // Si los caracteres coinciden, aumentamos la longitud de len
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else {
            // Si no coinciden y len no es cero, retrocedemos a la posición anterior del lps
            if (len != 0) {
                len = lps[len - 1];
            }
            else {
                // Si no hay coincidencias previas, establecemos lps[i] a 0
                lps[i] = 0;
                i++;
            }
        }
    }
}


// Función que ejecuta el algoritmo de búsqueda KMP
// txt: texto completo concatenado
// pat: patrón a buscar

int kmpSearch(std::string txt, std::string pat) {
    int n = txt.length(); // longitud del texto
    int m = pat.length(); // longitud del patron
    int count = 0;        // contador de apariciones del patrón

    std::vector<int> lps(m); // arreglo LPS del patrón


    constructLps(pat, lps); // construimos el arreglo LPS
    std::cout<<"lps.size"<<lps.size()<<" sizeofint: "<<sizeof(int)<<std::endl;
    std::cout<<"Bytes usados por vector :"<< lps.size() * sizeof(int)<<std::endl;

    // Punteros i y j para recorrer el texto y el patrón
    int i = 0;
    int j = 0;

    while (i < n) {
        // Si los caracteres coinciden, avanzamos ambos punteros
        if (txt[i] == pat[j]) {
            i++;
            j++;

            // Si se encontró una coincidencia completa del patrón
            if (j == m) {
                count++; // aumentamos el contador de apariciones

                // Utilizamos el valor LPS para saltar comparaciones innecesarias
                j = lps[j - 1];
            }
        }

        // Si hay una falla en la coincidencia
        else {
            // Usamos el LPS para evitar repetir comparaciones
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
    return count; // devolvemos el numero total de apariciones del patron
}
