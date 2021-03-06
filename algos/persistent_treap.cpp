#include <iostream>
#include <vector>
#include <string>

typedef long long ll;

using namespace std;

struct node {
  ll x, y, sz, sum;
  node *l, *r;
  node() {}
  node(ll _x) {
    x = _x;
    y = (rand() << 16) + rand();
    sz = 1;
    sum = 0;
    l = r = nullptr;
  }
  node (node* cur) {
    if (!cur) {
      sz = 0;
      return;
    }
    x = cur->x;
    y = cur->y;
    sz = cur->sz;
    sum = cur->sum;
    l = cur->l;
    r = cur->r;
  }
  static ll get_sum(node *p) {
    return p ? p->sum : 0;
  }
  static void upd_sum(node *p) {
    p->sum = p->x + get_sum(p->l) + get_sum(p->r);
  }
  static ll get_size(node *p) {
    return p ? p->sz : 0;
  }
  static void upd_size(node *p) {
    p->sz = 1 + get_size(p->l) + get_size(p->r);
  }
  static pair <node*, node*> split(node *p, ll x) {
    if (!p) return {};
    node *t = new node(p);
    if (get_size(t->l) + 1 <= x) {
      pair <node*, node*> q = split(t->r, x - get_size(t->l) - 1);
      t->r = q.first;
      upd_size(t), upd_sum(t);
      return { t, q.second };
    }
    pair <node*, node*> q = split(t->l, x);
    t->l = q.second;
    upd_size(t), upd_sum(t);
    return { q.first, t };
  }
  static node* merge(node *l, node *r) {
    node *t = 0;
    if (!l) {
      t = new node(r);
      return t;
    }
    if (!r) {
      t = new node(l);
      return t;
    }
    if (l->y > r->y) {
      t = new node(l);
      t->r = merge(l->r, r);
      upd_size(t), upd_sum(t);
      return t;
    }
    t = new node(r);
    t->l = merge(l, r->l);
    upd_size(r), upd_sum(r);
    return t;
  }
  static node* insert(ll val, ll x, node* &root) {
    pair <node*, node*> q = split(root, x);
    node *t = new node(val);
    return root = merge(q.first, merge(t, q.second));
  }
  static pair <node*, node*> cut(ll l, ll r, node* &root) {
    pair <node*, node*> q1;
    auto tmp1 = split(root, r);
    if (tmp1.first) q1.first = (tmp1.first);
    if (tmp1.second) q1.second = (tmp1.second);
    pair <node*, node*> q2;
    auto tmp2 = split(q1.first, l - 1);
    if (tmp2.first) q2.first = (tmp2.first);
    if (tmp2.second) q2.second = (tmp2.second);
    root = (merge(q2.first, q1.second));
    if (root->sz == 0) root = 0;
    return {root, q2.second};
  }
  static node* paste(node* p, ll pos, node* &root) {
    pair <node*, node*> q = split(root, pos - 1);
    return root = merge(q.first, merge(p, q.second));
  }
  static pair <node*, ll> get(ll l, ll r, node* &root) {
    if (l > r) return {root, 0};
    auto tmp1 = cut(l, r, root);
    root = new node(tmp1.first);
    if (root->sz == 0) root = 0;
    ll ans = tmp1.second->sum;
    node* tmp2 = paste(tmp1.second, l, root);
    return {tmp2, ans};
  }
  static void write(node* p) {
    if (!p) return;
    write(p->l);
    cout << p->x << " ";
    write(p->r);
  }
};

int main() {
  ll q;
  cin >> q;
  vector <node*> T(q, 0);
  for (int i = 1; i < q; i++) {
    int ver;
    cin >> ver;
    if (ver) T[i] = new node(T[ver]);
    string s;
    cin >> s;
    if (s == "cutandpaste") {
      int l, r, pos;
      cin >> l >> r >> pos;
      pair <node*, node*> tmp = node::cut(l, r, T[i]);
      T[i] = node::paste(tmp.second, pos, tmp.first);
    }
    if (s == "sum") {
      int l, r;
      cin >> l >> r;
      auto tmp = node::get(l, r, T[i]);
      cout << tmp.second << '\n';
      T[i] = tmp.first;
      i--, q--;
    }
    if (s == "insert") {
      int val, pos;
      cin >> val >> pos;
      T[i] = node::insert(val, pos - 1, T[i]);
    }
    if (s == "erase") {
      int l, r;
      cin >> l >> r;
      T[i] = node::cut(l, r, T[i]).first;
    }
    if (s == "write") {
      node::write(T[i]);
      cout << '\n';
      i--, q--;
    }
    cout << "OK" << '\n';
  }
  return 0;
}
