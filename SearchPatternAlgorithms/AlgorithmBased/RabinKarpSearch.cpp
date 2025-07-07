#include "../../searchpattern_lib.h"
#include <iostream>
#include <vector>
// Rabin-Karp: busca un patrón en un texto usando hashing modular.
// Compara el hash del patrón con el de cada subcadena del texto, y solo si coinciden, verifica carácter por carácter.
// Usa una función de rolling hash para calcular eficientemente el hash de cada nueva ventana.
//hash(P) = (P₀·d^(M−1) + P₁·d^(M−2) + ... + Pₘ₋₁·d^0) mod q

int rabinkarpSearch(std::string txt, std::string pat, std::vector<size_t> offsets) {
    const int d = 256;     // Tamaño del alfabeto (ASCII)
    const int q = 101;     // Número primo para el hash
    const int M = pat.length();
    const int N = txt.length();

    int hash_patron = 0;
    int hash_ventana = 0;
    int h = 1;

    int total_ocurrencias = 0;
    std::vector<int> ocurrencias_por_archivo(offsets.size(), 0);

    // Calcula h = d^(M-1) % q
    for (int i = 0; i < M - 1; i++)
        h = (h * d) % q;

    // Calcula hash del patrón y de la primera ventana del texto
    for (int i = 0; i < M; i++) {
        hash_patron = (d * hash_patron + pat[i]) % q;
        hash_ventana = (d * hash_ventana + txt[i]) % q;
    }

    // Recorre el texto para buscar coincidencias
    for (int i = 0; i <= N - M; i++) {
        // Si el hash coincide, verifica carácter por carácter
        if (hash_patron == hash_ventana) {
            bool match = true;
            for (int j = 0; j < M; j++) {
                if (txt[i + j] != pat[j]) {
                    match = false;
                    break;
                }
            }

            if (match) {
                total_ocurrencias++;

                // Determina a qué archivo pertenece la posición actual
                int archivo_idx = 0;
                for (int k = 0; k < offsets.size(); ++k) {
                    if (i < offsets[k]) break;
                    archivo_idx = k;
                }

                ocurrencias_por_archivo[archivo_idx]++;
            }
        }

        // Calcula el nuevo hash de la siguiente ventana
        if (i < N - M) {
            hash_ventana = (d * (hash_ventana - txt[i] * h) + txt[i + M]) % q;
            if (hash_ventana < 0)
                hash_ventana += q;
        }
    }

    return total_ocurrencias;
}