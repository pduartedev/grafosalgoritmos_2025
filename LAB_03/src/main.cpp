#include "GraphAStar.hpp"
#include "PuzzleGraph.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

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

void printSolution(const vector<GraphNode>& solution) {
    if (solution.empty()) {
        cout << "Não foi possível encontrar uma solução." << endl;
        return;
    }
    
    // Imprime o número de passos (número de vértices - 1)
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

void printPuzzleAsGraph(const GraphNode& initial) {
    cout << "=== Modelagem do Problema como Grafo ===" << endl;
    cout << "• Cada VÉRTICE representa uma configuração do puzzle" << endl;
    cout << "• Cada ARESTA representa um movimento válido (custo = 1)" << endl;
    cout << "• O problema é encontrar o menor caminho no grafo de estados" << endl;
    cout << "• Algoritmo: A* com heurística de Manhattan" << endl;
    cout << "• Representação: Lista de Adjacências (gerada dinamicamente)" << endl;
    cout << endl;
    
    cout << "Vértice inicial (configuração): " << endl;
    initial.print();
    cout << "ID do vértice: " << initial.getId() << endl;
    cout << "Heurística (distância ao objetivo): " << initial.calculateManhattanDistance() << endl;
    cout << endl;
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
        
        // Cria o nó inicial do grafo
        GraphNode initialNode(input);
        
        // Mostra como o problema é modelado como grafo
        printPuzzleAsGraph(initialNode);
        
        // Cria o solver A* orientado a grafos
        GraphAStar solver;
        
        // Resolve o puzzle usando busca no grafo
        vector<GraphNode> solution = solver.solve(initialNode);
        
        // Imprime as estatísticas na saída de erro
        solver.printStatistics();
        
        // Imprime informações do grafo construído
        cout << endl;
        solver.getGraph().printGraphInfo();
        cout << endl;
        
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
