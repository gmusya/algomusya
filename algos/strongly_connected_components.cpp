#include <iostream>
#include <vector>

using namespace std;

typedef vector <int> vi;
typedef vector <vi> vvi;

vector <bool> used;
vi col;
vvi g, _g;

void dfs(int v, vi &ord, vvi &g) {
  used[v] = true;
  for (int u : g[v])
    if (!used[u])
      dfs(u, ord, g);
  ord.push_back(v);
}

int main() {
  int n, m;
  cin >> n >> m;
  g.resize(n), _g.resize(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    g[u].push_back(v);
    _g[v].push_back(u);
  }
  vi ord;
  used.resize(n);
  for (int i = 0; i < n; i++)
    if (!used[i])
      dfs(i, ord, g);
  used.assign(n, false), col.resize(n);
  int cnt = 0;
  for (int i = n - 1; i >= 0; i--) {
    int v = ord[i];
    if (used[v])
      continue;
    vi comp;
    dfs(v, comp, _g);
    for (int u : comp)
      col[u] = cnt;
    cnt++;
  }
  vvi newg(cnt);
  for (int v = 0; v < n; v++)
    for (int u : g[v])
      if (col[u] != col[v])
        newg[col[v]].push_back(col[u]);
  for (int v = 0; v < n; v++)
    cout << col[v] << ' ';
  return 0;
}