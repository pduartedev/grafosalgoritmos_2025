/**
 * @file main.cpp
 * @brief Programa principal para resolver o LAB-02
 * @details Este programa lê um grafo orientado com pesos, verifica a existência
 *          de ciclos negativos e, caso não existam, calcula os caminhos mínimos
 *          entre todos os pares de vértices.
 * @date 2025-06-21
 * @author pduartedev
 */

#include <iostream>
#include "directed-graph.hpp"

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    
    DirectedGraph graph(n);
    
    // Leitura do grafo
    for (int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        graph.addEdge(u, v, c);
    }
    
    // Verifica se há ciclo negativo
    vector<int> cycle;
    if (graph.hasNegativeCycle(cycle)) {
        cout << "Ciclo negativo detectado" << endl;
        
        // Remove o último vértice que é igual ao primeiro (repetido)
        cycle.pop_back();
        
        // Imprime os vértices do ciclo
        for (size_t i = 0; i < cycle.size(); i++) {
            cout << cycle[i];
            if (i < cycle.size() - 1)
                cout << " ";
        }
        cout << endl;
    } else {
        // Calcula os caminhos mínimos entre todos os pares de vértices
        vector<vector<int>> distances = graph.allPairsShortestPaths();
        
        // Imprime a matriz de distâncias
        graph.printDistanceMatrix(distances);
    }
    
    return 0;
}