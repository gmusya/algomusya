#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, root, timer = 0;
vector <bool> used;
vector <int> depth, path, tin;
vector <vector <int>> g;
vector <int> lg;
vector <vector <pair <int, int>>> st;

void dfs(int v) {
  used[v] = true;
  tin[v] = timer++;
  path.push_back(v);
  for (int u : g[v])
    if (!used[u]) {
      depth[u] = depth[v] + 1;
      dfs(u);
      path.push_back(v);
      timer++;
    }
}

pair <int, int> get(int l, int r) {
  int p = lg[r - l + 1];
  return min(st[p][l], st[p][r - (1 << p) + 1]);
}

int lca(int u, int v) {
  if (tin[u] > tin[v])
    swap(u, v);
  return get(tin[u], tin[v]).second;
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
  used.resize(n), depth.resize(n), tin.resize(n);
  dfs(root);
  path.push_back(root);
  lg.resize(2 * n + 1);
  for (int i = 2; i <= 2 * n; i++)
    lg[i] = lg[i / 2] + 1;
  st.resize(lg[2 * n] + 1, vector <pair <int, int>>(2 * n));
  for (int i = 0; i < 2 * n; i++)
    st[0][i] = {depth[path[i]], path[i]};
  for (int p = 1; p <= lg[2 * n]; p++)
    for (int i = 0; i < 2 * n; i++)
      st[p][i] = min(st[p - 1][i], st[p - 1][min(i + (1 << (p - 1)), 2 * n - 1)]);
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
