# Makefile para o projeto LAB_02

# Compilador
CC = g++

# Flags de compilação
CFLAGS = -Wall -std=c++14

# Nome do executável
TARGET = main

# Arquivos fonte (todos os .cpp do diretório)
SOURCES = $(wildcard *.cpp)

# Objetos (substitui .cpp por .o)
OBJECTS = $(SOURCES:.cpp=.o)

# Regra principal
all: $(TARGET)

# Regra para linking
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# Regra para compilação
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para limpar arquivos temporários
clean:
	rm -f $(OBJECTS)

# Regra para limpar tudo (objetos e executável)
distclean: clean
	rm -f $(TARGET)

# Regra para executar o programa
run: $(TARGET)
	./$(TARGET)

# Regra para compilar e executar
all-run: all run

# Definição de phony targets
.PHONY: all clean distclean run all-run
