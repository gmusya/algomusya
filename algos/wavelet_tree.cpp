#include <iostream>
#include <vector>
#include <map>

using namespace std;

typedef vector <int> vi;
typedef vector <vi> vvi;

struct wavelet_tree {
  int n;
  vvi t;
  wavelet_tree(int _n) {
    n = _n;
    t.resize(n << 2);
  }
  void build(int v, int tl, int tr, vi &a) {
    int tm = (tl + tr) / 2;
    t[v].push_back(0);
    for (int i = 0; i < (int)a.size(); i++)
      t[v].push_back(t[v].back() + (a[i] <= tm));
    if (tl == tr)
      return;
    vi b, c;
    for (int i = 0; i < (int)a.size(); i++) {
      if (a[i] <= tm)
        b.push_back(a[i]);
      else
        c.push_back(a[i]);
    }
    build(v * 2, tl, tm, b);
    build(v * 2 + 1, tm + 1, tr, c);
  }
  int kth(int v, int tl, int tr, int l, int r, int k) {
    if (tl == tr)
      return tl;
    int lb = t[v][l - 1];
    int rb = t[v][r];
    int val = rb - lb;
    int tm = (tl + tr) / 2;
    if (k <= val)
      return kth(v * 2, tl, tm, lb + 1, rb, k);
    else
      return kth(v * 2 + 1, tm + 1, tr, l - lb, r - rb, k - val);
  }
  int kth(int l, int r, int k) {
    return kth(1, 0, n - 1, l, r, k);
  }
  void build(vi &a) {
    build(1, 0, n - 1, a);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vi a(n);
  vi pos(n);
  for (int i = 0; i < n; i++)
    cin >> a[i];
  {
    map <int, int> allx;
    for (int i = 0; i < n; i++)
      allx[a[i]] = 0;
    int cnt = 0;
    for (auto &now : allx)
      now.second = cnt++;
    for (int i = 0; i < n; i++)
      a[i] = allx[a[i]];
  }
  for (int i = 0; i < n; i++)
    pos[a[i]] = i;
  wavelet_tree wt(n);
  wt.build(a);
  int q;
  cin >> q;
  while (q--) {
    int l, r, k;
    cin >> l >> r >> k;
    cout << pos[wt.kth(l, r, k)] - l + 2 << '\n';
  }
  return 0;
}
