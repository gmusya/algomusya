#include <iostream>
#include <vector>
#include <set>

using namespace std;

typedef long long ll;

const ll INF = 1e18;

vector <ll> dijkstra(int s, vector <vector <pair <int, ll>>> &g) {
  int n = g.size();
  vector <ll> d(n, INF);
  d[s] = 0;
  set <pair <ll, int>> q;
  for (int v = 0; v < n; v++)
    q.insert({d[v], v});
  while (!q.empty()) {
    int v = q.begin()->second;
    q.erase(q.begin());
    for (auto [u, w] : g[v])
      if (d[v] + w < d[u]) {
        q.erase({d[u], u});
        d[u] = d[v] + w;
        q.insert({d[u], u});
      }
  }
  return d;
}

int main() {
  int n, m;
  cin >> n >> m;
  vector <vector <pair <int, ll>>> g(n);
  for (int i = 0; i < m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    u--, v--;
    g[u].push_back({v, w});
    g[v].push_back({u, w});
  }
  vector <ll> d = dijkstra(0, g);
  for (ll x : d)
    cout << x << ' ';
  return 0;
}
