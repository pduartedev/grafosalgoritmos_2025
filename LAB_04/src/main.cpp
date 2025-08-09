// Implementação do algoritmo de Fluxo Máximo com Custo Mínimo
// Autor: Patrick DUARTE Pimenta

#include <iostream>  // Para entrada e saída (cin, cout)
#include <vector>    // Para vector
#include <iomanip>   // Para formatação de saída (não usado, mas bom ter)
#include <algorithm> // Para sort

#include "Grafo.hpp"           // Inclui a definição da nossa classe de Grafo
#include "FluxMaxCustoMin.hpp" // Inclui a definição da nossa classe de solução

using namespace std;

// Estrutura simples para armazenar os dados das arestas originais,
// para que possamos reimprimi-las no final na ordem correta.
struct ArestaOriginal
{
    int de, para, capacidade, custo;
};

int main()
{
    // Otimização para acelerar a leitura e escrita de dados.
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n_vertices, n_arestas;
    cin >> n_vertices >> n_arestas;

    Grafo grafo(n_vertices);
    vector<ArestaOriginal> arestas_originais;
    arestas_originais.reserve(n_arestas); // Pré-aloca memória para eficiência

    // Loop para ler todas as arestas da entrada.
    for (int i = 0; i < n_arestas; ++i)
    {
        int de, para, cap, custo;
        cin >> de >> para >> cap >> custo;
        grafo.adicionar_aresta(de, para, cap, custo);
        arestas_originais.push_back({de, para, cap, custo});
    }

    // Define a fonte (s) e o sorvedouro (t) conforme especificado no problema.
    int fonte = 0, sorvedouro = n_vertices - 1;

    // Cria o objeto que resolverá o problema.
    FluxoCustoMinimo solucionador(grafo);

    // Executa o algoritmo e obtém o resultado.
    auto [fluxo_maximo, custo_minimo] = solucionador.executar(fonte, sorvedouro);

    // --- INÍCIO DA SAÍDA ---

    // 1. Imprime o valor do fluxo máximo.
    cout << fluxo_maximo << endl;

    // 2. Imprime o custo total do fluxo de custo mínimo.
    cout << custo_minimo << endl;

    // 3. Encontra e imprime os vértices do corte mínimo.
    vector<int> vertices_corte_minimo = solucionador.obter_corte_minimo(fonte);
    cout << vertices_corte_minimo.size() << "    "; // Imprime o tamanho e 4 espaços
    for (size_t i = 0; i < vertices_corte_minimo.size(); ++i)
    {
        cout << vertices_corte_minimo[i] << (i == vertices_corte_minimo.size() - 1 ? "" : " ");
    }
    cout << endl;

    // 4. Imprime o fluxo em cada uma das arestas originais.
    for (const auto &aresta_original : arestas_originais)
    {
        int valor_fluxo = 0;
        // Procura a aresta correspondente no grafo para obter o valor do fluxo final.
        // A busca é necessária porque a ordem na lista de adjacências pode não ser a mesma da entrada.
        for (const auto &aresta : grafo[aresta_original.de])
        {
            if (aresta.para == aresta_original.para && aresta.custo == aresta_original.custo)
            {
                valor_fluxo = aresta.fluxo;
                break;
            }
        }
        cout << aresta_original.de << " " << aresta_original.para << " " << aresta_original.capacidade << " " << aresta_original.custo << " -> " << valor_fluxo << endl;
    }

    return 0;
}