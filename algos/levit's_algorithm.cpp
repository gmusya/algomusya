#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef vector <int> vi;
typedef vector <pair <int, int>> vpii;
typedef vector <vpii> vvpii;

const int INF = 1e9;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  vvpii g(n);
  for (int i = 0; i < m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    u--, v--;
    g[u].push_back({v, w});
  }
  vi d(n, INF);
  d[0] = 0;
  queue <int> q;
  q.push(0);
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    for (auto &[u, w] : g[v])
      if (d[v] + w < d[u]) {
        d[u] = d[v] + w;
        q.push(u);
      }
  }
  for (int v = 0; v < n; v++)
    cout << d[v] << ' ';
  return 0;
}
