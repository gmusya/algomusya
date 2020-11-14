#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const int INF = 1e9 + 2;

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
vector <int> d, p;
vector <edge> e;
vector <vector <int>> g;

bool bfs(int val) {
  d.assign(n, INF);
  d[S] = 0;
  queue <int> q;
  q.push(S);
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    for (int i : g[v]) {
      edge tmp = e[i];
      int to = tmp.to;
      int c = tmp.c;
      int f = tmp.f;
      if (f + val < c && d[to] == INF) {
        d[to] = d[v] + 1;
        q.push(to);
      }
    }
  }
  return d[T] != INF;
}

int dfs(int v, int curf) {
  if (v == T || curf == 0) return curf;
  for (int i = p[v]; i < (int)g[v].size(); i++) {
    edge tmp = e[g[v][i]];
    int to = tmp.to;
    int c = tmp.c;
    int f = tmp.f;
    if (d[to] == d[v] + 1) {
      int delta = dfs(to, min(curf, c - f));
      if (delta) {
        e[g[v][i]].f += delta;
        e[tmp.back].f -= delta;
        return delta;
      }
    }
    p[v]++;
  }
  return 0;
}

long long findMaxFlow(int val) {
  long long maxFlow = 0;
  while (bfs(val)) {
    p.assign(n, 0);
    int flow = dfs(S, INF);
    while (flow) {
      maxFlow += flow;
      flow = dfs(S, INF);
    }
  }
  return maxFlow;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n >> m;
  S = 0, T = n - 1;
  d.resize(n), g.resize(n), e.resize(2 * m);
  for (int i = 0; i < m; i++) {
    int u, v, c;
    cin >> u >> v >> c;
    u--, v--;
    g[u].push_back(i);
    g[v].push_back(i + m);
    edge tmp1(v, c, i + m);
    edge tmp2(u, 0, i);
    e[i] = tmp1;
    e[i + m] = tmp2;
  }
  long long ans = 0;
  long long p = (1 << 30);
  while (true) {
    ans += findMaxFlow(p);
    if (!p)
      break;
    p /= 2;
  }
  cout << ans;
  return 0;
}
