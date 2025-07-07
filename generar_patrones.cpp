#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "searchpattern_lib.h"
#include <filesystem>
#include <fstream>
#include <chrono>
#include <random>

//leer la entrada del usuario con D1$D2D3... etc, guardarlas en un archivo que lea cada separacion

int main(int argc, char const *argv[]){
    // ./generador_patrones <carpeta> <cantidad archivos> <cantidad_patrones> <largo>
    std::string rute = (std::filesystem::current_path()).string() + "/datasets/" + argv[1];
    std::string complete_text = "", line;
    int num_archives = std::stoi(argv[2]), breaker = 0;
    int cantidad_patrones = std::stoi(argv[3]), largo_patrones=std::stoi(argv[4]);

    for (auto entry : std::filesystem::directory_iterator(rute)){ // encuentra cada archivo encontrado en la carpeta argv[1]
        if (breaker == (num_archives + 1)) break; // romper for cuando se llegue al numero solicitado de archivos
        
        std::string temp_text = "";  
        std::ifstream f(entry.path()); // abrimos los archivos encontrados en argv[1] (si no son txt fallara no lo valide porque pene)

        while(getline(f, line)){ // concatenamos cada linea del archivo para tener el texto completo
            temp_text += line;
        }
        complete_text += "$" + temp_text; // concatenamos el text del archivo
        
        breaker += 1;
    }
    // Determinar el límite superior para las posiciones de inicio de los patrones
    int max_start = complete_text.size()-largo_patrones;

    // Inicialización del generador de números aleatorios (Mersenne Twister)
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, max_start);

    // Crear el archivo de salida donde se guardarán los patrones generados
    std::ofstream out("patrones.txt");

    // Generar los patrones extrayendo substrings desde posiciones aleatorias del texto completo
    for (int i = 0; i < cantidad_patrones; ++i) {
        int start = dist(rng);
        std::string original = complete_text.substr(start, largo_patrones);
        out << original << '\n';
    }

    return 0;
}