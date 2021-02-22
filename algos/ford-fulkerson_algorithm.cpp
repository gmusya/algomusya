#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;

struct edge {
  int to, c, f, back;
  edge() {}
  edge(int _to, int _c, int _back) {
    to = _to;
    c = _c;
    back = _back;
    f = 0;
  }
};

int n, m, S, T;
vector <bool> used;
vector <edge> e;
vector <vector <int>> g;

int dfs(int v, int curf) {
  if (v == T) return curf;
  used[v] = true;
  for (int i : g[v]) {
    edge tmp = e[i];
    int to = tmp.to;
    int c = tmp.c;
    int f = tmp.f;
    if (used[to] || tmp.f >= tmp.c) continue;
    int delta = dfs(to, min(curf, c - f));
    if (delta > 0) {
      e[i].f += delta;
      e[tmp.back].f -= delta;
      return delta;
    }
  }
  return 0;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n >> m;
  S = 0, T = n - 1;
  g.resize(n), e.resize(2 * m);
  for (int i = 0; i < m; i++) {
    int u, v, c;
    cin >> u >> v >> c;
    u--, v--;
    g[u].push_back(i);
    g[v].push_back(i + m);
    edge tmp1(v, c, i + m);
    edge tmp2(u, c, i);
    e[i] = tmp1;
    e[i + m] = tmp2;
  }
  int ans = 0;
  while (true) {
    used.assign(n, false);
    int delta = dfs(S, INF);
    ans += delta;
    if (!delta) break;
  }
  cout << ans << endl;
  return 0;
}
