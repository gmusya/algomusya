#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int INF = 1e9;

struct node {
  int x;
  node *left, *right, *parent;
  int sz;
  bool rev;
  int mi;
  node(int _x) {
    x = _x;
    left = right = parent = nullptr;
    sz = 1;
    mi = x;
    rev = false;
  }
  static int get(node* v) {
    if (!v)
      return 0;
    return v->sz;
  }
  static int get_min(node* v) {
    if (!v)
      return INF;
    return v->mi;
  }
  static void upd(node* v) {
    if (!v)
      return;
    v->sz = 1 + get(v->left) + get(v->right);
    v->mi = min({v->x, get_min(v->left), get_min(v->right)});
  }
  static void push(node* v) {
    if (!v)
      return;
    if (v->rev) {
      v->rev = false;
      swap(v->left, v->right);
      if (v->left)
        v->left->rev ^= 1;
      if (v->right)
        v->right->rev ^= 1;
    }
  }
  static void rotate_left(node* v) {
    node* p = v->parent;
    node* r = v->right;
    if (p) {
      if (p->left == v)
        p->left = r;
      else
        p->right = r;
    }
    node* tmp = r->left;
    r->left = v;
    v->right = tmp;
    v->parent = r;
    r->parent = p;
    if (v->right)
      v->right->parent = v;
    upd(v);
    upd(r);
  }
  static void rotate_right(node* v) {
    node* p = v->parent;
    node* l = v->left;
    if (p) {
      if (p->left == v)
        p->left = l;
      else
        p->right = l;
    }
    node* tmp = l->right;
    l->right = v;
    v->left = tmp;
    v->parent = l;
    l->parent = p;
    if (v->left)
      v->left->parent = v;
    upd(v);
    upd(l);
  }
  static void splay(node* v) {
    push(v);
    while (v->parent) {
      node* g = v->parent->parent;
      if (v == v->parent->left) {
        if (!g) {
          rotate_right(v->parent);
        } else if (v->parent == g->left) {
          rotate_right(g);
          rotate_right(v->parent);
        } else {
          rotate_right(v->parent);
          rotate_left(v->parent);
        }
      } else {
        if (!g) {
          rotate_left(v->parent);
        } else if (v->parent == g->right) {
          rotate_left(g);
          rotate_left(v->parent);
        } else {
          rotate_left(v->parent);
          rotate_right(v->parent);
        }
      }
    }
  }
  static void insert(int x, int pos, node* &v) {
    node* p = nullptr;
    bool is_it_left_kid = false;
    while (v) {
      push(v);
      p = v;
      v->sz++;
      if (pos <= get(v->left) + 1) {
        is_it_left_kid = true;
        v = v->left;
      } else {
        pos -= get(v->left) + 1;
        is_it_left_kid = false;
        v = v->right;
      }
    }
    v = new node(x);
    if (p) {
      v->parent = p;
      if (is_it_left_kid)
        p->left = v;
      else
        p->right = v;
    }
    splay(v);
  }
  static node* merge(node* l, node* r) {
    if (!l)
      return r;
    if (!r)
      return l;
    push(l);
    while (l->right) {
      l = l->right;
      push(l);
    }
    splay(l);
    l->right = r;
    r->parent = l;
    upd(l);
    return l;
  }
  static void erase(int pos, node* &v) {
    if (get(v) < pos)
      return;
    while (v && get(v->left) + 1 != pos) {
      push(v);
      v->sz--;
      if (pos < get(v->left) + 1) {
        v = v->left;
      } else {
        pos -= get(v->left) + 1;
        v = v->right;
      }
    }
    splay(v);
    if (v->left)
      v->left->parent = nullptr;
    if (v->right)
      v->right->parent = nullptr;
    v = merge(v->left, v->right);
  }
  static pair <node*, node*> split(int pos, node* v) { // [1; x]
    if (pos == 0)
      return {nullptr, v};
    push(v);
    while (v && get(v->left) + 1 != pos) {
      if (pos < get(v->left) + 1) {
        v = v->left;
      } else {
        pos -= get(v->left) + 1;
        v = v->right;
      }
      push(v);
    }
    splay(v);
    node* tmp = v->right;
    if (v->right) {
      v->right->parent = nullptr;
      v->right = nullptr;
    }
    upd(v);
    return {v, tmp};
  }
  static void reverse(int l, int r, node* &v) {
    pair <node*, node*> tmp1 = split(r, v);
    pair <node*, node*> tmp2 = split(l - 1, tmp1.first);
    tmp2.second->rev ^= 1;
    v = merge(merge(tmp2.first, tmp2.second), tmp1.second);
  }
  static int get_min(int l, int r, node* &v) {
    pair <node*, node*> tmp1 = split(r, v);
    pair <node*, node*> tmp2 = split(l - 1, tmp1.first);
    int ans = tmp2.second->mi;
    v = merge(merge(tmp2.first, tmp2.second), tmp1.second);
    return ans;
  }
  static void write(node* v) {
    if (!v)
      return;
    write(v->left);
    cout << v->x << ' ';
    write(v->right);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  node* T = nullptr;
  int n, q;
  cin >> n >> q;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    node::insert(x, i + 1, T);
  }
  while (q--) {
    int t;
    cin >> t;
    if (t == 1) {
      int l, r;
      cin >> l >> r;
      node::reverse(l, r, T);
    }
    if (t == 2) {
      int l, r;
      cin >> l >> r;
      cout << node::get_min(l, r, T) << '\n';
    }
  }
  return 0;
}
