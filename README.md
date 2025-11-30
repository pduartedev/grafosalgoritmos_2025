# Grafos e Algoritmos 2025 🎓

Repositório contendo implementações práticas e exercícios da disciplina de Grafos e Algoritmos desenvolvidos em 2025.  O projeto inclui implementações de algoritmos clássicos de teoria dos grafos, incluindo análise de conectividade, caminhos mínimos, busca A* e fluxo máximo com custo mínimo.

## 📋 Sobre o Projeto

Este repositório apresenta soluções completas para problemas fundamentais de teoria dos grafos, implementados em C++ com foco em eficiência e clareza. Cada laboratório aborda conceitos distintos e progressivamente mais avançados da área.

## 🛠️ Tecnologias Utilizadas

- **C++** (90. 1%) - Implementação principal dos algoritmos
- **Makefile** (5.7%) - Sistema de build automatizado
- **Python** (4.2%) - Scripts auxiliares e análises
- **C++17/C++20** - Padrões modernos da linguagem

## 📁 Estrutura do Projeto

```
grafosalgoritmos_2025/
├── LAB_01/              # Conectividade de Vértices
│   ├── graph. cpp        # Implementação da classe Graph
│   ├── graph.hpp        # Header da classe Graph
│   ├── main.cpp         # Programa principal
│   ├── Makefile         # Build configuration
│   └── enunc-lab01/     # Enunciado do laboratório
│
├── LAB_02/              # Caminhos Mínimos e Ciclos Negativos
│   ├── src/             # Código fonte (Floyd-Warshall/Bellman-Ford)
│   └── doc/             # Documentação
│
├── LAB_03/              # Busca A* (8-puzzle e 15-puzzle)
│   ├── src/
│   │   ├── GraphAStar.cpp       # Implementação do A*
│   │   ├── GraphAStar.hpp       # Header do A*
│   │   ├── PuzzleGraph.cpp      # Grafo do puzzle
│   │   ├── PuzzleGraph.hpp      # Header do grafo
│   │   ├── main.cpp             # Programa principal
│   │   ├── Makefile             # Build configuration
│   │   └── ins/                 # Instâncias de teste
│   │       ├── ins-8/           # 8-puzzle (100 instâncias)
│   │       └── ins-15/          # 15-puzzle (100 instâncias)
│   ├── doc/                     # Documentação
│   └── README.md                # Documentação específica
│
├── LAB_04/              # Fluxo Máximo com Custo Mínimo
│   ├── src/             # Código fonte (Min-Cost Max-Flow)
│   └── doc/             # Documentação
│
└── README.md            # Este arquivo
```

## 🚀 Como Compilar e Executar

### Pré-requisitos

- Compilador C++ com suporte a C++17 ou superior (g++ recomendado)
- Make (sistema de build)
- Python 3. x (opcional, para scripts de análise)

### Compilação Geral

Cada laboratório possui seu próprio Makefile.  Para compilar um laboratório específico:

```bash
cd LAB_0X
make
```

### Limpeza

Para remover arquivos compilados:

```bash
make clean
```

## 📚 Laboratórios Implementados

### LAB_01 - Conectividade de Vértices 🔗

**Objetivo**: Determinar a conectividade de um grafo (0, 1, 2 ou ≥3) e identificar vértices/pares de corte.

**Algoritmo**: Busca em profundidade (DFS) com detecção de pontos de articulação

**Entrada**: Grafo não-direcionado via stdin
- Primeira linha: `n m` (vértices e arestas)
- Próximas m linhas: `u v` (aresta entre u e v)

**Saída**:
- Grafo desconexo: "Grafo desconexo."
- 1-conexo: "Grafo 1-conexo." + lista de vértices de corte
- 2-conexo: "Grafo 2-conexo." + lista de pares de vértices de corte
- ≥3-conexo: "Grafo 3-conexo."

**Compilação e Execução**:
```bash
cd LAB_01
make
./main < entrada.txt
```

**Características**:
- Detecção eficiente de pontos de articulação
- Análise de conectividade em tempo linear
- Ordem lexicográfica na saída

---

### LAB_02 - Caminhos Mínimos e Ciclos Negativos 🔄

**Objetivo**: Detectar ciclos negativos em grafos orientados com pesos e calcular custos mínimos entre todos os pares de vértices.

