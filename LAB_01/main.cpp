#include <iostream>
#include <algorithm>
#include "graph.hpp"

using namespace std;

int main() {
    // Leitura dos dados do grafo
    int n, m;
    cin >> n >> m;
    
    // Criação do grafo
    Graph graph(n, m);
    
    // Leitura e adição das arestas
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph.addEdge(u, v);
    }
    
    // Determina a conectividade do grafo
    int connectivity = graph.getConnectivity();
    
    // Imprime o resultado conforme o enunciado
    if (connectivity == 0) {
        cout << "Grafo desconexo." << endl;
    } else if (connectivity == 1) {
        cout << "Grafo 1-conexo." << endl;
        
        // Lista os pontos de articulação
        vector<int> artPoints = graph.findArticulationPoints();
        sort(artPoints.begin(), artPoints.end());
        
        for (int point : artPoints) {
            cout << point << endl;
        }
    } else if (connectivity == 2) {
        cout << "Grafo 2-conexo." << endl;
        
        // Lista os pares de vértices de corte
        vector<pair<int, int>> cutPairs = graph.findCutVertexPairs();
        sort(cutPairs.begin(), cutPairs.end());
        
        for (const auto& pair : cutPairs) {
            cout << pair.first << " " << pair.second << endl;
        }
    } else {
        cout << "Grafo 3-conexo." << endl;
    }
    
    return 0;
}