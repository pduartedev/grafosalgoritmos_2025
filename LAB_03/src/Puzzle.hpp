#pragma once

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Puzzle {
private:
    vector<vector<int>> board;
    int size;
    int emptyRow, emptyCol;
    int gCost; // Custo do caminho desde o início
    int hCost; // Heurística (Manhattan distance)
    string path; // Sequência de movimentos

public:
    // Construtores
    Puzzle();
    Puzzle(const vector<int>& input);
    Puzzle(const vector<vector<int>>& board, int g = 0, const string& p = "");
    
    // Getters
    const vector<vector<int>>& getBoard() const { return board; }
    int getSize() const { return size; }
    int getGCost() const { return gCost; }
    int getHCost() const { return hCost; }
    int getFCost() const { return gCost + hCost; }
    string getPath() const { return path; }
    pair<int, int> getEmptyPosition() const { return {emptyRow, emptyCol}; }
    
    // Setters
    void setGCost(int g) { gCost = g; }
    void setPath(const string& p) { path = p; }
    
    // Métodos principais
    bool isGoal() const;
    vector<Puzzle> getNeighbors() const;
    int calculateManhattanDistance() const;
    string toString() const;
    void print() const;
    
    // Operadores
    bool operator==(const Puzzle& other) const;
    bool operator<(const Puzzle& other) const;
    
private:
    void findEmptyPosition();
    void calculateHeuristic();
    vector<vector<int>> getGoalState() const;
    bool isValidMove(int newRow, int newCol) const;
    Puzzle makeMove(int newRow, int newCol, const string& move) const;
};

// Estrutura para usar como chave no unordered_set
struct PuzzleHash {
    size_t operator()(const Puzzle& puzzle) const;
};
