#include <iostream>
#include <vector>
#include <string>

typedef long long ll;

using namespace std;

struct node {
  ll x, y, sz;
  node *l, *r;
  node() = default;
  explicit node(ll _x) {
    x = _x;
    y = (rand() << 16) + rand();
    l = r = nullptr;
    sz = 1;
  }
  static ll get_size(node *p) {
    return p ? p->sz : 0;
  }
  static void upd_size(node *p) {
    p->sz = 1 + get_size(p->l) + get_size(p->r);
  }
  static pair <node*, node*> split (node* p, ll x) {
    if (!p) return {};
    if (x >= p->x) {
      pair <node*, node*> q = split(p->r, x);
      p->r = q.first;
      upd_size(p);
      return { p, q.second };
    }
    pair <node*, node*> q = split(p->l, x);
    p->l = q.second;
    upd_size(p);
    return { q.first, p };
  }
  static node* merge(node *l, node *r) {
    if (!l) return r;
    if (!r) return l;
    if (l->y > r->y) {
      l->r = merge(l->r, r);
      upd_size(l);
      return l;
    }
    r->l = merge(l, r->l);
    upd_size(r);
    return r;
  }
  static void insert(ll x, node* &p) {
    pair <node*, node*> q = split(p, x);
    node *t = new node(x);
    p = merge(q.first, merge(t, q.second));
  }
  static void erase(ll x, node* &p) {
    if (!p) return;
    if (p->x == x) p = merge(p->l, p->r);
    else erase(x, x < p->x ? p->l : p->r);
  }
  static void write(node* p) {
    if (!p) return;
    write(p->l);
    cout << p->x << " ";
    write(p->r);
  }
  static int kth (int k, node *p) {
    if (!p) return -1;
    if (get_size(p->l) == k - 1) return p->x;
    if (get_size(p->l) >= k) return kth(k, p->l);
    return kth(k - get_size(p->l) - 1, p->r);
  }
};

int main () {
  node *T = 0;
  int q;
  cin >> q;
  while (q--) {
    string s;
    cin >> s;
    if (s == "insert") {
      int val;
      cin >> val;
      node::insert(val, T);
    }
    if (s == "erase") {
      int val;
      cin >> val;
      node::erase(val, T);
    }
    if (s == "kth") {
      int k;
      cin >> k;
      cout << node::kth(k, T) << '\n';
    }
    if (s == "write") {
      node::write(T);
      cout << '\n';
    }
  }
  return 0;
}
