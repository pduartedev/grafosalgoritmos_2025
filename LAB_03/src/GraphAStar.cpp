#include "GraphAStar.hpp"
#include <iostream>
#include <algorithm>

GraphAStar::GraphAStar() : statesEvaluated(0), statesEnqueued(0) {}

vector<GraphNode> GraphAStar::solve(const GraphNode& initial) {
    auto startTime = chrono::high_resolution_clock::now();
    
    // Reset das estatísticas
    statesEvaluated = 0;
    statesEnqueued = 0;
    
    // Verifica se já está no estado objetivo
    if (initial.isGoal()) {
        auto endTime = chrono::high_resolution_clock::now();
        executionTime = endTime - startTime;
        return {initial};
    }
    
    // Verifica se a instância é solucionável
    if (!initial.isSolvable()) {
        cout << "=== INSTÂNCIA INSOLÚVEL ===" << endl;
        cout << "Esta configuração do puzzle não pode ser resolvida!" << endl;
        auto endTime = chrono::high_resolution_clock::now();
        executionTime = endTime - startTime;
        return {};
    }
    
    // Priority queue para o algoritmo A* (min-heap baseado no f-cost)
    priority_queue<AStarNode, vector<AStarNode>, greater<AStarNode>> openSet;
    
    // Conjuntos para controle de estados
    unordered_set<string> closedSet;
    unordered_set<string> inOpenSet;
    unordered_map<string, AStarNode> allNodes; // Para reconstruir o caminho
    
    // Adiciona o estado inicial
    int initialH = calculateHeuristic(initial);
    AStarNode initialNode(initial, 0, initialH);
    
    openSet.push(initialNode);
    inOpenSet.insert(initial.getId());
    allNodes[initial.getId()] = initialNode;
    statesEnqueued++;
    
    cout << "=== Iniciando busca A* no grafo de estados ===" << endl;
    cout << "Estado inicial (Vértice): " << initial.getId() << endl;
    cout << "Heurística inicial (Manhattan): " << initial.calculateManhattanDistance() << endl;
    cout << "Heurística avançada (Manhattan + Linear Conflicts): " << initialH << endl;
    cout << "Instância solucionável: " << (initial.isSolvable() ? "SIM" : "NÃO") << endl << endl;
    
    const int MAX_STATES = (initial.getSize() == 3) ? 500000 : 5000000; // 5M para 15-puzzle, 500k para 8-puzzle
    int progressCounter = 0;
    
    while (!openSet.empty() && statesEvaluated < MAX_STATES) {
        // Pega o nó com menor f-cost (vértice mais promissor)
        AStarNode current = openSet.top();
        openSet.pop();
        
        // Remove do conjunto de estados abertos
        inOpenSet.erase(current.graphNode.getId());
        
        // Adiciona ao conjunto de estados fechados (vértices visitados)
        closedSet.insert(current.graphNode.getId());
        statesEvaluated++;
        
        // Feedback de progresso a cada 1000 estados
        if (++progressCounter % 1000 == 0) {
            cout << "Progresso: " << statesEvaluated << " vértices avaliados, " 
                 << "f-cost atual: " << current.gCost + current.hCost << endl;
        }
        closedSet.insert(current.graphNode.getId());
        statesEvaluated++;
        
        // Verifica se chegou ao objetivo
        if (current.graphNode.isGoal()) {
            auto endTime = chrono::high_resolution_clock::now();
            executionTime = endTime - startTime;
            
            cout << "=== Solução encontrada! ===" << endl;
            cout << "Vértice objetivo: " << current.graphNode.getId() << endl;
            cout << "Custo da solução: " << current.gCost << endl;
            
            return reconstructPath(current, allNodes);
        }
        
        // Gera vizinhos dinamicamente (explora arestas do grafo)
        vector<pair<GraphNode, string>> neighbors = graph.generateNeighbors(current.graphNode);
        
        for (const auto& neighborPair : neighbors) {
            GraphNode neighbor = neighborPair.first;
            string moveUsed = neighborPair.second;
            
            // Ignora se já foi visitado (vértice já no conjunto fechado)
            if (closedSet.find(neighbor.getId()) != closedSet.end()) {
                continue;
            }
            
            int tentativeG = current.gCost + 1; // Custo da aresta é sempre 1
            int h = calculateHeuristic(neighbor);
            
            // Se não está na lista aberta ou encontramos um caminho melhor
            bool inOpen = inOpenSet.find(neighbor.getId()) != inOpenSet.end();
            bool betterPath = false;
            
            if (inOpen) {
                // Verifica se encontramos um caminho melhor
                auto it = allNodes.find(neighbor.getId());
                if (it != allNodes.end() && tentativeG < it->second.gCost) {
                    betterPath = true;
                }
            }
            
            if (!inOpen || betterPath) {
                AStarNode neighborNode(neighbor, tentativeG, h, 
                                      current.graphNode.getId(), moveUsed);
                
                if (!inOpen) {
                    openSet.push(neighborNode);
                    inOpenSet.insert(neighbor.getId());
                    statesEnqueued++;
                }
                
                allNodes[neighbor.getId()] = neighborNode;
                
                // Adiciona aresta ao grafo (para visualização/debug)
                graph.addEdge(current.graphNode, neighbor, moveUsed);
            }
        }
        
        // Debug: mostra progresso a cada 1000 estados avaliados
        if (statesEvaluated % 1000 == 0) {
            cout << "Estados avaliados: " << statesEvaluated 
                 << ", Estados enfileirados: " << statesEnqueued 
                 << ", F-cost atual: " << current.getFCost() << endl;
        }
    }
    
    auto endTime = chrono::high_resolution_clock::now();
    executionTime = endTime - startTime;
    
    cout << "=== Solução não encontrada ===" << endl;
    return {};
}

