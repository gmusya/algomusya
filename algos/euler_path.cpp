#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector <int> f, ans;
vector <vector <pair <int, int>>> g;

void dfs(int v) {
  for (; f[v] < (int)g[v].size();) {
    int u = g[v][f[v]].first;
    int id = g[v][f[v]].second;
    f[v]++;
    dfs(u);
    ans.push_back(id);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  g.resize(n), f.resize(n);
  vector <int> degin(n), degout(n);
  vector <pair <int, int>> e;
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    degin[v]++, degout[u]++;
    g[u].push_back({v, i});
    e.push_back({u, v});
  }
  vector <int> s;
  for (int i = 0; i < n; i++)
    if (degout[i] > degin[i])
      s.push_back(i);
  if (s.size() > 1) {
    cout << -1;
    return 0;
  }
  if (s.empty())
    s.push_back(0);
  dfs(s[0]);
  if (ans.size() != m) {
    cout << -1;
    return 0;
  }
  reverse(ans.begin(), ans.end());
  for (int i = 0; i + 1 < (int)ans.size(); i++)
    if (e[ans[i]].second != e[ans[i + 1]].first) {
      cout << -1;
      return 0;
    }
  for (auto &now : ans)
    cout << now + 1 << ' ';
  return 0;
}
