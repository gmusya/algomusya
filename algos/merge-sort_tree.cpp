#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct merge_sort_tree {
  int n;
  vector <vector <int>> t;
  merge_sort_tree(int _n) {
    n = _n;
    t.resize(n << 2);
  }
  void build(int v, int tl, int tr, vector <int> &a) {
    if (tl == tr) {
      t[v].push_back(a[tl]);
      return;
    }
    int tm = (tl + tr) / 2;
    build(v * 2, tl, tm, a);
    build(v * 2 + 1, tm + 1, tr, a);
    // если написать merge вручную, может заработать быстрее
    merge(t[v * 2].begin(), t[v * 2].end(),
      t[v * 2 + 1].begin(), t[v * 2 + 1].end(), back_inserter(t[v]));
  }
  int query(int v, int tl, int tr, int l, int r, int minval, int maxval) {
    if (l > r)
      return 0;
    if (l == tl && r == tr)
      return upper_bound(t[v].begin(), t[v].end(), maxval) -
        lower_bound(t[v].begin(), t[v].end(), minval);
    int tm = (tl + tr) / 2;
    int x = query(v * 2, tl, tm, l, min(r, tm), minval, maxval);
    int y = query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, minval, maxval);
    return x + y;
  }
  void build(vector <int> &a) {
    build(1, 0, n - 1, a);
  }
  int query(int l, int r, int minval, int maxval) {
    return query(1, 0, n - 1, l, r, minval, maxval);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, q;
  cin >> n >> q;
  vector <int> a(n);
  for (int i = 0; i < n; i++)
    cin >> a[i];
  merge_sort_tree mst(n);
  mst.build(a);
  while (q--) { // количество элементов со значением от minval до maxval на отрезке
    int l, r, minval, maxval;
    cin >> l >> r >> minval >> maxval;
    l--, r--;
    cout << mst.query(l, r, minval, maxval) << '\n';
  }
  return 0;
}
