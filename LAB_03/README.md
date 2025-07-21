# Algo```
LAB_03/
├── src/
│   ├── Puzzle.h          # Classe para representar o estado do puzzle
│   ├── Puzzle.cpp        # Implementação da classe Puzzle
│   ├── AStar.h           # Classe para o algoritmo A*
│   ├── AStar.cpp         # Implementação do algoritmo A*
│   ├── main.cpp          # Programa principal
│   └── ins/              # Diretório de instâncias de teste
│       ├── ins-8/        # Instâncias do 8-puzzle
│       └── ins-15/       # Instâncias do 15-puzzle
├── Makefile              # Arquivo de configuração para compilação
├── build_and_test.sh     # Script para compilar e testar
└── README.md            # Este arquivo
```-Puzzle e 15-Puzzle

Este projeto implementa o algoritmo A* para resolver os problemas 8-puzzle e 15-puzzle.

## Estrutura do Projeto

```
LAB_03/
├── src/
│   ├── Puzzle.h          # Classe para representar o estado do puzzle
│   ├── Puzzle.cpp        # Implementação da classe Puzzle
│   ├── AStar.h           # Classe para o algoritmo A*
│   ├── AStar.cpp         # Implementação do algoritmo A*
│   └── main.cpp          # Programa principal
├── ins/                  # Diretório de instâncias de teste
│   ├── ins-8/           # Instâncias do 8-puzzle
│   └── ins-15/          # Instâncias do 15-puzzle
├── Makefile              # Arquivo de configuração do Make
├── build_and_test.sh     # Script para compilar e testar
└── README.md            # Este arquivo
```

## Compilação

### Usando Makefile (Recomendado)

```bash
# Compilação normal
make

# Compilação debug
make debug

# Compilação rápida (sem otimização)
make fast

# Limpeza
make clean

# Executar testes
make test

# Ver todos os comandos disponíveis
make help
```

### Usando o script automático

```bash
chmod +x build_and_test.sh
./build_and_test.sh
```

### Compilação manual

```bash
g++ -std=c++17 -O2 -Wall -Wextra -o astar_puzzle src/main.cpp src/Puzzle.cpp src/AStar.cpp
```

## Uso

### Entrada via arquivo

```bash
./bin/astar_puzzle src/ins/ins-8/8puzz.00
```

### Entrada via stdin

```bash
echo "1 2 3 4 5 6 7 8 0" | ./bin/astar_puzzle
```

## Formato de Entrada

- **8-puzzle**: 9 números (0-8) em uma linha
- **15-puzzle**: 16 números (0-15) em uma linha
- O número 0 representa a posição vazia
- Os números devem ser uma permutação válida

### Exemplo de entrada 8-puzzle:
```
5 6 2 7 1 8 3 4 0
```

### Exemplo de entrada 15-puzzle:
```
1 2 3 4 5 6 7 8 9 10 11 12 13 14 0 15
```

## Formato de Saída

### Saída Padrão (stdout)
```
K

estado_inicial
linha1 linha2 linha3

estado_1
linha1 linha2 linha3

...

estado_objetivo
linha1 linha2 linha3
```

### Saída de Erro (stderr)
```
Tempo de execução: X.XXXX segundos
Estados avaliados: XXXX
Estados enfileirados: XXXX
```

## Algoritmo

O projeto utiliza o algoritmo A* com as seguintes características:

- **Heurística**: Distância de Manhattan
- **Função de avaliação**: f(n) = g(n) + h(n)
  - g(n): custo do caminho desde o início
  - h(n): heurística (distância de Manhattan)
- **Estrutura de dados**: Priority queue para estados abertos
- **Detecção de ciclos**: Conjunto de estados fechados

## Funcionalidades

### Classe Puzzle
- Representação do estado do puzzle
- Geração de movimentos válidos
- Cálculo da heurística de Manhattan
- Verificação de estado objetivo
- Operadores de comparação para uso em containers STL

### Classe AStar
- Implementação do algoritmo A*
- Estatísticas de execução
- Reconstrução do caminho da solução

## Exemplo de Execução

```bash
$ echo "1 2 3 4 5 6 7 0 8" | ./bin/astar_puzzle
1

1 2 3
4 5 6
7 0 8

1 2 3
4 5 6
7 8 0
```

```
Tempo de execução: 0.0001 segundos
Estados avaliados: 2
Estados enfileirados: 3
```

## Complexidade

- **Tempo**: O(b^d) onde b é o fator de ramificação e d a profundidade da solução
- **Espaço**: O(b^d) para armazenar estados na memória
- **Otimalidade**: Garantida com heurística admissível (Manhattan distance)

## Testes

O projeto inclui instâncias de teste pré-definidas:
- **8-puzzle**: 100 instâncias em `ins/ins-8/`
- **15-puzzle**: Instâncias em `ins/ins-15/`

Execute o script de teste para validar a implementação:

```bash
./build_and_test.sh
```
