#pragma GCC optimize("O3")

#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <string>
#include <algorithm>

using namespace std;

typedef vector <int> vi;
typedef vector <vi> vvi;

mt19937 rnd(time(0));

struct node {
  int x, y;
  int sz;
  node *l, *r;
  node(int _x) {
    x = _x;
    sz = 1;
    y = rnd();
    l = r = nullptr;
  }
  static int get_sz(node* p) {
    if (!p)
      return 0;
    return p->sz;
  }
  static void upd(node* p) {
    if (!p)
      return;
    p->sz = 1 + get_sz(p->l) + get_sz(p->r);
  }
  static void heapify(node* p) {
    if (!p)
      return;
    node* mx = p;
    if (p->l && p->l->y > mx->y)
      mx = p->l;
    if (p->r && p->r->y > mx->y)
      mx = p->r;
    if (mx != p) {
      swap(mx->y, p->y);
      heapify(mx);
    }
  }
  static node* build(int l, int r, vector <int> &a) {
    if (l > r)
      return {};
    int m = (l + r) / 2;
    node* p = new node(a[m]);
    p->l = build(l, m - 1, a);
    p->r = build(m + 1, r, a);
    heapify(p);
    upd(p);
    return p;
  }
  static node* merge(node* l, node* r) {
    if (!l)
      return r;
    if (!r)
      return l;
    if (l->y > r->y) {
      l->r = merge(l->r, r);
      upd(l);
      return l;
    } else {
      r->l = merge(l, r->l);
      upd(r);
      return r;
    }
  }
  static pair <node*, node*> split(int x, node* p) { // (-inf; x)
    if (!p)
      return {};
    if (x <= p->x) {
      pair <node*, node*> tmp = split(x, p->l);
      p->l = tmp.second;
      upd(p);
      return {tmp.first, p};
    } else {
      pair <node*, node*> tmp = split(x, p->r);
      p->r = tmp.first;
      upd(p);
      return {p, tmp.second};
    }
  }
  static void node_insert(node* n, node* &p) {
    if (!p) {
      p = n;
    } else if (n->y > p->y) {
      pair <node*, node*> tmp = split(n->x, p);
      n->l = tmp.first, n->r = tmp.second;
      p = n;
    } else {
      node_insert(n, n->x < p->x ? p->l : p->r);
    }
    upd(p);
  }
  static void erase_one(int x, node* &p) {
    if (!p)
      return;
    if (x == p->x)
      p = merge(p->l, p->r);
    else
      erase_one(x, x < p->x ? p->l : p->r);
    upd(p);
  }
  static int lower_than(int x, node* p) {
    if (!p)
      return 0;
    if (x <= p->x)
      return lower_than(x, p->l);
    else
      return get_sz(p->l) + 1 + lower_than(x, p->r);
  }
};

struct treap {
  node *T = 0;
  void build(vector <int> &a) {
    T = node::build(0, (int)a.size() - 1, a);
  }
  void insert(int x) {
    node* n = new node(x);
    node::node_insert(n, T);
  }
  void erase(int x) {
    node::erase_one(x, T);
  }
  int lower_than(int x) {
    return node::lower_than(x, T);
  }
};

struct merge_sort_tree {
  int n;
  vvi t;
  vector <treap> trp;
  merge_sort_tree(int _n) {
    n = _n;
    t.resize(n << 2);
    trp.resize(n << 2);
  }
  void build(int v, int tl, int tr, vi &a) {
    if (tl == tr) {
      t[v].push_back(a[tl]);
      trp[v].build(t[v]);
      return;
    }
    int tm = (tl + tr) / 2;
    build(v * 2, tl, tm, a);
    build(v * 2 + 1, tm + 1, tr, a);
    merge(t[v * 2].begin(), t[v * 2].end(), t[v * 2 + 1].begin(), t[v * 2 + 1].end(), back_inserter(t[v]));
    trp[v].build(t[v]);
  }
  int get(int v, int tl, int tr, int l, int r, int lval, int rval) {
    if (l > r)
      return 0;
    if (l == tl && r == tr)
      return trp[v].lower_than(rval + 1) - trp[v].lower_than(lval);
    int tm = (tl + tr) / 2;
    int x = get(v * 2, tl, tm, l, min(r, tm), lval, rval);
    int y = get(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, lval, rval);
    return x + y;
  }
  void upd(int v, int tl, int tr, int pos, int oldval, int newval) {
    trp[v].erase(oldval);
    trp[v].insert(newval);
    if (tl == tr)
      return;
    int tm = (tl + tr) / 2;
    if (pos <= tm)
      upd(v * 2, tl, tm, pos, oldval, newval);
    else
      upd(v * 2 + 1, tm + 1, tr, pos, oldval, newval);
  }
  void build(vi &a) {
    build(1, 0, n - 1, a);
  }
  int get(int l, int r, int lval, int rval) {
    return get(1, 0, n - 1, l, r, lval, rval);
  }
  void upd(int pos, int oldval, int newval) {
    upd(1, 0, n - 1, pos, oldval, newval);
  }
};

int main() {
  int n;
  cin >> n;
  vi a(n);
  for (int i = 0; i < n; i++)
    cin >> a[i];
  merge_sort_tree mst(n);
  mst.build(a);
  cout << "OK";
  int q;
  cin >> q;
  while (q--) {
    string s;
    cin >> s;
    if (s == "get") {
      int l, r, lval, rval;
      cin >> l >> r >> lval >> rval;
      l--, r--;
      cout << mst.get(l, r, lval, rval) << endl;
    }
    if (s == "upd") {
      int i, val;
      cin >> i >> val;
      i--;
      mst.upd(i, a[i], val);
      a[i] = val;
    }
  }
  return 0;
}
