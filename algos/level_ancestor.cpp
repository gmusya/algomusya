#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector <int> vi;
typedef vector <vi> vvi;

int cnt = 0;
vi parent, depth, maxdepth;
vvi g;
vi pathnum, posinpath;
vvi path;
vi lg;
vvi up;

void dfs1(int v, int p = -1) {
  maxdepth[v] = depth[v];
  for (int u : g[v])
    if (u != p) {
      parent[u] = v;
      depth[u] = depth[v] + 1;
      dfs1(u, v);
      maxdepth[v] = max(maxdepth[v], maxdepth[u]);
    }
}

void dfs2(int v, int p = -1) {
  int id = -1;
  for (int u : g[v])
    if (u != p && maxdepth[v] == maxdepth[u])
      id = u;
  if (id == -1) {
    pathnum[v] = cnt++;
    path.push_back({});
    path[pathnum[v]].push_back(v);
    return;
  }
  dfs2(id, v);
  pathnum[v] = pathnum[id];
  posinpath[v] = path[pathnum[v]].size();
  path[pathnum[v]].push_back(v);
  for (int u : g[v])
    if (u != p && u != id)
      dfs2(u, v);
}

int la(int v, int minusdepth) {
  if (!minusdepth)
    return v;
  v = up[lg[minusdepth]][v];
  minusdepth -= (1 << lg[minusdepth]);
  v = path[pathnum[v]][min(posinpath[v] + minusdepth, (int)path[pathnum[v]].size() - 1)];
  return v;
}

int main() {
  int n;
  cin >> n;
  parent.resize(n), depth.resize(n), maxdepth.resize(n);
  pathnum.resize(n), posinpath.resize(n);
  g.resize(n);
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  dfs1(0);
  dfs2(0);
  for (int i = 0; i < (int)path.size(); i++) {
    int newsize = path[i].size() * 2;
    while (path[i].size() < newsize)
      path[i].push_back(parent[path[i][path[i].size() - 1]]);
  }
  lg.resize(n + 1);
  for (int i = 2; i <= n; i++)
    lg[i] = lg[i / 2] + 1;
  up.resize(lg[n] + 1, vi(n));
  for (int v = 0; v < n; v++)
    up[0][v] = parent[v];
  for (int pow = 1; pow <= lg[n]; pow++)
    for (int v = 0; v < n; v++)
      up[pow][v] = up[pow - 1][up[pow - 1][v]];
  int q;
  cin >> q;
  while (q--) {
    int u, d;
    cin >> u >> d;
    u--;
    cout << la(u, d) + 1 << '\n';
  }
  return 0;
}
