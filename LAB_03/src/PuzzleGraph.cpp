#include "PuzzleGraph.hpp"
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <iostream>

// ===== Implementação da classe GraphNode =====

GraphNode::GraphNode() : size(0), emptyRow(0), emptyCol(0) {}

GraphNode::GraphNode(const vector<int>& input) {
    if (input.size() == 9) {
        size = 3;
    } else if (input.size() == 16) {
        size = 4;
    } else {
        throw invalid_argument("Entrada inválida: deve ter 9 ou 16 elementos");
    }
    
    state.resize(size, vector<int>(size));
    
    // Converte entrada linear para matriz
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            state[i][j] = input[i * size + j];
        }
    }
    
    findEmptyPosition();
    generateId();
}

GraphNode::GraphNode(const vector<vector<int>>& state) : state(state) {
    size = state.size();
    findEmptyPosition();
    generateId();
}

void GraphNode::findEmptyPosition() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (state[i][j] == 0) {
                emptyRow = i;
                emptyCol = j;
                return;
            }
        }
    }
}

void GraphNode::generateId() {
    stringstream ss;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i > 0 || j > 0) ss << "-";
            ss << state[i][j];
        }
    }
    id = ss.str();
}

vector<vector<int>> GraphNode::getGoalState() const {
    vector<vector<int>> goal(size, vector<int>(size));
    int num = 1;
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == size - 1 && j == size - 1) {
                goal[i][j] = 0; // Posição vazia no final
            } else {
                goal[i][j] = num++;
            }
        }
    }
    
    return goal;
}

bool GraphNode::isGoal() const {
    vector<vector<int>> goal = getGoalState();
    return state == goal;
}

int GraphNode::calculateManhattanDistance() const {
    int distance = 0;
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (state[i][j] != 0) {
                int targetRow, targetCol;
                if (state[i][j] == size * size) {
                    targetRow = size - 1;
                    targetCol = size - 1;
                } else {
                    targetRow = (state[i][j] - 1) / size;
                    targetCol = (state[i][j] - 1) % size;
                }
                distance += abs(i - targetRow) + abs(j - targetCol);
            }
        }
    }
    
    return distance;
}

string GraphNode::toString() const {
    stringstream ss;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (j > 0) ss << " ";
            ss << state[i][j];
        }
        if (i < size - 1) ss << "\\n";
    }
    return ss.str();
}

void GraphNode::print() const {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (j > 0) cout << " ";
            cout << state[i][j];
        }
        cout << endl;
    }
}

bool GraphNode::operator==(const GraphNode& other) const {
    return id == other.id;
}

bool GraphNode::operator<(const GraphNode& other) const {
    return id < other.id;
}

// ===== Implementação da classe GraphEdge =====

GraphEdge::GraphEdge(const string& from, const string& to, const string& move, int c)
    : fromNodeId(from), toNodeId(to), moveDescription(move), cost(c) {}

// ===== Implementação da classe PuzzleGraph =====

PuzzleGraph::PuzzleGraph() {}

void PuzzleGraph::addNode(const GraphNode& node) {
    nodes[node.getId()] = node;
    if (adjacencyList.find(node.getId()) == adjacencyList.end()) {
        adjacencyList[node.getId()] = vector<GraphEdge>();
    }
}

void PuzzleGraph::addEdge(const GraphNode& from, const GraphNode& to, const string& moveDescription) {
    // Adiciona os nós se não existirem
    addNode(from);
    addNode(to);
    
    // Adiciona a aresta
    GraphEdge edge(from.getId(), to.getId(), moveDescription);
    adjacencyList[from.getId()].push_back(edge);
}

vector<GraphNode> PuzzleGraph::getNeighbors(const GraphNode& node) {
    vector<GraphNode> neighbors;
    
    if (adjacencyList.find(node.getId()) != adjacencyList.end()) {
        for (const GraphEdge& edge : adjacencyList[node.getId()]) {
            if (nodes.find(edge.getToNodeId()) != nodes.end()) {
                neighbors.push_back(nodes[edge.getToNodeId()]);
            }
        }
    }
    
    return neighbors;
}

bool PuzzleGraph::hasNode(const string& nodeId) const {
    return nodes.find(nodeId) != nodes.end();
}

GraphNode PuzzleGraph::getNode(const string& nodeId) const {
    auto it = nodes.find(nodeId);
    if (it != nodes.end()) {
        return it->second;
    }
    throw runtime_error("Nó não encontrado: " + nodeId);
}

bool PuzzleGraph::isValidMove(const GraphNode& node, int newRow, int newCol) const {
    int size = node.getSize();
    return newRow >= 0 && newRow < size && newCol >= 0 && newCol < size;
}

GraphNode PuzzleGraph::makeMove(const GraphNode& node, int newRow, int newCol) const {
    vector<vector<int>> newState = node.getState();
    auto emptyPos = node.getEmptyPosition();
    
    // Troca a posição vazia com a nova posição
    swap(newState[emptyPos.first][emptyPos.second], newState[newRow][newCol]);
    
    return GraphNode(newState);
}

vector<pair<GraphNode, string>> PuzzleGraph::generateNeighbors(const GraphNode& node) {
    vector<pair<GraphNode, string>> neighbors;
    auto emptyPos = node.getEmptyPosition();
    int emptyRow = emptyPos.first;
    int emptyCol = emptyPos.second;
    
    // Movimentos possíveis: cima, baixo, esquerda, direita
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    vector<string> moves = {"UP", "DOWN", "LEFT", "RIGHT"};
    
    for (int i = 0; i < 4; i++) {
        int newRow = emptyRow + directions[i].first;
        int newCol = emptyCol + directions[i].second;
        
        if (isValidMove(node, newRow, newCol)) {
            GraphNode neighbor = makeMove(node, newRow, newCol);
            neighbors.push_back({neighbor, moves[i]});
        }
    }
    
    return neighbors;
}

int PuzzleGraph::getEdgeCount() const {
    int count = 0;
    for (const auto& pair : adjacencyList) {
        count += pair.second.size();
    }
    return count;
}

void PuzzleGraph::printGraphInfo() const {
    cout << "=== Informações do Grafo ===" << endl;
    cout << "Número de vértices (estados): " << getNodeCount() << endl;
    cout << "Número de arestas (transições): " << getEdgeCount() << endl;
    cout << "Representação: Lista de Adjacências" << endl;
}
