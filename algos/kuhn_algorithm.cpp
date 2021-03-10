#include <iostream>
#include <vector>

using namespace std;

int timer = 0;
int n, m, k;
vector <int> used;
vector <int> mt;
vector <vector <int>> g;

bool dfs(int v) {
  if (used[v] == timer)
    return false;
  used[v] = timer;
  for (auto to : g[v]) {
    if (mt[to] == -1 || dfs(mt[to])) {
      mt[to] = v;
      return true;
    }
  }
  return false;
}

int main() {
  cin >> n >> m >> k;
  g.resize(n);
  for (int i = 0; i < k; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    g[u].push_back(v);
  }
  used.resize(n, -1);
  mt.resize(m, -1);
  for (int i = 0; i < n; i++)
    if (dfs(i))
      timer++;
  vector <pair <int, int>> answer;
  for (int i = 0; i < m; i++)
    if (mt[i] != -1)
      answer.push_back({mt[i] + 1, i + 1});
  cout << answer.size() << endl;
  for (auto now : answer)
    cout << now.first << " " << now.second << '\n';
  return 0;
}