vector<GraphNode> GraphAStar::reconstructPath(const AStarNode& goalNode, 
                                             const unordered_map<string, AStarNode>& allNodes) {
    vector<GraphNode> path;
    string currentId = goalNode.graphNode.getId();
    
    // Reconstroi o caminho seguindo os pais
    while (!currentId.empty()) {
        auto it = allNodes.find(currentId);
        if (it != allNodes.end()) {
            path.push_back(it->second.graphNode);
            currentId = it->second.parentId;
        } else {
            break;
        }
    }
    
    // Inverte para ter o caminho do início ao fim
    reverse(path.begin(), path.end());
    
    cout << "Caminho no grafo (sequência de vértices): ";
    for (size_t i = 0; i < path.size(); i++) {
        if (i > 0) cout << " -> ";
        cout << "V" << i;
    }
    cout << endl;
    
    return path;
}

// Versão silenciosa da reconstrução do caminho (para processamento em lote)
vector<GraphNode> GraphAStar::reconstructPathSilent(const AStarNode& goalNode, 
                                                   const unordered_map<string, AStarNode>& allNodes) {
    vector<GraphNode> path;
    string currentId = goalNode.graphNode.getId();
    
    // Reconstrói o caminho seguindo os parentIds
    while (!currentId.empty()) {
        auto it = allNodes.find(currentId);
        if (it != allNodes.end()) {
            path.push_back(it->second.graphNode);
            currentId = it->second.parentId;
        } else {
            break;
        }
    }
    
    // Inverte para ter o caminho do início ao fim
    reverse(path.begin(), path.end());
    
    return path;
}

int GraphAStar::calculateHeuristic(const GraphNode& node) {
    return node.calculateAdvancedHeuristic();
}

void GraphAStar::printStatistics() const {
    cerr << "Tempo de execução: " << executionTime.count() << " segundos" << endl;
    cerr << "Estados avaliados: " << statesEvaluated << endl;
    cerr << "Estados enfileirados: " << statesEnqueued << endl;
}

// Versão silenciosa para processamento em lote
vector<GraphNode> GraphAStar::solveSilent(const GraphNode& initial) {
    auto startTime = chrono::high_resolution_clock::now();
    
    // Reset das estatísticas
    statesEvaluated = 0;
    statesEnqueued = 0;
    graph = PuzzleGraph(); // Reset do grafo
    
    // Verifica se a instância é solucionável
    if (!initial.isSolvable()) {
        auto endTime = chrono::high_resolution_clock::now();
        executionTime = endTime - startTime;
        return {};
    }
    
    // Priority queue para o algoritmo A* (min-heap baseado no f-cost)
    priority_queue<AStarNode, vector<AStarNode>, greater<AStarNode>> openSet;
    
    // Conjuntos para controle de estados
    unordered_set<string> closedSet;
    unordered_set<string> inOpenSet;
    unordered_map<string, AStarNode> allNodes; // Para reconstruir o caminho
    
    // Adiciona o estado inicial
    int initialH = calculateHeuristic(initial);
    AStarNode initialNode(initial, 0, initialH);
    
    openSet.push(initialNode);
    inOpenSet.insert(initial.getId());
    allNodes[initial.getId()] = initialNode;
    statesEnqueued++;
    
    const int MAX_STATES = (initial.getSize() == 3) ? 500000 : 5000000; // 5M para 15-puzzle, 500k para 8-puzzle
    const int size = initial.getSize(); // Tamanho do puzzle (3 para 8-puzzle, 4 para 15-puzzle)
    
    while (!openSet.empty() && statesEvaluated < MAX_STATES) {
        // Pega o nó com menor f-cost (vértice mais promissor)
        AStarNode current = openSet.top();
        openSet.pop();
        
        // Remove do conjunto de estados abertos
        inOpenSet.erase(current.graphNode.getId());
        
        // Adiciona ao conjunto de estados fechados (vértices visitados)
        closedSet.insert(current.graphNode.getId());
        statesEvaluated++;
        
        // Verifica se chegou ao objetivo
        if (current.graphNode.isGoal()) {
            auto endTime = chrono::high_resolution_clock::now();
            executionTime = endTime - startTime;
            return reconstructPathSilent(current, allNodes);
        }
        
        // Gera vizinhos (arestas do grafo)
        vector<pair<GraphNode, string>> neighbors = graph.generateNeighbors(current.graphNode);
        
        for (const auto& neighborPair : neighbors) {
            const GraphNode& neighbor = neighborPair.first;
            const string& move = neighborPair.second;
            
            // Ignora se já foi avaliado (vértice já visitado)
            if (closedSet.find(neighbor.getId()) != closedSet.end()) {
                continue;
            }
            
            // Adiciona aresta ao grafo
            graph.addEdge(current.graphNode, neighbor, move);
            
            int neighborG = current.gCost + 1;
            int neighborH = calculateHeuristic(neighbor);
            AStarNode neighborNode(neighbor, neighborG, neighborH, current.graphNode.getId(), move);
            
            // Se não está na lista aberta ou encontrou caminho melhor
            if (inOpenSet.find(neighbor.getId()) == inOpenSet.end()) {
                // Para 15-puzzle, verifica se já está em closedSet para economizar memória
                if (size == 4 && closedSet.find(neighbor.getId()) != closedSet.end()) {
                    continue;
                }
                
                openSet.push(neighborNode);
                inOpenSet.insert(neighbor.getId());
                allNodes[neighbor.getId()] = neighborNode;
                statesEnqueued++;
            }
        }
    }
    
    auto endTime = chrono::high_resolution_clock::now();
    executionTime = endTime - startTime;
    
    // Não encontrou solução
    return {};
}
