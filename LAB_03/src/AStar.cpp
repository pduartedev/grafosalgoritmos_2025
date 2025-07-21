#include "AStar.hpp"

#include <iostream>
#include <algorithm>
#include <sstream>
#include <map>

using namespace std;

AStar::AStar() : statesEvaluated(0), statesEnqueued(0) {}

vector<Puzzle> AStar::solve(const Puzzle &initial)
{
    auto startTime = chrono::high_resolution_clock::now();

    // Reset das estatísticas
    statesEvaluated = 0;
    statesEnqueued = 0;

    // Verifica se já está no estado objetivo
    if (initial.isGoal())
    {
        auto endTime = chrono::high_resolution_clock::now();
        executionTime = endTime - startTime;
        return {initial};
    }

    // Priority queue para o algoritmo A* (min-heap baseado no f-cost)
    priority_queue<Puzzle> openSet;
    unordered_set<Puzzle, PuzzleHash> closedSet;
    unordered_set<Puzzle, PuzzleHash> inOpenSet;
    map<Puzzle, Puzzle> cameFrom; // Para reconstruir o caminho

    openSet.push(initial);
    inOpenSet.insert(initial);
    statesEnqueued++;

    while (!openSet.empty())
    {
        // Pega o estado com menor f-cost
        Puzzle current = openSet.top();
        openSet.pop();

        // Remove do conjunto de estados abertos
        inOpenSet.erase(current);

        // Adiciona ao conjunto de estados fechados
        closedSet.insert(current);
        statesEvaluated++;

        // Verifica se chegou ao objetivo
        if (current.isGoal())
        {
            auto endTime = chrono::high_resolution_clock::now();
            executionTime = endTime - startTime;
            return reconstructPath(current, cameFrom, initial);
        }

        // Gera vizinhos
        vector<Puzzle> neighbors = current.getNeighbors();

        for (Puzzle &neighbor : neighbors)
        {
            // Ignora se já foi avaliado
            if (closedSet.find(neighbor) != closedSet.end())
            {
                continue;
            }

            // Se não está na lista aberta, adiciona
            if (inOpenSet.find(neighbor) == inOpenSet.end())
            {
                openSet.push(neighbor);
                inOpenSet.insert(neighbor);
                cameFrom[neighbor] = current;
                statesEnqueued++;
            }
        }
    }

    auto endTime = chrono::high_resolution_clock::now();
    executionTime = endTime - startTime;

    // Não encontrou solução
    return {};
}

vector<Puzzle> AStar::reconstructPath(const Puzzle &goal,
                                      const map<Puzzle, Puzzle> &cameFrom,
                                      const Puzzle &initial)
{
    vector<Puzzle> path;
    Puzzle current = goal;

    // Reconstroi o caminho de trás para frente
    while (!(current == initial))
    {
        path.push_back(current);
        auto it = cameFrom.find(current);
        if (it != cameFrom.end())
        {
            current = it->second;
        }
        else
        {
            break;
        }
    }
    path.push_back(initial);

    // Inverte para ter o caminho do início ao fim
    reverse(path.begin(), path.end());

    return path;
}

bool AStar::isVisited(const Puzzle &puzzle, const unordered_set<Puzzle, PuzzleHash> &visited) const
{
    return visited.find(puzzle) != visited.end();
}

void AStar::printStatistics() const
{
    cerr << "Tempo de execução: " << executionTime.count() << " segundos" << endl;
    cerr << "Estados avaliados: " << statesEvaluated << endl;
    cerr << "Estados enfileirados: " << statesEnqueued << endl;
}
