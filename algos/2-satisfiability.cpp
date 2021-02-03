#include <iostream>
#include <vector>

using namespace std;

typedef vector <int> vi;
typedef vector <vi> vvi;

vector <bool> used;
vvi g, _g;

void dfs(int v, vi &ord, vvi &g) {
  used[v] = true;
  for (int u : g[v])
    if (!used[u])
      dfs(u, ord, g);
  ord.push_back(v);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  while (cin >> n >> m) {
    g.assign(2 * n, {});
    _g.assign(2 * n, {});
    used.assign(2 * n, false);
    while (m--) {
      int i1, e1, i2, e2;
      cin >> i1 >> e1 >> i2 >> e2; // [i1, e1, i2, e2] = [0, 1, 3, 0] <=> (x[1] | !x[3])
      int u1 = i1, u2 = i1 + n;
      int v1 = i2, v2 = i2 + n;
      if (e1 == 0)
        swap(u1, u2);
      if (e2 == 0)
        swap(v1, v2);
      g[u1].push_back(v2);
      g[v1].push_back(u2);
      _g[v2].push_back(u1);
      _g[u2].push_back(v1);
    }
    vi ord;
    for (int i = 0; i < 2 * n; i++)
      if (!used[i])
        dfs(i, ord, g);
    int cnt = 0;
    vi col(2 * n);
    used.assign(2 * n, false);
    for (int i = 2 * n - 1; i >= 0; i--) {
      int v = ord[i];
      if (used[v])
        continue;
      vi comp;
      dfs(v, comp, _g);
      for (int u : comp)
        col[u] = cnt;
      cnt++;
    }
    for (int v = 0; v < n; v++) {
      if (col[v] > col[v + n])
        cout << 0;
      else
        cout << 1;
    }
    cout << '\n';
  }
  return 0;
}
