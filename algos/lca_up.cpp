#include <iostream>
#include <vector>

using namespace std;

int n, root;
vector <bool> used;
vector <int> depth, parent;
vector <vector <int>> g;
vector <int> lg;
vector <vector <int>> up;

void dfs(int v) {
  used[v] = true;
  for (int u : g[v])
    if (!used[u]) {
      parent[u] = v;
      depth[u] = depth[v] + 1;
      dfs(u);
    }
}

int lca(int u, int v) {
  if (depth[u] > depth[v])
    swap(u, v);
  int len = depth[v] - depth[u];
  for (int i = 0; i <= lg[len]; i++)
    if (len & (1 << i))
      v = up[i][v];
  if (u == v)
    return u;
  for (int i = lg[depth[u] + 1]; i >= 0; i--)
    if (up[i][v] != up[i][u])
      v = up[i][v], u = up[i][u];
  return up[0][v];
}

int main() {
  cin >> n >> root;
  g.resize(n);
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  // считаем значения для дерева
  used.resize(n), depth.resize(n), parent.resize(n);
  parent[root] = root;
  dfs(root);
  // преподсчитываем предков на расстоянии 2^i
  lg.resize(n + 1);
  for (int i = 2; i <= n; i++)
    lg[i] = lg[i / 2] + 1;
  up.resize(lg[n] + 1, vector <int>(n));
  for (int v = 0; v < n; v++)
    up[0][v] = parent[v];
  for (int p = 1; p <= lg[n]; p++)
    for (int v = 0; v < n; v++)
      up[p][v] = up[p - 1][up[p - 1][v]];
  int q;
  cin >> q;
  while (q--) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    cout << lca(u, v) + 1 << '\n';
  }
  return 0;
}
