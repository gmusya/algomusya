#include <iostream>
#include <vector>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

typedef long long ll;

mt19937_64 gen(time(0));

vector <int> ans;
vector <int> dsu, rnk;
vector <pair <int, int>> e;

int get(int v) {
  if (dsu[v] == v)
    return v;
  return get(dsu[v]);
}

void merge(int u, int v, vector <pair <int, pair <int, int>>> &upd, int &comp) {
  u = get(u), v = get(v);
  if (u == v)
    return;
  comp--;
  if (rnk[u] < rnk[v])
    swap(u, v);
  if (rnk[u] == rnk[v])
    rnk[u]++;
  upd.push_back({v, {u, rnk[u]}});
  dsu[v] = u;
}

struct segment_tree {
  int q;
  vector <vector <int>> tree;
  segment_tree(int n) {
    q = n;
    tree.resize(n << 2);
  }
  void add(int v, int tl, int tr, int l, int r, int pos) {
    if (l > r)
      return;
    if (l == tl && r == tr) {
      tree[v].push_back(pos);
      return;
    }
    int tm = (tl + tr) / 2;
    add(v * 2, tl, tm, l, min(r, tm), pos);
    add(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, pos);
  }
  void solve(int v, int tl, int tr, int comp) {
    vector <pair <int, pair <int, int>>> upd;
    for (int i = 0; i < (int)tree[v].size(); i++)
      merge(e[tree[v][i]].first, e[tree[v][i]].second, upd, comp);
    if (tl == tr) {
      ans[tl] = comp;
      for (int i = (int)upd.size() - 1; i >= 0; i--) {
        dsu[upd[i].first] = upd[i].first;
        rnk[upd[i].second.first] = upd[i].second.second;
      }
      return;
    }
    int tm  = (tl + tr) / 2;
    solve(v * 2, tl, tm, comp);
    solve(v * 2 + 1, tm + 1, tr, comp);
    for (int i = (int)upd.size() - 1; i >= 0; i--) {
      dsu[upd[i].first] = upd[i].first;
      rnk[upd[i].second.first] = upd[i].second.second;
    }
  }
  void add(int l, int r, int pos) {
    add(1, 0, q - 1, l, r, pos);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, q;
  cin >> n >> q;
  if (q == 0)
    return 0;
  vector <int> t;
  unordered_map <ll, int> pos, birth;
  segment_tree se(q);
  int cnt = -1;
  for (int i = 0; i < q; i++) {
    char c;
    cin >> c;
    if (c == '?')
      t.push_back(++cnt);
    if (c == '+') {
      ++cnt;
      int u, v;
      cin >> u >> v;
      u--, v--;
      if (u > v)
        swap(u, v);
      ll hash = n * 1ll * u + v;
      pos[hash] = e.size();
      birth[hash] = cnt;
      e.push_back({u, v});
    }
    if (c == '-') {
      ++cnt;
      int u, v;
      cin >> u >> v;
      u--, v--;
      if (u > v)
        swap(u, v);
      ll hash = n * 1ll * u + v;
      se.add(birth[hash], cnt, pos[hash]);
      pos.erase(hash);
      birth.erase(hash);
    }
  }
  for (auto &now : pos) {
    ll hash = now.first;
    se.add(birth[hash], q - 1, now.second);
  }
  int comp = n;
  dsu.resize(n), rnk.resize(n);
  iota(dsu.begin(), dsu.end(), 0);
  ans.resize(q);
  se.solve(1, 0, q - 1, comp);
  for (int i = 0; i < (int)t.size(); i++)
    cout << ans[t[i]] << '\n';
  return 0;
}