**Algoritmos**:
- **Bellman-Ford**: Detecção de ciclos negativos
- **Floyd-Warshall**: Caminhos mínimos entre todos os pares

**Entrada**: Grafo orientado com pesos via stdin
- Primeira linha: `n m` (vértices e arestas, n≤1000, m≤4000)
- Próximas m linhas: `u v c` (arco de u→v com custo c, -10000≤c≤10000)

**Saída**:
- **Com ciclo negativo**: 
  - "Ciclo negativo detectado"
  - Sequência de vértices do ciclo
- **Sem ciclo negativo**:
  - Matriz n×n com custos mínimos
  - 'X' quando não existe caminho

**Compilação e Execução**:
```bash
cd LAB_02
make
./main < grafo.txt
```

**Características**:
- Detecção robusta de ciclos negativos
- Complexidade O(n³) para Floyd-Warshall
- Suporte a grafos esparsos e densos

---

### LAB_03 - Busca A* (8-puzzle e 15-puzzle) 🧩

**Objetivo**: Resolver os clássicos problemas de sliding puzzles usando busca heurística A*.

**Algoritmo**: A* com heurísticas otimizadas
- **Heurística básica**: Distância de Manhattan
- **Heurística avançada**: Manhattan + Conflitos Lineares + Penalidades

**Entrada**: Configuração inicial do puzzle
- **8-puzzle**: 9 números (0-8) em uma linha
- **15-puzzle**: 16 números (0-15) em uma linha
- 0 representa o espaço vazio

**Saída (stdout)**:
```
K                    # Número de movimentos

estado_inicial
linha1 linha2 linha3

estado_1
linha1 linha2 linha3

... 

estado_objetivo
linha1 linha2 linha3
```

**Saída (stderr)**:
```
Tempo de execução: X. XXXX segundos
Estados avaliados: XXXX
Estados enfileirados: XXXX
```

**Compilação e Execução**:
```bash
cd LAB_03/src
make

# Entrada via stdin
echo "1 2 3 4 5 6 7 0 8" | ./main

# Entrada via arquivo
./main ins/ins-8/8puzzle_instances. txt

# Processamento em lote
./main ins/ins-8/8puzzle_instances.txt --batch
```

**Testes Disponíveis**:
```bash
make test          # Teste básico 8-puzzle
make test-15       # Teste 15-puzzle
```

**Características**:
- ✅ Detecção de instâncias insolúveis
- ✅ Heurística admissível (garante solução ótima)
- ✅ Otimizações para 15-puzzle (muito mais complexo)
- ✅ 100 instâncias de teste para cada puzzle
- ✅ Modo batch para análise estatística
- ✅ Modelagem como problema de busca em grafo implícito

**Complexidade**:
- **Tempo**: O(b^d) onde b é o fator de ramificação (~2. 67) e d a profundidade
- **Espaço**: O(b^d) para estados na memória
- **8-puzzle**: ~181. 440 estados possíveis (9!/2)
- **15-puzzle**: ~10^13 estados possíveis (16!/2)

---

### LAB_04 - Fluxo Máximo com Custo Mínimo 💰

**Objetivo**: Encontrar um fluxo máximo de custo mínimo entre dois vértices em um grafo orientado com capacidades e custos nas arestas.

**Algoritmo**: Min-Cost Max-Flow (variação do algoritmo de Ford-Fulkerson com custos)

**Entrada**: Grafo orientado com capacidades e custos
- Primeira linha: `N M` (vértices≤1000, arestas≤50000)
- Próximas M linhas: `x y c k` (arco x→y, capacidade c≤1000, custo k≤1000)
- Origem: vértice 0 (s)
- Destino: vértice N-1 (t)

**Saída**:
1. Valor do fluxo máximo
2. Custo total do fluxo máximo de custo mínimo
3.  Praia de um corte mínimo s,t:
   - Formato: `T    v1 v2 v3 ...` (T vértices ordenados)
4. Lista de arestas com fluxo atribuído:
   - Formato: `x y c k -> f` (aresta original → valor do fluxo)

**Compilação e Execução**:
```bash
cd LAB_04
make
./main < rede.txt
```

**Características**:
- Fluxo máximo com custo mínimo simultâneos
- Identificação de corte mínimo
- Suporte a grafos grandes (50k arestas)
- Preservação da ordem das arestas na saída

