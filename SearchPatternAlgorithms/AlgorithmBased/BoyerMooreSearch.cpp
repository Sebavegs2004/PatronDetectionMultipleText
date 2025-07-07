#include <string>
#include <iostream>
#define NO_OF_CHARS 256  // Cantidad de caracteres posibles (tabla ASCII extendida)

// Función de preprocesamiento para la heurística del "carácter malo" (bad character)
// Esta función construye un arreglo donde para cada carácter se guarda su última
// posición en el patrón (si aparece), o -1 si no aparece.
void badCharHeuristic(std::string &str, int size, int badchar[NO_OF_CHARS]) {
    // Inicializar todas las posiciones con -1
    std::fill(badchar, badchar + NO_OF_CHARS, -1);

    // Para cada carácter del patrón, actualizar su última posición (más a la derecha)
    for (int i = 0; i < size; i++)
        badchar[(unsigned char)str[i]] = i;
}

// Función principal del algoritmo Boyer-Moore usando la heurística del carácter malo
// Devuelve la cantidad de veces que el patrón aparece en el texto
int boyermooreSearch(std::string txt, std::string pat) {
    int m = pat.size();  // Largo del patrón
    int n = txt.size();  // Largo del texto
    int occur = 0;       // Contador de ocurrencias encontradas

    int badchar[NO_OF_CHARS];  // Arreglo para la heurística del carácter malo
    badCharHeuristic(pat, m, badchar);  // Preprocesar el patrón

    int s = 0;  // s es el desplazamiento del patrón con respecto al texto
    while (s <= n - m) {
        int j = m - 1;

        // Comparar el patrón desde el final hacia el inicio
        while (j >= 0 && pat[j] == txt[s + j])
            j--;

        if (j < 0) {
            // Si j < 0, entonces se encontró una ocurrencia completa
            occur++;

            // Avanzar el patrón a la siguiente posible posición
            // Esto permite encontrar patrones superpuestos
            s += (s + m < n) ? m - badchar[(unsigned char)txt[s + m]] : 1;
        } else {
            // Calcular cuánto desplazar el patrón según el carácter malo
            // Se asegura de avanzar al menos una posición
            s += std::max(1, j - badchar[(unsigned char)txt[s + j]]);
        }
    }

    return occur;  // Retornar cantidad total de ocurrencias encontradas
}
