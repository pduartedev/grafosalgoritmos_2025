#pragma once

#include "Grafo.hpp"
#include <vector>
#include <utility> // Para pair

using namespace std;

// Classe que encapsula o algoritmo de Fluxo Máximo de Custo Mínimo.
class FluxoCustoMinimo
{
public:
    // Construtor: recebe uma referência para o grafo.
    FluxoCustoMinimo(Grafo &grafo);

    // Executa o algoritmo para encontrar o fluxo de custo mínimo da fonte 's' ao sorvedouro 't'.
    // Retorna um par contendo {fluxo máximo, custo mínimo}.
    pair<int, int> executar(int fonte, int sorvedouro);

    // Após a execução do algoritmo, retorna os vértices que compõem o lado da fonte (s) no corte mínimo.
    vector<int> obter_corte_minimo(int fonte);

private:
    Grafo &grafo; // Referência para o grafo de entrada.

    // Estruturas de dados auxiliares para o algoritmo de Dijkstra.
    vector<int> potencial;   // Potenciais dos vértices para manter os custos das arestas não-negativos.
    vector<int> distancia;   // Distâncias da fonte em cada iteração de Dijkstra.
    vector<int> pai_vertice; // Armazena o vértice pai no caminho aumentante encontrado.
    vector<int> pai_aresta;  // Armazena o índice da aresta pai no caminho aumentante.

    // Algoritmo de Dijkstra com potenciais para encontrar o caminho mais curto (menor custo)
    // no grafo residual. Retorna 'true' se um caminho for encontrado, 'false' caso contrário.
    bool dijkstra(int fonte, int sorvedouro);
};