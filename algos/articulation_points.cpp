#include <iostream>
#include <vector>

using namespace std;

typedef vector <int> vi;
typedef vector <vi> vvi;

int timer = 0;
vector <bool> used;
vector <bool> is_articulation_point;

void dfs(int v, vi &tin, vi &up, vvi &g, int p = -1) {
  used[v] = true;
  tin[v] = up[v] = timer++;
  int ch = 0;
  for (int u : g[v]) {
    if (u == p)
      continue;
    if (used[u]) {
      up[v] = min(up[v], tin[u]);
    } else {
      dfs(u, tin, up, g, v);
      up[v] = min(up[v], up[u]);
      if (up[u] >= tin[v] && p != -1)
        is_articulation_point[v] = true;
      ch++;
    }
  }
  if (p == -1)
    is_articulation_point[v] = (ch > 1);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
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
  is_articulation_point.assign(n, false);
  for (int v = 0; v < n; v++)
    if (!used[v])
      dfs(v, tin, up, g);
  vi ans;
  for (int v = 0; v < n; v++)
    if (is_articulation_point[v])
      ans.push_back(v + 1);
  cout << ans.size() << '\n';
  for (int x : ans)
    cout << x << '\n';
  return 0;
}
