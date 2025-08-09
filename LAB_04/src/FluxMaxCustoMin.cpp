#include "FluxMaxCustoMin.hpp"
#include <queue>     // Para a fila de prioridade do Dijkstra
#include <vector>    // Para os vetores auxiliares
#include <limits>    // Para numeric_limits
#include <algorithm> // Para min e sort

using namespace std;

// Construtor da classe.
FluxoCustoMinimo::FluxoCustoMinimo(Grafo &grafo) : grafo(grafo) {}

// Método principal que executa o algoritmo.
pair<int, int> FluxoCustoMinimo::executar(int fonte, int sorvedouro)
{
    int fluxo_maximo = 0;
    int custo_minimo = 0;
    // Inicializa os potenciais de todos os vértices com 0.
    potencial.assign(grafo.obter_numero_vertices(), 0);

    // Loop principal: continua enquanto Dijkstra encontrar um caminho aumentante de menor custo.
    while (dijkstra(fonte, sorvedouro))
    {
        // Após encontrar um caminho, atualiza os potenciais dos vértices.
        // Isso é crucial para manter os custos das arestas não-negativos nas próximas iterações.
        for (int i = 0; i < grafo.obter_numero_vertices(); ++i)
        {
            if (distancia[i] != numeric_limits<int>::max())
            {
                potencial[i] += distancia[i];
            }
        }

        // Encontra a capacidade gargalo (o máximo de fluxo que podemos enviar) no caminho encontrado.
        int fluxo_a_enviar = numeric_limits<int>::max();
        for (int v = sorvedouro; v != fonte; v = pai_vertice[v])
        {
            fluxo_a_enviar = min(fluxo_a_enviar, grafo[pai_vertice[v]][pai_aresta[v]].capacidade - grafo[pai_vertice[v]][pai_aresta[v]].fluxo);
        }

        // Aumenta o fluxo ao longo do caminho (e diminui nas arestas reversas).
        for (int v = sorvedouro; v != fonte; v = pai_vertice[v])
        {
            Aresta &aresta = grafo[pai_vertice[v]][pai_aresta[v]];
            aresta.fluxo += fluxo_a_enviar;
            grafo[v][aresta.aresta_reversa].fluxo -= fluxo_a_enviar;
        }

        // Atualiza o fluxo máximo e o custo mínimo total.
        fluxo_maximo += fluxo_a_enviar;
        custo_minimo += fluxo_a_enviar * potencial[sorvedouro];
    }

    return {fluxo_maximo, custo_minimo};
}

// Implementação do Dijkstra com potenciais.
bool FluxoCustoMinimo::dijkstra(int fonte, int sorvedouro)
{
    distancia.assign(grafo.obter_numero_vertices(), numeric_limits<int>::max());
    pai_vertice.assign(grafo.obter_numero_vertices(), -1);
    pai_aresta.assign(grafo.obter_numero_vertices(), -1);
    distancia[fonte] = 0;

    // Fila de prioridade para o Dijkstra: armazena {distância, vértice}.
    using Estado = pair<int, int>;
    priority_queue<Estado, vector<Estado>, greater<Estado>> fila_prioridade;
    fila_prioridade.push({0, fonte});

    while (!fila_prioridade.empty())
    {
        auto [dist_atual, vertice_atual] = fila_prioridade.top();
        fila_prioridade.pop();

        if (dist_atual > distancia[vertice_atual])
        {
            continue; // Otimização: já encontramos um caminho melhor para este vértice.
        }

        // Explora os vizinhos do vértice atual.
        for (size_t i = 0; i < grafo[vertice_atual].size(); ++i)
        {
            Aresta &aresta = grafo[vertice_atual][i];

            // Calcula o custo reduzido usando os potenciais.
            int custo_reduzido = aresta.custo + potencial[vertice_atual] - potencial[aresta.para];

            // Se a aresta tem capacidade residual e encontramos um caminho mais curto...
            if (aresta.capacidade - aresta.fluxo > 0 && distancia[aresta.para] > distancia[vertice_atual] + custo_reduzido)
            {
                distancia[aresta.para] = distancia[vertice_atual] + custo_reduzido;
                pai_vertice[aresta.para] = vertice_atual;
                pai_aresta[aresta.para] = i;
                fila_prioridade.push({distancia[aresta.para], aresta.para});
            }
        }
    }

    // Retorna true se o sorvedouro foi alcançado, false caso contrário.
    return distancia[sorvedouro] != numeric_limits<int>::max();
}

// Encontra o corte mínimo após o algoritmo de fluxo ter sido executado.
vector<int> FluxoCustoMinimo::obter_corte_minimo(int fonte)
{
    vector<int> vertices_alcancaveis;
    vector<bool> visitado(grafo.obter_numero_vertices(), false);
    queue<int> fila; // Usando uma fila para fazer uma busca em largura (BFS)

    fila.push(fonte);
    visitado[fonte] = true;

    while (!fila.empty())
    {
        int vertice_atual = fila.front();
        fila.pop();
        vertices_alcancaveis.push_back(vertice_atual);

        // Itera sobre os vizinhos no grafo residual.
        for (const auto &aresta : grafo[vertice_atual])
        {
            // Se o vizinho não foi visitado e ainda há capacidade na aresta...
            if (!visitado[aresta.para] && aresta.capacidade - aresta.fluxo > 0)
            {
                visitado[aresta.para] = true;
                fila.push(aresta.para);
            }
        }
    }

    // Ordena os vértices para a saída, conforme solicitado.
    sort(vertices_alcancaveis.begin(), vertices_alcancaveis.end());
    return vertices_alcancaveis;
}