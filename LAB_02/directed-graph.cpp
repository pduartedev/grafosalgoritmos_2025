/**
 * @file DirectedGraph.cpp
 * @brief Implementação da classe DirectedGraph para grafos direcionados com pesos
 * @date 2025-06-21
 * @author pduartedev
 */

#include "directed-graph.hpp"
#include <algorithm>
#include <queue>
#include <utility>
#include <functional>

using namespace std;

DirectedGraph::DirectedGraph(int n) : numVertices(n) {
    adjList.resize(n);
}

void DirectedGraph::addEdge(int source, int target, int weight) {
    adjList[source].emplace_back(target, weight);
    edgeList.push_back({source, target, weight});
}

bool DirectedGraph::hasNegativeCycle(vector<int>& cycle) {
    // Algoritmo de Bellman-Ford modificado para detectar e retornar um ciclo negativo
    vector<int> dist(numVertices, 0);
    vector<int> parent(numVertices, -1);
    int x = -1;

    // Relaxamento de arestas n-1 vezes
    for (int i = 0; i < numVertices; i++) {
        x = -1;
        for (const auto& e : edgeList) {
            if (dist[e.target] > dist[e.source] + e.weight) {
                dist[e.target] = dist[e.source] + e.weight;
                parent[e.target] = e.source;
                x = e.target;
            }
        }
    }

    // Se não houver atualização na n-ésima iteração, não há ciclo negativo
    if (x == -1) {
        return false;
    }

    // Encontrando um vértice que faz parte de um ciclo negativo
    for (int i = 0; i < numVertices; i++) {
        x = parent[x];
    }

    // Construindo o ciclo negativo
    cycle.clear();
    int y = x;
    do {
        cycle.push_back(y);
        y = parent[y];
    } while (y != x);
    cycle.push_back(y);  // Adiciona x novamente para fechar o ciclo
    
    // Inverte o ciclo para obter a ordem correta
    reverse(cycle.begin(), cycle.end());
    
    return true;
}

vector<int> DirectedGraph::bellmanFord(int source) {
    // Inicializa as distâncias como infinito
    vector<int> dist(numVertices + 1, INF);
    dist[source] = 0;

    // Relaxa todas as arestas |V| - 1 vezes
    for (int i = 0; i < numVertices; i++) {
        for (const auto& e : edgeList) {
            if (dist[e.source] != INF && dist[e.target] > dist[e.source] + e.weight) {
                dist[e.target] = dist[e.source] + e.weight;
            }
        }
    }

    return dist;
}

vector<int> DirectedGraph::dijkstra(int source, const vector<int>& h) {
    // Inicializa as distâncias como infinito
    vector<int> dist(numVertices, INF);
    dist[source] = 0;

    // Fila de prioridade para os vértices (distância, vértice)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) continue;

        // Para cada vizinho de u
        for (const auto& edge : adjList[u]) {
            int v = edge.first;
            int weight = edge.second;
            
            // Peso reponderado usando os potenciais h
            int weightReweighted = weight + h[u] - h[v];
            
            // Se encontrarmos um caminho mais curto para v através de u
            if (dist[u] != INF && dist[v] > dist[u] + weightReweighted) {
                dist[v] = dist[u] + weightReweighted;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

vector<vector<int>> DirectedGraph::allPairsShortestPaths() {
    // Criamos um grafo auxiliar com um super vértice s
    int n = numVertices;
    DirectedGraph auxGraph(n + 1);
    
    // Copiamos todas as arestas do grafo original
    for (const auto& e : edgeList) {
        auxGraph.addEdge(e.source, e.target, e.weight);
    }
    
    // Adicionamos arestas de peso 0 do super vértice s para todos os outros vértices
    for (int v = 0; v < n; v++) {
        auxGraph.addEdge(n, v, 0);
    }
    
    // Executamos Bellman-Ford a partir do super vértice s para calcular os potenciais h(v)
    vector<int> h = auxGraph.bellmanFord(n);
    
    // Verifica se há ciclos negativos
    for (const auto& e : edgeList) {
        if (h[e.source] != INF && h[e.target] != INF && 
            h[e.target] > h[e.source] + e.weight) {
            return {}; // Ciclo negativo detectado
        }
    }
    
    // Matriz de distâncias
    vector<vector<int>> dist(n, vector<int>(n, INF));
    
    // Para cada vértice como fonte
    for (int u = 0; u < n; u++) {
        // Executamos Dijkstra com os pesos reponderados
        vector<int> distU = dijkstra(u, h);
        
        // Ajustamos as distâncias usando os potenciais h
        for (int v = 0; v < n; v++) {
            if (distU[v] != INF) {
                // Restaurando o peso original: d'(u,v) = d(u,v) + h(v) - h(u)
                dist[u][v] = distU[v] + h[v] - h[u];
            }
        }
    }
    
    return dist;
}

void DirectedGraph::printDistanceMatrix(const vector<vector<int>>& distances) {
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            if (distances[i][j] == INF) {
                cout << "X";
            } else {
                cout << distances[i][j];
            }
            
            if (j < numVertices - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }
}