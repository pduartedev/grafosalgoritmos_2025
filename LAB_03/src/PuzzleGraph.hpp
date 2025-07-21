#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

// Classe para representar um vértice (estado) no grafo
class GraphNode {
private:
    vector<vector<int>> state;
    int size;
    string id; // ID único para este estado
    int emptyRow, emptyCol;
    
public:
    GraphNode();
    GraphNode(const vector<int>& input);
    GraphNode(const vector<vector<int>>& state);
    
    // Getters
    const vector<vector<int>>& getState() const { return state; }
    int getSize() const { return size; }
    const string& getId() const { return id; }
    pair<int, int> getEmptyPosition() const { return {emptyRow, emptyCol}; }
    
    // Métodos principais
    bool isGoal() const;
    int calculateManhattanDistance() const;
    void print() const;
    string toString() const;
    
    // Operadores
    bool operator==(const GraphNode& other) const;
    bool operator<(const GraphNode& other) const;
    
private:
    void findEmptyPosition();
    void generateId();
    vector<vector<int>> getGoalState() const;
};

// Hash para usar GraphNode em unordered containers
struct GraphNodeHash {
    size_t operator()(const GraphNode& node) const {
        return hash<string>{}(node.getId());
    }
};

// Classe para representar uma aresta no grafo
class GraphEdge {
private:
    string fromNodeId;
    string toNodeId;
    string moveDescription;
    int cost;
    
public:
    GraphEdge(const string& from, const string& to, const string& move, int c = 1);
    
    // Getters
    const string& getFromNodeId() const { return fromNodeId; }
    const string& getToNodeId() const { return toNodeId; }
    const string& getMoveDescription() const { return moveDescription; }
    int getCost() const { return cost; }
};

// Classe principal do grafo para o puzzle
class PuzzleGraph {
private:
    unordered_map<string, GraphNode> nodes;
    unordered_map<string, vector<GraphEdge>> adjacencyList;
    
public:
    PuzzleGraph();
    
    // Métodos para manipular o grafo
    void addNode(const GraphNode& node);
    void addEdge(const GraphNode& from, const GraphNode& to, const string& moveDescription);
    
    // Busca e navegação
    vector<GraphNode> getNeighbors(const GraphNode& node);
    bool hasNode(const string& nodeId) const;
    GraphNode getNode(const string& nodeId) const;
    
    // Método para gerar vizinhos dinamicamente (sem pré-construir todo o grafo)
    vector<pair<GraphNode, string>> generateNeighbors(const GraphNode& node);
    
    // Estatísticas
    int getNodeCount() const { return nodes.size(); }
    int getEdgeCount() const;
    
    void printGraphInfo() const;
    
private:
    bool isValidMove(const GraphNode& node, int newRow, int newCol) const;
    GraphNode makeMove(const GraphNode& node, int newRow, int newCol) const;
};
