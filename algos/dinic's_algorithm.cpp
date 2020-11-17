#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

typedef long long ll;

using namespace std;

const int INF = 1e9; // должна быть не меньше максимальной пропускной способности

struct edge {
  int to, c, f, back;
  edge(int _to, int _c, int _back) {
    to = _to;
    c = _c;
    f = 0;
    back = _back;
  }
};

int n, S, T;
vector <edge> e;
vector <int> d; // расстояние от истока
vector <int> p; // для каждой вершины х раним номер первого ребра, по которому может течь поток
vector <vector <int>> g; // для каждой вершины храним номера рёбер, исходящих из неё

void add_edge(int u, int v, int cuv, int cvu) {
  // если ребра ориентированные, то cvu = 0; в противном случае cuv = cvu
  int tail = e.size();
  g[u].push_back(tail);
  g[v].push_back(tail + 1);
  edge euv(v, cuv, tail + 1);
  edge evu(u, cvu, tail);
  e.push_back(euv);
  e.push_back(evu);
}

bool bfs(int scal) { // строим слоистую сеть
  d.assign(n, n);
  d[S] = 0;
  queue <int> q;
  q.push(S);
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    for (int i : g[v]) {
      edge tmp = e[i];
      int to = tmp.to, c = tmp.c, f = tmp.f;
      if (f + scal < c && d[to] == n) {
        d[to] = d[v] + 1;
        q.push(to);
      }
    }
  }
  return (d[T] != n);
}

int dfs(int v, int curf) { // curf - величина потока, найденного до вершины v
  if (v == T || !curf)
    return curf;
  for (int i = p[v]; i < (int)g[v].size(); i++) {
    edge tmp = e[g[v][i]];
    int to = tmp.to, c = tmp.c, f = tmp.f, back = tmp.back;
    if (d[to] == d[v] + 1) {
      int delta = dfs(to, min(curf, c - f));
      if (delta) {
        e[g[v][i]].f += delta;
        e[back].f -= delta;
        return delta;
      }
    }
    p[v]++; // если не нашли пути с этим ребром, на него больше нет смысла смотреть
  }
  return 0;
}

ll find_max_flow(int scal) {
  ll max_flow = 0;
  while (bfs(scal)) {
    p.assign(n, 0);
    int cur_flow = dfs(S, INF); // внимательно следить за типом бесконечности
    while (cur_flow) {
      max_flow += cur_flow;
      cur_flow = dfs(S, INF);
    }
  }
  return max_flow;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int m;
  cin >> n >> m;
  S = 0, T = n - 1;
  g.resize(n);
  for (int i = 0; i < m; i++) {
    int u, v, c;
    cin >> u >> v >> c;
    u--, v--;
    add_edge(u, v, c, 0);
  }
  ll ans = 0;
  int p = (1 << 30); // масштабируем, для рёбер единичной пропускной способности p = 0
  while (true) {
    ans += find_max_flow(p);
    if (!p)
      break;
    p /= 2;
  }
  cout << ans;
  return 0;
}
