#pragma once

#include <vector>

using namespace std;

// Estrutura para representar uma aresta (ou arco) no grafo.
struct Aresta
{
    int para;           // Vértice de destino do arco
    int capacidade;     // Capacidade máxima do arco
    int custo;          // Custo para enviar uma unidade de fluxo pelo arco
    int fluxo;          // Fluxo atual que passa pelo arco
    int aresta_reversa; // Índice da aresta reversa na lista de adjacência do vértice de destino
};

// Classe para representar o grafo direcionado usado no problema de fluxo.
class Grafo
{
public:
    // Construtor: inicializa o grafo com 'n_vertices' vértices.
    Grafo(int n_vertices);

    // Adiciona um arco direcionado de 'de' para 'para' com capacidade e custo.
    // Este método também cria a aresta residual reversa correspondente.
    void adicionar_aresta(int de, int para, int capacidade, int custo);

    // Retorna o número total de vértices no grafo.
    int obter_numero_vertices() const;

    // Sobrecarga do operador [] para permitir acesso direto à lista de adjacências de um vértice.
    vector<Aresta> &operator[](int vertice);
    const vector<Aresta> &operator[](int vertice) const;

private:
    int num_vertices;                 // Número de vértices
    vector<vector<Aresta>> lista_adj; // Lista de adjacências para representar o grafo
};