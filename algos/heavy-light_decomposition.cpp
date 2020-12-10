#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef __int128 i128;
typedef long long ll;

typedef vector <bool> vb;
typedef vector <int> vi;
typedef vector <ll> vl;
typedef vector <vi> vvi;
typedef vector <i128> vi128;

const ll MOD = 1e9 + 7;

struct segment_tree {
  int n;
  vi128 t;
  vi128 mod;
  void push(int v) {
    mod[v * 2] += mod[v];
    mod[v * 2 + 1] += mod[v];
    mod[v] = 0;
  }
  void build(int v, int tl, int tr, vector <ll> &a) {
    if (tl == tr) {
      t[v] = a[tl];
      return;
    }
    int tm = (tl + tr) / 2;
    build(v * 2, tl, tm, a);
    build(v * 2 + 1, tm + 1, tr, a);
    t[v] = t[v * 2] + t[v * 2 + 1];
  }
  void upd(int v, int tl, int tr, int l, int r, ll val) {
    if (l > r)
      return;
    if (l == tl && r == tr) {
      mod[v] += val;
      return;
    }
    push(v);
    int tm = (tl + tr) / 2;
    upd(v * 2, tl, tm, l, min(r, tm), val);
    upd(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, val);
    t[v] = t[v * 2] + t[v * 2 + 1] + mod[v * 2] * (tm - tl + 1) + mod[v * 2 + 1] * (tr - tm);
  }
  i128 get(int v, int tl, int tr, int l, int r) {
    if (l > r)
      return (i128)0;
    if (l == tl && r == tr)
      return t[v] + mod[v] * (tr - tl + 1);
    push(v);
    int tm = (tl + tr) / 2;
    i128 x = get(v * 2, tl, tm, l, min(r, tm));
    i128 y = get(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
    t[v] = t[v * 2] + t[v * 2 + 1] + mod[v * 2] * (tm - tl + 1) + mod[v * 2 + 1] * (tr - tm);
    return x + y;
  }
  void build(vector <ll> &a) {
    n = (int)a.size();
    t.resize(n << 2);
    mod.resize(n << 2);
    build(1, 0, n - 1, a);
  }
  void upd(int l, int r, ll val) {
    upd(1, 0, n - 1, l, r, val);
  }
  i128 get(int l, int r) {
    return get(1, 0, n - 1, l, r);
  }
};

int n, timer = 0;
vi tin, tout, sz, dep, par, root;
vvi g;
vi lg;
vvi up;

segment_tree st;

void dfs1(int v) {
  sz[v] = 1;
  for (int u : g[v]) {
    dep[u] = dep[v] + 1;
    par[u] = v;
    dfs1(u);
    sz[v] += sz[u];
  }
}

void dfs2(int v) {
  tin[v] = timer++;
  int id = -1;
  for (int u : g[v])
    if (id == -1 || sz[u] > sz[id])
      id = u;
  if (id == -1) {
    tout[v] = timer - 1;
    return;
  }
  root[id] = root[v];
  dfs2(id);
  for (int u : g[v])
    if (u != id) {
      root[u] = u;
      dfs2(u);
    }
  tout[v] = timer - 1;
}

i128 get(int v, int w) {
  if (dep[root[v]] <= dep[w])
    return st.get(tin[w], tin[v]);
  i128 s1 = st.get(tin[root[v]], tin[v]);
  i128 s2 = (root[v] ? get(par[root[v]], w) : 0);
  return s1 + s2;
}

i128 get(int v) {
  int l = tin[v] + 1, r = tout[v];
  i128 s1 = st.get(l, r);
  i128 s2 = get(v, 0);
  return s1 + s2;
}

void upd(int v, int w, ll val) {
  if (dep[root[v]] <= dep[w]) {
    st.upd(tin[w], tin[v], val);
  } else {
    st.upd(tin[root[v]], tin[v], val);
    if (root[v])
      upd(par[root[v]], w, val);
  }
}

void upd(int v, ll val) {
  int l = tin[v] + 1, r = tout[v];
  st.upd(l, r, val);
  upd(v, 0, val);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int q;
  cin >> n >> q;
  g.resize(n);
  for (int i = 1; i < n; i++) {
    int p;
    cin >> p;
    g[p].push_back(i);
  }
  vl c(n);
  for (int i = 0; i < n; i++)
    cin >> c[i];
  sz.resize(n), dep.resize(n), par.resize(n);
  dfs1(0);
  tin.resize(n), tout.resize(n), root.resize(n);
  dfs2(0);
  {
    vl tmp(n);
    for (int i = 0; i < n; i++)
      tmp[tin[i]] = c[i];
    st.build(tmp);
  }
  cout << (ll)st.get(tin[n - 1], tin[n - 1]) << ' ';
  while (q--) {
    int u, v;
    cin >> u >> v;
    i128 s = get(u);
    s %= MOD;
    upd(v, s);
    cout << (ll)st.get(tin[n - 1], tin[n - 1]) << ' ';
  }
  return 0;
}
