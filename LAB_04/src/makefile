# Compilador C++
CXX = g++

# Flags de compilação: -std=c++17 para recursos modernos, -O2 para otimização, -Wall para avisos
CXXFLAGS = -std=c++20 -O2 -Wall

# Nome do executável
EXECUTABLE = lab04_solver

# Arquivos fonte
SOURCES = main.cpp Grafo.cpp FluxMaxCustoMin.cpp

# Arquivos objeto (gerados a partir dos fontes)
OBJECTS = $(SOURCES:.cpp=.o)

# Regra principal: compila tudo
all: $(EXECUTABLE)

# Regra para criar o executável final a partir dos arquivos objeto
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) $(OBJECTS)

# Regra para compilar cada .cpp em um .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para limpar os arquivos gerados
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

.PHONY: all clean
