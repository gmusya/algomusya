#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

typedef vector <bool> vb;
typedef vector <int> vi;
typedef vector <vi> vvi;
typedef vector <ll> vl;
typedef vector <vl> vvl;

const ll INF = 1e18;

struct edge {
  int u, v;
  ll w;
};

vb cen;  // является ли вершина центроидом
vi sz;
vi cp;  // предок центроида
vvi g;  // номера рёбер
vvl dis;  // расстояния от вершины до её центроидов
vector <edge> e;

void dfs1(int v, int p) {  // преподсчёт для компоненты
  sz[v] = 1;
  for (int i : g[v]) {
    int u = (e[i].u ^ e[i].v ^ v);
    if (u == p || cen[u])
      continue;
    dfs1(u, v);
    sz[v] += sz[u];
  }
}

int dfs2(int v, int p, int est_sz) {  // ищем центроид
  for (int i : g[v]) {
    int u = (e[i].u ^ e[i].v ^ v);
    if (u == p || cen[u])
      continue;
    if (sz[u] > est_sz)
      return dfs2(u, v, est_sz);
  }
  return v;
}

void dfs3(int v, int p) {  // считаем расстояние до центроида
  for (int i : g[v]) {
    int u = (e[i].u ^ e[i].v ^ v);
    ll w = e[i].w;
    if (u == p || cen[u])
      continue;
    dis[u].push_back(dis[v].back() + w);
    dfs3(u, v);
  }
}

void build_centroid_tree(int v, int p, int est_sz) {
  dfs1(v, p);
  int c = dfs2(v, p, est_sz);
  dis[c].push_back(0);
  dfs3(c, -1);
  cp[c] = p;
  cen[c] = true;
  for (int i : g[c]) {
    int u = (e[i].u ^ e[i].v ^ c);
    if (!cen[u])
      build_centroid_tree(u, c, est_sz / 2);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  g.resize(n);
  for (int i = 0; i + 1 < n; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    u--, v--;
    e.push_back({u, v, w});
    g[u].push_back(i);
    g[v].push_back(i);
  }
  cen.resize(n);
  sz.resize(n);
  cp.resize(n);
  dis.resize(n);
  build_centroid_tree(0, -1, n / 2);
  for (int v = 0; v < n; v++) {
    cout << "v = " << v << '\n';
    for (int it = 0, c = v; it != (int)dis[v].size(); it++, c = cp[c])
      cout << c << ' ' << dis[v][it] << '\n';
  }
  return 0;
}
