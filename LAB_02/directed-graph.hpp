/**
 * @file DirectedGraph.hpp
 * @brief Declaração da classe DirectedGraph para grafos direcionados com pesos
 * @date 2025-06-21
 * @author pduartedev
 */

#pragma once

#include <vector>
#include <limits>
#include <iostream>
#include <string>
#include <queue>
#include <utility> // for std::pair

using namespace std;

class DirectedGraph {
private:
    int numVertices;
    vector<vector<pair<int, int>>> adjList;
    
    const int INF = numeric_limits<int>::max() / 2;

    struct Edge {
        int source, target, weight;
    };
    vector<Edge> edgeList;

    // Executa o algoritmo de Bellman-Ford a partir de um vértice fonte
    // Retorna um vetor de potenciais para reponderar o grafo
    vector<int> bellmanFord(int source);

    // Executa o algoritmo de Dijkstra a partir de um vértice fonte com pesos reponderados
    vector<int> dijkstra(int source, const vector<int>& h);

public:
    // Construtor
    DirectedGraph(int n);
    
    // Adiciona uma aresta ao grafo
    void addEdge(int source, int target, int weight);
    
    // Verifica se há ciclo negativo e retorna o ciclo caso exista
    bool hasNegativeCycle(vector<int>& cycle);
    
    // Calcula caminhos mínimos entre todos os pares de vértices usando o algoritmo de Johnson
    vector<vector<int>> allPairsShortestPaths();
    
    // Imprime a matriz de distâncias conforme o formato especificado
    void printDistanceMatrix(const vector<vector<int>>& distances);
};