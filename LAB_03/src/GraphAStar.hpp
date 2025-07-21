#pragma once

#include "PuzzleGraph.hpp"
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <chrono>

using namespace std;

// Estrutura para representar um nó na busca A*
struct AStarNode {
    GraphNode graphNode;
    int gCost;           // Custo do caminho desde o início
    int hCost;           // Heurística (Manhattan distance)
    string parentId;     // ID do nó pai para reconstruir o caminho
    string moveUsed;     // Movimento usado para chegar aqui
    
    AStarNode() : gCost(0), hCost(0), parentId(""), moveUsed("") {}
    
    AStarNode(const GraphNode& node, int g = 0, int h = 0, 
              const string& parent = "", const string& move = "")
        : graphNode(node), gCost(g), hCost(h), parentId(parent), moveUsed(move) {}
    
    int getFCost() const { return gCost + hCost; }
    
    // Operador para priority_queue (min-heap)
    bool operator>(const AStarNode& other) const {
        int thisFCost = getFCost();
        int otherFCost = other.getFCost();
        
        if (thisFCost != otherFCost) {
            return thisFCost > otherFCost;
        }
        return hCost > other.hCost; // Desempate pela heurística
    }
};

class GraphAStar {
private:
    PuzzleGraph graph;
    int statesEvaluated;
    int statesEnqueued;
    chrono::duration<double> executionTime;
    
public:
    GraphAStar();
    
    // Método principal para resolver o puzzle usando A* no grafo
    vector<GraphNode> solve(const GraphNode& initial);
    
    // Getters para estatísticas
    int getStatesEvaluated() const { return statesEvaluated; }
    int getStatesEnqueued() const { return statesEnqueued; }
    double getExecutionTime() const { return executionTime.count(); }
    
    // Método para imprimir estatísticas
    void printStatistics() const;
    
    // Acesso ao grafo
    const PuzzleGraph& getGraph() const { return graph; }
    
private:
    // Reconstroi o caminho da solução
    vector<GraphNode> reconstructPath(const AStarNode& goalNode, 
                                     const unordered_map<string, AStarNode>& allNodes);
    
    // Calcula a heurística para um nó
    int calculateHeuristic(const GraphNode& node);
};