---

## 📊 Comparação de Complexidade

| Laboratório | Algoritmo Principal | Complexidade Temporal | Complexidade Espacial |
|-------------|---------------------|----------------------|----------------------|
| LAB_01 | DFS + Articulação | O(V + E) | O(V) |
| LAB_02 | Floyd-Warshall | O(V³) | O(V²) |
| LAB_03 | A* | O(b^d) | O(b^d) |
| LAB_04 | Min-Cost Max-Flow | O(V²E²) | O(V + E) |

## 🎯 Conceitos Abordados

### Teoria dos Grafos
- ✅ Conectividade e pontos de articulação
- ✅ Caminhos mínimos (single-source e all-pairs)
- ✅ Detecção de ciclos negativos
- ✅ Busca heurística (A*)
- ✅ Fluxo em redes
- ✅ Cortes mínimos

### Estruturas de Dados
- ✅ Grafos (listas de adjacência)
- ✅ Priority queues (heaps)
- ✅ Hash tables (unordered_map/set)
- ✅ Vetores e matrizes dinâmicas

### Algoritmos
- ✅ DFS/BFS
- ✅ Bellman-Ford
- ✅ Floyd-Warshall
- ✅ A* (busca informada)
- ✅ Ford-Fulkerson (fluxo máximo)
- ✅ Algoritmos de custo mínimo

## 🧪 Testando o Projeto

Cada laboratório inclui casos de teste:

```bash
# LAB_01
cd LAB_01
make test

# LAB_02
cd LAB_02
make test

# LAB_03
cd LAB_03/src
make test         # 8-puzzle
make test-15      # 15-puzzle
./main ins/ins-8/8puzzle_instances.txt --batch

# LAB_04
cd LAB_04
make test
```

## 📝 Formato de Entrada/Saída

Todos os laboratórios seguem o padrão:
- **Entrada**: stdin ou arquivo
- **Saída principal**: stdout (resultado do problema)
- **Estatísticas/Debug**: stderr (quando aplicável)

## 🏆 Destaques Técnicos

### LAB_01
- Implementação eficiente de detecção de pontos de articulação
- Análise de conectividade sem construir grafo complementar

### LAB_02
- Suporte a pesos negativos
- Detecção robusta de ciclos negativos antes de calcular caminhos

### LAB_03
- **Heurística sofisticada** para 15-puzzle:
  - Manhattan Distance
  - Linear Conflicts (conflitos em linhas/colunas)
  - Corner Penalties (penalidades para cantos)
  - Walking Distance (aproximação de dependências)
- Verificação de solvabilidade (paridade de inversões)
- Modo batch para análise estatística de 100 instâncias

### LAB_04
- Fluxo máximo e custo mínimo simultaneamente
- Identificação automática de corte mínimo
- Suporte a redes grandes

## 📖 Referências

- **Cormen et al.** - Introduction to Algorithms (CLRS)
- **Sedgewick & Wayne** - Algorithms, 4th Edition
- **Russell & Norvig** - Artificial Intelligence: A Modern Approach (A* e heurísticas)
- **Ahuja, Magnanti & Orlin** - Network Flows

## 👤 Autor

**pduartedev**

- GitHub: [@pduartedev](https://github.com/pduartedev)

## 📄 Licença

Este projeto é desenvolvido para fins **educacionais** no contexto da disciplina de Grafos e Algoritmos. 

---

## 🚦 Status dos Laboratórios

| Lab | Status | Funcionalidades |
|-----|--------|----------------|
| LAB_01 | ✅ Completo | Conectividade, vértices de corte |
| LAB_02 | ✅ Completo | Ciclos negativos, caminhos mínimos |
| LAB_03 | ✅ Completo | A* para 8 e 15-puzzle, heurísticas avançadas |
| LAB_04 | ✅ Completo | Fluxo máximo com custo mínimo, corte mínimo |

---

⭐ **Se este repositório foi útil para você, considere deixar uma estrela!** ⭐

## 🤝 Contribuições

Este é um projeto acadêmico, mas sugestões de melhorias são bem-vindas através de issues ou pull requests.

## 📧 Contato

Para questões sobre o projeto, abra uma issue no repositório. 

---

**Última atualização**: Novembro de 2025
