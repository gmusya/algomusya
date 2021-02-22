#include <iostream>
#include <vector>
#include <deque>

using namespace std;

int main() {
  int n, m;
  cin >> n >> m;
  vector <vector <pair <int, int>>> g(n);
  for (int i = 0; i < m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    u--, v--;
    g[v].push_back({u, w});
    g[u].push_back({v, w});
  }
  vector <int> d(n, n);
  d[0] = 0;
  deque <int> dq;
  dq.push_back(0);
  while (!dq.empty()) {
    int v = dq.front();
    dq.pop_front();
    for (auto [u, w] : g[v])
      if (d[v] + w < d[u]) {
        d[u] = d[v] + w;
        if (w)
          dq.push_back(u);
        else
          dq.push_front(u);
      }
  }
  for (int x : d)
    cout << x << ' ';
  return 0;
}
