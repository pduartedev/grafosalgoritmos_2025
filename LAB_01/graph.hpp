#pragma once

#include <vector>
#include <set>
#include <unordered_set>

using namespace std;

// Classe para representar um grafo não orientado
class Graph {
    public:

    int n; // Número de vértices
    int m; // Número de arestas
    vector<vector<int>> adj; // Lista de adjacência

    // Função auxiliar para DFS
    void dfs(int v, vector<bool>& visited);
    
    // DFS para encontrar pontos de articulação (algoritmo de Tarjan)
    void dfsAP(int u, int parent, vector<int>& disc, vector<int>& low, 
               vector<bool>& ap, int& time);
    
    // DFS excluindo dois vértices específicos
    void dfsExcluding(int vertex, int exclude1, int exclude2, vector<bool>& visited);

    // Construtor
    Graph(int vertices, int edges);
    
    // Adiciona uma aresta ao grafo
    void addEdge(int u, int v);
    
    // Verifica se o grafo é conexo
    bool isConnected();
    
    // Algoritmo de Tarjan para encontrar pontos de articulação
    vector<int> findArticulationPoints();
    
    // Encontra pares de vértices de corte
    vector<pair<int, int>> findCutVertexPairs();
    
    // Verifica se remover os vértices u e v desconecta o grafo
    bool isCutPair(int u, int v);
    
    // Determina a conectividade do grafo (0, 1, 2 ou pelo menos 3)
    int getConnectivity();
};