# Makefile para A* Orientado a Grafos

# Compilador e flags
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -O2
DEBUGFLAGS = -std=c++20 -Wall -Wextra -g -DDEBUG

# Arquivos fonte
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

# Nome do executável
TARGET = main

# Regra principal
all: $(TARGET)

# Regra para criar o executável
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@

# Regra para compilar arquivos objeto
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Versão debug
debug: CXXFLAGS = $(DEBUGFLAGS)
debug: $(TARGET)

# Limpeza
clean:
	rm -f *.o $(TARGET)

# Limpeza completa
distclean: clean
	rm -f *~ *.bak

# Teste com 8-puzzle
test: $(TARGET)
	@echo "=== Testando A* Orientado a Grafos ==="
	@echo ""
	@echo "--- Teste com 8-puzzle simples ---"
	@echo "1 2 3 4 5 6 7 0 8" | ./$(TARGET)

# Teste com 15-puzzle
test-15: $(TARGET)
	@echo "=== Testando A* com 15-puzzle ==="
	@echo ""
	@echo "--- Verificando solvabilidade da instância 15puzz.00 ---"
	@./$(TARGET) ins/ins-15/15puzz.00 || true
	@echo ""
	@echo "--- Teste com instância solucionável (1 movimento) ---"
	@./$(TARGET) ins/ins-15/15puzz_goal_minus_1.txt
	@echo ""
	@echo "--- Teste com instância solucionável (2 movimentos) ---"
	@./$(TARGET) ins/ins-15/15puzz_solvable_3moves.txt

# Teste com 15-puzzle simples
test-15-simple: $(TARGET)
	@echo "=== Testando A* com 15-puzzle simples ==="
	@echo ""
	@echo "--- Teste com instância simples ---"
	@./$(TARGET) ins/ins-15/15puzz_simple.txt

# Teste com 15-puzzle médio
test-15-medium: $(TARGET)
	@echo "=== Testando A* com 15-puzzle médio ==="
	@echo ""
	@echo "--- Teste com instância média ---"
	@./$(TARGET) ins/ins-15/15puzz_medium.txt

# Dependências dos headers
main.o: main.cpp PuzzleGraph.hpp GraphAStar.hpp
PuzzleGraph.o: PuzzleGraph.cpp PuzzleGraph.hpp
GraphAStar.o: GraphAStar.cpp GraphAStar.hpp PuzzleGraph.hpp

# Indica que estes targets não são arquivos
.PHONY: all debug clean distclean test test-15 test-15-simple test-15-medium help
