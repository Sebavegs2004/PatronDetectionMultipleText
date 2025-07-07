#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "searchpattern_lib.h"
#include <filesystem>
#include <fstream>
#include <chrono>


int main(int argc, char const *argv[])
{
    std::string rute = (std::filesystem::current_path()).string() + "/datasets/" + argv[1];
    std::string complete_text = "", line, pattern = argv[3]; //rute crea directorio hacia la carpeta argv[1]
    int num_archives = std::stoi(argv[2]), breaker = 1, occu = 0, occur_total = 0;
    std::vector<size_t> offsets = {0};  // Empieza en 0
    std::vector<std::string> nombres_docs;
    std::vector<int> occur_docs;
    double time = 0;

    for (auto entry : std::filesystem::directory_iterator(rute)){ // encuentra cada archivo encontrado en la carpeta argv[1]
        if (breaker > (num_archives)) break; // romper for cuando se llegue al numero solicitado de archivos
        
        std::string temp_text = "";  
        std::ifstream f(entry.path()); // abrimos los archivos encontrados en argv[1] (si no son txt fallara no lo valide porque pene)

        while(getline(f, line)){ // concatenamos cada linea del archivo para tener el texto completo
            temp_text += line;
            temp_text += " ";
        }
        nombres_docs.push_back(entry.path().filename()); // guardar nombre de documento leido

        std::cout << entry.path().filename() << " = ";
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<int> suffArray = buildSuffArr(temp_text);
        auto end = std::chrono::high_resolution_clock::now();
        time += std::chrono::duration<double>(end - start).count();
        occu = suffixArraySearch(temp_text, pattern, suffArray);
        std::cout << occu << std::endl;
        occur_total += occu;

        complete_text += temp_text + "$"; // concatenamos el text del archivo
        
        offsets.push_back(complete_text.size() + 1); // Guardamos offset del proximo documento (posicion donde comenzara el siguiente)
        breaker += 1;
    }
    offsets.pop_back();
    complete_text.erase(complete_text.size() - 1, 1);

    auto start = std::chrono::high_resolution_clock::now();
    auto occur = boyermooreSearch(complete_text, pattern); // tomamos el tiempo del algoritmo con el text concatenado de todos los archivos
    auto end = std::chrono::high_resolution_clock::now();
    auto running_time = std::chrono::duration<double>(end - start).count();

    std::cout << "Algoritmo Boyer-Moore:\n\tOcurrencias = " << occur << "\n\tTimepo de ejecucion = " << running_time << "\n" << std::endl;

    std::cout << "Algoritmo Suffix-Array:\n\tOcurrencias = " << occur_total << "\n\tTimepo de ejecucion = " << time << "\n" << std::endl;

    return 0;
}