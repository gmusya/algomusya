#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct segment_tree {
  int tail = 0;
  int n;
  vector <int> rt;
  vector <int> t, left, right;
  segment_tree(int _n) {
    n = _n;
    tail = (n << 2) + 1;
    t.resize(2e6);
    left.resize(2e6);
    right.resize(2e6);
    rt.push_back(build(1, 0, n - 1));
  }
  int build(int v, int tl, int tr) {
    if (tl == tr)
      return v;
    int tm = (tl + tr) / 2;
    left[v] = build(v * 2, tl, tm);
    right[v] = build(v * 2 + 1, tm + 1, tr);
    return v;
  }
  int upd(int v, int tl, int tr, int pos) {
    int u = tail++;
    t[u] = t[v];
    left[u] = left[v];
    right[u] = right[v];
    if (tl == tr) {
      t[u]++;
      return u;
    }
    int tm = (tl + tr) / 2;
    if (pos <= tm)
      left[u] = upd(left[u], tl, tm, pos);
    else
      right[u] = upd(right[u], tm + 1, tr, pos);
    t[u] = t[left[u]] + t[right[u]];
    return u;
  }
  int slalom(int v1, int v2, int tl, int tr, int k) {
    if (tl == tr)
      return tl;
    int val = t[left[v2]] - t[left[v1]];
    int tm = (tl + tr) / 2;
    if (val >= k)
      return slalom(left[v1], left[v2], tl, tm, k);
    else
      return slalom(right[v1], right[v2], tm + 1, tr, k - val);
  }
  void upd(int pos) {
    rt.push_back(upd(rt.back(), 0, n - 1, pos));
  }
  int kth(int l, int r, int k) {
    return slalom(rt[l - 1], rt[r], 0, n - 1, k);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector <int> pos(n);
  vector <int> a(n);
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
  segment_tree st(n);
  for (int i = 0; i < n; i++)
    st.upd(a[i]);
  int q;
  cin >> q;
  while (q--) {
    int l, r, k;
    cin >> l >> r >> k;
    cout << pos[st.kth(l, r, k)] - l + 2 << '\n';
  }
  return 0;
}
