#include <iostream>
#include <vector>

using namespace std;

typedef vector <int> vi;
typedef vector <vi> vvi;

int timer = 0;
vector <bool> used;

void dfs(int v, vi &tin, vi &up, vvi &g, int p = -1) {
  used[v] = true;
  tin[v] = up[v] = timer++;
  for (int u : g[v]) {
    if (u == p)
      continue;
    if (used[u]) {
      up[v] = min(up[v], tin[u]);
    } else {
      dfs(u, tin, up, g, v);
      up[v] = min(up[v], up[u]);
      if (up[u] > tin[v])
        cout << u + 1 << ' ' << v + 1 << '\n';
    }
  }
}

int main() {
  int n, m;
  cin >> n >> m;
  vvi g(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  vi tin(n), up(n);
  used.assign(n, false);
  for (int v = 0; v < n; v++)
    if (!used[v])
      dfs(v, tin, up, g);
  return 0;
}
