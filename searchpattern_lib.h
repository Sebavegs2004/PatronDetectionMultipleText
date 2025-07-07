#ifndef SEARCHPATTERN_LIB_H
#define SEARCHPATTERN_LIB_H

#include <string>    // Para usar std::vector
#include <cstdint>    // Para usar int32_t
#include <vector>

int boyermooreSearch(std::string txt, std::string pat);
int kmpSearch(std::string txt, std::string pat);
std::vector<int> buildSuffArr(std::string text);
int rabinkarpSearch(std::string pat, std::string txt, std::vector<size_t> offsets);
int suffixArraySearch( std::string text, std::string pat, std::vector<int> sufArr);

#endif