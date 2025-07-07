#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

// Construye el suffix array de un texto usando el algoritmo de duplicación de longitud (prefix doubling)
// Complejidad: O(n log n)
std::vector<int> buildSuffArr(std::string text) {
    int n = text.size();
    int classes = 256; // Número máximo de caracteres posibles (ASCII)
    
    std::vector<int> sa(n), c(n); // sa: suffix array, c: clases de equivalencia
    std::vector<int> cnt(std::max(classes, n), 0), sa2(n); // cnt: conteo para counting sort, sa2: array auxiliar

    // Paso 0: contar frecuencia de cada carácter
    for (int i = 0; i < n; i++) 
        cnt[(unsigned char)text[i]]++;
    
    // Suma acumulada para ordenar por los caracteres
    for (int i = 1; i < classes; i++) 
        cnt[i] += cnt[i - 1];
    
    // Primera ordenación: por el primer carácter (sufijos de longitud 1)
    for (int i = 0; i < n; i++) 
        sa[--cnt[(unsigned char)text[i]]] = i;

    // Asignar clases de equivalencia iniciales (caracteres únicos)
    c[sa[0]] = 0;
    int num_classes = 1;
    for (int i = 1; i < n; i++) {
        if ((unsigned char)text[sa[i]] != (unsigned char)text[sa[i - 1]])
            num_classes++;
        c[sa[i]] = num_classes - 1;
    }

    std::vector<int> c2(n); // Array auxiliar para nuevas clases

    // Duplicar la longitud del prefijo considerado en cada iteración: k = 2^h
    for (int h = 0; (1 << h) < n; ++h) {
        int k = 1 << h;

        // Paso 1: rotar cada sufijo k posiciones hacia atrás
        for (int i = 0; i < n; i++) {
            sa2[i] = sa[i] - k;
            if (sa2[i] < 0) sa2[i] += n;
        }

        // Paso 2: counting sort usando la primera clave (clase de equivalencia)
        std::fill(cnt.begin(), cnt.begin() + num_classes, 0);
        for (int i = 0; i < n; i++) 
            cnt[c[sa2[i]]]++;
        for (int i = 1; i < num_classes; i++) 
            cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i--) 
            sa[--cnt[c[sa2[i]]]] = sa2[i];

        // Paso 3: asignar nuevas clases de equivalencia
        c2[sa[0]] = 0;
        num_classes = 1;
        for (int i = 1; i < n; i++) {
            int mid1 = (sa[i] + k) % n;
            int mid2 = (sa[i - 1] + k) % n;

            if (c[sa[i]] != c[sa[i - 1]] || c[mid1] != c[mid2])
                num_classes++;
            c2[sa[i]] = num_classes - 1;
        }
        c.swap(c2); // Actualizar clases
    }

    return sa; // Devolver el suffix array construido
}

int suffixArraySearch( std::string text, std::string pattern, std::vector<int> sufArr){
    int n = text.length();
    int m = pattern.length();
    int left = 0, right = n;
    // Buscar el primer sufijo mayor o igual (lower bound)
    while (left < right) {
        int mid = (left + right) / 2;
        int cmp = text.compare(sufArr[mid], m, pattern);
        if (cmp < 0)
            left = mid + 1;
        else
            right = mid;
    }
    int first = left;

    left = 0, right = n;
    // Buscar el primer sufijo estrictamente mayor (upper bound)
    while (left < right) {
        int mid = (left + right) / 2;
        int cmp = text.compare(sufArr[mid], m, pattern);
        if (cmp <= 0)
            left = mid + 1;
        else
            right = mid;
    }
    int last = left;

    return last - first;
}

