#include "Grafo.hpp"

using namespace std;

// Implementação do construtor da classe Grafo.
Grafo::Grafo(int n_vertices) : num_vertices(n_vertices), lista_adj(n_vertices) {}

// Implementação do método para adicionar arestas.
void Grafo::adicionar_aresta(int de, int para, int capacidade, int custo)
{
    // Cria a aresta de ida (original)
    Aresta aresta_ida = {para, capacidade, custo, 0, (int)lista_adj[para].size()};

    // Cria a aresta de volta (residual), que inicialmente não tem fluxo nem capacidade.
    // O custo é negativo para que o algoritmo possa "desfazer" um fluxo se encontrar um caminho mais barato.
    Aresta aresta_volta = {de, 0, -custo, 0, (int)lista_adj[de].size()};

    lista_adj[de].push_back(aresta_ida);
    lista_adj[para].push_back(aresta_volta);
}

// Implementação do método para obter o número de vértices.
int Grafo::obter_numero_vertices() const
{
    return num_vertices;
}

// Implementação do operador [] para acesso não-constante.
vector<Aresta> &Grafo::operator[](int vertice)
{
    return lista_adj[vertice];
}

// Implementação do operador [] para acesso constante.
const vector<Aresta> &Grafo::operator[](int vertice) const
{
    return lista_adj[vertice];
}