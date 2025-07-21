#include "GraphAStar.hpp"
#include "PuzzleGraph.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <streambuf>

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

// Nova função para processar múltiplas instâncias
void processBatchFile(const string& filename) {
    ifstream file(filename);
    
    if (!file.is_open()) {
        cerr << "Erro: Não foi possível abrir o arquivo " << filename << endl;
        return;
    }
    
    string line;
    int instanceCount = 0;
    double totalTime = 0.0;
    int totalStatesEvaluated = 0;
    int totalStatesEnqueued = 0;
    int solvedCount = 0;
    int unsolvableCount = 0;
    
    cout << "=== PROCESSAMENTO EM LOTE DE INSTÂNCIAS PUZZLE ===" << endl;
    cout << "Arquivo: " << filename << endl << endl;
    
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        instanceCount++;
        vector<int> input;
        istringstream iss(line);
        int number;
        
        // Lê números da linha
        while (iss >> number) {
            input.push_back(number);
        }
        
        if (input.size() != 9 && input.size() != 16) {
            cout << "Instância " << instanceCount << ": FORMATO INVÁLIDO (esperado 9 ou 16 números)" << endl;
            continue;
        }
        
        try {
            // Cria o puzzle inicial
            GraphNode initialPuzzle(input);
            
            // Verifica solvabilidade
            if (!initialPuzzle.isSolvable()) {
                cout << "Instância " << instanceCount << ": INSOLÚVEL" << endl;
                unsolvableCount++;
                continue;
            }
            
            // Cria o solver A*
            GraphAStar solver;
            
            // Resolve o puzzle (modo silencioso para lote)
            vector<GraphNode> solution = solver.solveSilent(initialPuzzle);
            
            if (!solution.empty()) {
                cout << "Instância " << instanceCount << ": RESOLVIDA em " 
                     << (solution.size() - 1) << " passos | "
                     << "Tempo: " << fixed << setprecision(6) << solver.getExecutionTime() << "s | "
                     << "Vértices: " << solver.getStatesEvaluated() << " | "
                     << "Enfileirados: " << solver.getStatesEnqueued() << endl;
                
                totalTime += solver.getExecutionTime();
                totalStatesEvaluated += solver.getStatesEvaluated();
                totalStatesEnqueued += solver.getStatesEnqueued();
                solvedCount++;
            } else {
                cout << "Instância " << instanceCount << ": FALHA NA RESOLUÇÃO" << endl;
            }
            
        } catch (const exception& e) {
            cout << "Instância " << instanceCount << ": ERRO - " << e.what() << endl;
        }
    }
    
    file.close();
    
    // Estatísticas finais
    cout << endl << "=== ESTATÍSTICAS FINAIS ===" << endl;
    cout << "Total de instâncias processadas: " << instanceCount << endl;
    cout << "Instâncias resolvidas: " << solvedCount << endl;
    cout << "Instâncias insolúveis: " << unsolvableCount << endl;
    cout << "Taxa de sucesso: " << fixed << setprecision(1) 
         << (instanceCount > 0 ? (double)solvedCount / instanceCount * 100 : 0) << "%" << endl;
    
    if (solvedCount > 0) {
        cout << "Tempo médio por instância: " << fixed << setprecision(6)
             << totalTime / solvedCount << "s" << endl;
        cout << "Vértices médios avaliados: " << totalStatesEvaluated / solvedCount << endl;
        cout << "Vértices médios enfileirados: " << totalStatesEnqueued / solvedCount << endl;
    }
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

int main(int argc, char* argv[]) {
    try {
        // Verifica se foi passado argumento de linha de comando
        if (argc > 1) {
            string filename = argv[1];
            
            // Verifica se é o modo em lote (arquivo com múltiplas instâncias)
            if (argc > 2 && string(argv[2]) == "--batch") {
                processBatchFile(filename);
                return 0;
            }
            
            // Modo single - processa apenas uma instância do arquivo
            vector<int> input = readInputFromFile(filename);
            
            // Verifica se a entrada é válida
            if (input.size() != 9 && input.size() != 16) {
                cerr << "Erro: Entrada deve conter 9 números (8-puzzle) ou 16 números (15-puzzle)" << endl;
                return 1;
            }
            
            // Cria o nó inicial do grafo
            GraphNode initialNode(input);
            
            // Cria o solver A* orientado a grafos
            GraphAStar solver;
            
            // Resolve o puzzle usando busca no grafo (modo silencioso)
            vector<GraphNode> solution = solver.solveSilent(initialNode);
            
            // Imprime as estatísticas obrigatórias na saída de erro (conforme enunciado)
            solver.printStatistics();
            
            // Imprime APENAS a solução na saída padrão (conforme enunciado)
            printSolution(solution);
            
            if (solution.empty()) {
                return 1; // Indica que não foi encontrada solução
            }
            
        } else {
            // Modo stdin - lê da entrada padrão
            vector<int> input = readInput();
            
            // Verifica se a entrada é válida
            if (input.size() != 9 && input.size() != 16) {
                cerr << "Erro: Entrada deve conter 9 números (8-puzzle) ou 16 números (15-puzzle)" << endl;
                return 1;
            }
            
            // Cria o nó inicial do grafo
            GraphNode initialNode(input);
            
            // Cria o solver A* orientado a grafos
            GraphAStar solver;
            
            // Resolve o puzzle usando busca no grafo (modo silencioso)
            vector<GraphNode> solution = solver.solveSilent(initialNode);
            
            // Imprime as estatísticas obrigatórias na saída de erro (conforme enunciado)
            solver.printStatistics();
            
            // Imprime APENAS a solução na saída padrão (conforme enunciado)
            printSolution(solution);
            
            if (solution.empty()) {
                return 1; // Indica que não foi encontrada solução
            }
        }
        
    } catch (const exception& e) {
        cerr << "Erro: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
