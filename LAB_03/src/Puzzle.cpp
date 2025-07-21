#include "Puzzle.hpp"

#include <algorithm>
#include <cmath>
#include <sstream>
#include <iomanip>

using namespace std;

// Construtor padrão
Puzzle::Puzzle() : size(0), emptyRow(0), emptyCol(0), gCost(0), hCost(0), path("") {}

// Construtor com entrada linear
Puzzle::Puzzle(const vector<int>& input) : gCost(0), path("") {
    if (input.size() == 9) {
        size = 3;
    } else if (input.size() == 16) {
        size = 4;
    } else {
        throw invalid_argument("Entrada inválida: deve ter 9 ou 16 elementos");
    }
    
    board.resize(size, vector<int>(size));
    
    // Converte entrada linear para matriz
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = input[i * size + j];
        }
    }
    
    findEmptyPosition();
    calculateHeuristic();
}

// Construtor com matriz
Puzzle::Puzzle(const vector<vector<int>>& board, int g, const string& p) 
    : board(board), gCost(g), path(p) {
    size = board.size();
    findEmptyPosition();
    calculateHeuristic();
}

void Puzzle::findEmptyPosition() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == 0) {
                emptyRow = i;
                emptyCol = j;
                return;
            }
        }
    }
}

vector<vector<int>> Puzzle::getGoalState() const {
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

bool Puzzle::isGoal() const {
    vector<vector<int>> goal = getGoalState();
    return board == goal;
}

int Puzzle::calculateManhattanDistance() const {
    int distance = 0;
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] != 0) {
                int targetRow, targetCol;
                if (board[i][j] == size * size) {
                    targetRow = size - 1;
                    targetCol = size - 1;
                } else {
                    targetRow = (board[i][j] - 1) / size;
                    targetCol = (board[i][j] - 1) % size;
                }
                distance += abs(i - targetRow) + abs(j - targetCol);
            }
        }
    }
    
    return distance;
}

void Puzzle::calculateHeuristic() {
    hCost = calculateManhattanDistance();
}

bool Puzzle::isValidMove(int newRow, int newCol) const {
    return newRow >= 0 && newRow < size && newCol >= 0 && newCol < size;
}

Puzzle Puzzle::makeMove(int newRow, int newCol, const string& move) const {
    vector<vector<int>> newBoard = board;
    
    // Troca a posição vazia com a nova posição
    swap(newBoard[emptyRow][emptyCol], newBoard[newRow][newCol]);
    
    string newPath = path;
    if (!newPath.empty()) newPath += " ";
    newPath += move;
    
    return Puzzle(newBoard, gCost + 1, newPath);
}

vector<Puzzle> Puzzle::getNeighbors() const {
    vector<Puzzle> neighbors;
    
    // Movimentos possíveis: cima, baixo, esquerda, direita
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    vector<string> moves = {"UP", "DOWN", "LEFT", "RIGHT"};
    
    for (int i = 0; i < 4; i++) {
        int newRow = emptyRow + directions[i].first;
        int newCol = emptyCol + directions[i].second;
        
        if (isValidMove(newRow, newCol)) {
            neighbors.push_back(makeMove(newRow, newCol, moves[i]));
        }
    }
    
    return neighbors;
}

string Puzzle::toString() const {
    stringstream ss;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (j > 0) ss << " ";
            ss << board[i][j];
        }
        if (i < size - 1) ss << "\\n";
    }
    return ss.str();
}

void Puzzle::print() const {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (j > 0) cout << " ";
            cout << board[i][j];
        }
        cout << endl;
    }
}

bool Puzzle::operator==(const Puzzle& other) const {
    return board == other.board;
}

bool Puzzle::operator<(const Puzzle& other) const {
    int thisFCost = getFCost();
    int otherFCost = other.getFCost();
    
    if (thisFCost != otherFCost) {
        return thisFCost > otherFCost; // Para usar com priority_queue (min-heap)
    }
    
    return hCost > other.hCost; // Desempate pela heurística
}

size_t PuzzleHash::operator()(const Puzzle& puzzle) const {
    size_t hash = 0;
    const auto& board = puzzle.getBoard();
    int size = puzzle.getSize();
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            hash = hash * 31 + board[i][j];
        }
    }
    
    return hash;
}
