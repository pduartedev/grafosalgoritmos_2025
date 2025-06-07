#include "graph.hpp"
#include <algorithm>

using namespace std;

// Construtor
Graph::Graph(int vertices, int edges) : n(vertices), m(edges) {
    adj.resize(n);
}

// Adiciona uma aresta ao grafo
void Graph::addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}

// Verifica se o grafo é conexo usando DFS
bool Graph::isConnected() {
    if (n == 0) return true;
    
    vector<bool> visited(n, false);
    dfs(0, visited);
    
    // Verifica se todos os vértices foram visitados
    for (bool v : visited) {
        if (!v) return false;
    }
    return true;
}

// Função auxiliar para DFS
void Graph::dfs(int v, vector<bool>& visited) {
    visited[v] = true;
    for (int u : adj[v]) {
        if (!visited[u]) {
            dfs(u, visited);
        }
    }
}

// Algoritmo de Tarjan para encontrar pontos de articulação
vector<int> Graph::findArticulationPoints() {
    vector<int> disc(n, -1);   // Tempo de descoberta
    vector<int> low(n, -1);    // Valor low para o algoritmo de Tarjan
    vector<bool> ap(n, false); // Marca se um vértice é ponto de articulação
    int time = 0;
    
    // Executa DFS começando de cada vértice não visitado
    for (int i = 0; i < n; i++) {
        if (disc[i] == -1) {
            dfsAP(i, -1, disc, low, ap, time);
        }
    }
    
    // Coleta os pontos de articulação identificados
    vector<int> articulationPoints;
    for (int i = 0; i < n; i++) {
        if (ap[i]) {
            articulationPoints.push_back(i);
        }
    }
    
    return articulationPoints;
}

// DFS para encontrar pontos de articulação (parte do algoritmo de Tarjan)
void Graph::dfsAP(int u, int parent, vector<int>& disc, vector<int>& low, vector<bool>& ap, int& time) {
    int children = 0;
    disc[u] = low[u] = ++time;
    
    for (int v : adj[u]) {
        // Se v não foi visitado
        if (disc[v] == -1) {
            children++;
            dfsAP(v, u, disc, low, ap, time);
            
            // Atualiza o valor low de u
            low[u] = min(low[u], low[v]);
            
            // Verifica condição para ponto de articulação
            // Se u não é raiz e low[v] >= disc[u]
            if (parent != -1 && low[v] >= disc[u]) {
                ap[u] = true;
            }
        } 
        // Se v já foi visitado e não é o pai, atualiza low[u]
        else if (v != parent) {
            low[u] = min(low[u], disc[v]);
        }
    }
    
    // Caso especial: se u é raiz e tem mais de um filho
    if (parent == -1 && children > 1) {
        ap[u] = true;
    }
}

// Encontra pares de vértices de corte
vector<pair<int, int>> Graph::findCutVertexPairs() {
    // Se o grafo tem pontos de articulação ou não é conexo, não é 2-conexo
    if (!isConnected() || !findArticulationPoints().empty()) {
        return vector<pair<int, int>>();
    }
    
    // Conjunto para armazenar pares de corte únicos
    set<pair<int, int>> cutPairsSet;
    
    // Para grafos menores, usamos força bruta
    if (n <= 1000) {
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (isCutPair(i, j)) {
                    cutPairsSet.insert({i, j});
                }
            }
        }
    } else {
        // Para grafos maiores, usamos uma abordagem mais sofisticada
        // Verifica apenas pares estratégicos com base na estrutura do grafo
        
        // Construímos conjuntos de vizinhos para cada vértice
        vector<unordered_set<int>> neighbors(n);
        
        for (int i = 0; i < n; i++) {
            for (int j : adj[i]) {
                neighbors[i].insert(j);
            }
        }
        
        // Verifica pares de vértices
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                // Pula se i e j estão diretamente conectados
                if (neighbors[i].find(j) != neighbors[i].end()) {
                    continue;
                }
                
                // Encontra vizinhos comuns
                vector<int> commonNeighbors;
                for (int neighbor : neighbors[i]) {
                    if (neighbors[j].find(neighbor) != neighbors[j].end()) {
                        commonNeighbors.push_back(neighbor);
                    }
                }
                
                // Se têm vizinhos em comum, verifica se formam um par de corte
                if (!commonNeighbors.empty() && isCutPair(i, j)) {
                    cutPairsSet.insert({i, j});
                }
            }
        }
    }
    
    // Converte o conjunto para um vetor e ordena
    vector<pair<int, int>> cutPairs(cutPairsSet.begin(), cutPairsSet.end());
    return cutPairs;
}

// Verifica se remover os vértices u e v desconecta o grafo
bool Graph::isCutPair(int u, int v) {
    if (n <= 2) return false;
    
    vector<bool> visited(n, false);
    visited[u] = visited[v] = true;
    
    // Encontra um vértice inicial diferente de u e v
    int start = 0;
    while (start == u || start == v) start++;
    
    // Realiza DFS a partir de start, excluindo u e v
    dfsExcluding(start, u, v, visited);
    
    // Verifica se todos os vértices (exceto u e v) foram visitados
    for (int i = 0; i < n; i++) {
        if (i != u && i != v && !visited[i]) {
            return true; // Encontrou um vértice não alcançável
        }
    }
    
    return false;
}

// DFS excluindo dois vértices específicos
void Graph::dfsExcluding(int vertex, int exclude1, int exclude2, vector<bool>& visited) {
    visited[vertex] = true;
    
    for (int neighbor : adj[vertex]) {
        if (neighbor != exclude1 && neighbor != exclude2 && !visited[neighbor]) {
            dfsExcluding(neighbor, exclude1, exclude2, visited);
        }
    }
}

// Determina a conectividade do grafo (0, 1, 2 ou pelo menos 3)
int Graph::getConnectivity() {
    // Um grafo é 0-conexo se não for conexo
    if (!isConnected()) return 0;
    
    // Um grafo é 1-conexo se tiver pontos de articulação
    vector<int> artPoints = findArticulationPoints();
    if (!artPoints.empty()) return 1;
    
    // Um grafo é 2-conexo se tiver pares de vértices de corte
    vector<pair<int, int>> cutPairs = findCutVertexPairs();
    if (!cutPairs.empty()) return 2;
    
    // Se não for nenhum dos anteriores, é pelo menos 3-conexo
    return 3;
}