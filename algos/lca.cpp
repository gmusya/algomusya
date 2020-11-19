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
  // поднимаемся от v до уровня u
  int len = depth[v] - depth[u];
  for (int i = 0; i <= lg[n]; i++)
    if (len & (1 << i))
      v = up[i][v];
  if (u == v)
    return u;
  pair <int, int> ans = {depth[root], root};
  for (int i = lg[n]; i >= 0; i--) {
    int _u = up[u][i];
    int _v = up[v][i];
    if (_u == _v) { // ответ не может находиться выше _u
      ans = max(ans, {depth[_u], _u});
    } else { // ответ не может находиться ниже _u
      u = _u;
      v = _v;
    }
  }
  return ans.second;
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
