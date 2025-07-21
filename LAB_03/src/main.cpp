#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "AStar.hpp"
#include "Puzzle.hpp"

using namespace std;

vector<int> readInput() {
    vector<int> input;
    string line;
    
    // Lê uma linha de entrada
    if (getline(cin, line)) {
        istringstream iss(line);
        int number;
        
        // Extrai todos os números da linha
        while (iss >> number) {
            input.push_back(number);
        }
    }
    
    return input;
}

vector<int> readInputFromFile(const string& filename) {
    vector<int> input;
    ifstream file(filename);
    
    if (!file.is_open()) {
        cerr << "Erro: Não foi possível abrir o arquivo " << filename << endl;
        return input;
    }
    
    string line;
    if (getline(file, line)) {
        istringstream iss(line);
        int number;
        
        while (iss >> number) {
            input.push_back(number);
        }
    }
    
    file.close();
    return input;
}

void printSolution(const vector<Puzzle>& solution) {
    if (solution.empty()) {
        cout << "Não foi possível encontrar uma solução." << endl;
        return;
    }
    
    // Imprime o número de passos (número de estados - 1)
    int steps = solution.size() - 1;
    cout << steps << endl << endl;
    
    // Imprime cada estado da solução separado por linha em branco
    for (size_t i = 0; i < solution.size(); i++) {
        solution[i].print();
        if (i < solution.size() - 1) {
            cout << endl;
        }
    }
}

int main(int argc, char* argv[]) {
    try {
        vector<int> input;
        
        // Verifica se foi passado um arquivo como argumento
        if (argc > 1) {
            input = readInputFromFile(argv[1]);
        } else {
            input = readInput();
        }
        
        // Verifica se a entrada é válida
        if (input.size() != 9 && input.size() != 16) {
            cerr << "Erro: Entrada deve conter 9 números (8-puzzle) ou 16 números (15-puzzle)" << endl;
            return 1;
        }
        
        // Cria o puzzle inicial
        Puzzle initialPuzzle(input);
        
        // Cria o solver A*
        AStar solver;
        
        // Resolve o puzzle
        vector<Puzzle> solution = solver.solve(initialPuzzle);
        
        // Imprime as estatísticas na saída de erro
        solver.printStatistics();
        
        // Imprime a solução na saída padrão
        printSolution(solution);
        
        if (solution.empty()) {
            return 1; // Indica que não foi encontrada solução
        }
        
    } catch (const exception& e) {
        cerr << "Erro: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
