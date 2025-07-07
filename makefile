# Nombre del ejecutable
TARGET = patternsearch

# Archivos fuente
SRCS = main.cpp SearchPatternAlgorithms/AlgorithmBased/KMPSearch.cpp SearchPatternAlgorithms/AlgorithmBased/RabinKarpSearch.cpp SearchPatternAlgorithms/AlgorithmBased/BoyerMooreSearch.cpp SearchPatternAlgorithms/DataStructureBased/SuffixArraySearch.cpp
# Compilador y banderas
CXX = g++
CXXFLAGS = -Wall -std=c++17 -O2 -Wno-sign-compare

# Regla principal
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

# Limpieza
clean:
	rm -f $(TARGET)