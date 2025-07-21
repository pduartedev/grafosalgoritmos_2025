#pragma once

#include <queue>
#include <unordered_set>
#include <vector>
#include <chrono>
#include <map>

#include "Puzzle.hpp"

using namespace std;

class AStar
{
private:
    int statesEvaluated;
    int statesEnqueued;
    chrono::duration<double> executionTime;

public:
    AStar();

    // Método principal para resolver o puzzle
    vector<Puzzle> solve(const Puzzle &initial);

    // Getters para estatísticas
    int getStatesEvaluated() const { return statesEvaluated; }
    int getStatesEnqueued() const { return statesEnqueued; }
    double getExecutionTime() const { return executionTime.count(); }

    // Método para imprimir estatísticas
    void printStatistics() const;

private:
    // Reconstroi o caminho da solução
    vector<Puzzle> reconstructPath(const Puzzle &goal,
                                   const map<Puzzle, Puzzle> &cameFrom,
                                   const Puzzle &initial);

    // Verifica se um estado já foi visitado
    bool isVisited(const Puzzle &puzzle, const unordered_set<Puzzle, PuzzleHash> &visited) const;
};
