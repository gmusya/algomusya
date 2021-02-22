#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef vector <int> vi;
typedef vector <vi> vvi;

vi bfs(int s, vvi &g) {
  int n = g.size();
  vi d(n, n);
  queue <int> q;
  q.push(s);
  d[s] = 0;
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    for (int u : g[v])
      if (d[v] + 1 < d[u]) {
        d[u] = d[v] + 1;
        q.push(u);
      }
  }
  return d;
}

int main() {
  int n;
  cin >> n;
  vvi g(n);
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  vi d1 = bfs(0, g);
  int s = max_element(d1.begin(), d1.end()) - d1.begin();
  vi d2 = bfs(s, g);
  int f = max_element(d2.begin(), d2.end()) - d2.begin();
  cout << "(" << s + 1 << ',' << f + 1 << ") " << d2[f] << endl;
  return 0;
}
