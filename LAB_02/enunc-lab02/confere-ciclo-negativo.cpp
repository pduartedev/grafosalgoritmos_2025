#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>      // std::priority_queue
#include <functional> // greater
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char *argv[])
{
  ifstream grafo_arq(argv[1]);
  ifstream ciclo_arq(argv[2]);

  int n, m;

  grafo_arq >> n >> m;

  vector<vector<pair<int, int>>> G(n);

  for (int i = 0; i < m; ++i)
  {
    int x, y, c;

    grafo_arq >> x >> y >> c;

    G[x].push_back({y, c});
  }

  vector<int> ciclo;
  int x;
  string S;
  ciclo_arq >> S >> S >> S;

  while (ciclo_arq >> x)
  {
    ciclo.push_back(x);
  }

  int custo = 0;

  for (int i = 0; i < ciclo.size(); ++i)
  {
    int v = ciclo[i];
    int w = ciclo[(i + 1) % ciclo.size()];
    auto it = ranges::find(G[v], w, &pair<int, int>::first);

    if (it == G[v].end())
    {
      cout << "Erro: Aresta não encontrada." << endl;
      return 1;
    }
    custo += it->second;
  }

  cout << "Custo=" << custo << endl;

  if (custo >= 0)
  {
    cout << "Erro: Ciclo não negativo." << endl;
  }

  cout << "OK." << endl;

  return 0;
}
