#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

const long long INF = 1e18;

struct edge {
  int to, cap, f, cost, back;
  edge() {}
  edge(int _to, int _cap, int _cost, int _back) {
    to = _to;
    cap = _cap;
    back = _back;
    cost = _cost;
    f = 0;
  }
};

int n, m, S, T;
vector <edge> e;
vector <vector <int>> g;

long long levit() {
  vector <long long> d(n, INF);
  d[S] = 0;
  vector <bool> used(n);
  vector <pair <int, int>> p(n, {-1, -1});
  deque <int> dq;
  dq.push_back(S);
  while (!dq.empty()) {
    int v = dq.front();
    dq.pop_front();
    for (int i : g[v]) {
      edge tmp = e[i];
      int to = tmp.to, cap = tmp.cap, f = tmp.f, cost = tmp.cost;
      if (d[v] + cost < d[to] && tmp.f < tmp.cap) {
        d[to] = d[v] + cost;
        p[to] = {v, i};
        if (!used[to])
          dq.push_back(to);
        else
          dq.push_front(to);
      }
    }
  }
  if (d[T] == INF)
    return 0;
  vector <int> id;
  for (int v = T; v != S; v = p[v].first)
    id.push_back(p[v].second);
  int mi = 1e9 + 1;
  for (int i : id)
    mi = min(mi, e[i].cap - e[i].f);
  long long res = 0;
  for (int i : id) {
    e[i].f += mi;
    e[e[i].back].f -= mi;
    res += mi * 1ll * e[i].cost;
  }
  return res;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n >> m;
  S = 0, T = n - 1;
  g.resize(n), e.resize(2 * m);
  for (long long i = 0; i < m; i++) {
    int u, v, c, w;
    cin >> u >> v >> c >> w;
    u--, v--;
    g[u].push_back(i);
    g[v].push_back(i + m);
    edge tmp1(v, c, w, i + m);
    edge tmp2(u, 0, -w, i);
    e[i] = tmp1;
    e[i + m] = tmp2;
  }
  long long ans = 0;
  while (true) {
    long long delta = levit();
    ans += delta;
    if (!delta)
      break;
  }
  cout << ans;
  return 0;
}
