#pragma GCC optimize("O3")

#include <iostream>
#include <vector>
#include <chrono>
#include <set>
#include <random>

using namespace std;

struct node {
  int x;
  node *left, *right, *parent;
  node(int _x) {
    x = _x;
    left = right = parent = nullptr;
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
  }
  static void splay(node* v) {
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
  static void insert(int x, node* &v) {
    node* p = nullptr;
    bool is_it_left_kid = false;
    while (v) {
      p = v;
      if (x <= v->x) {
        v = v->left;
        is_it_left_kid = true;
      } else {
        v = v->right;
        is_it_left_kid = false;
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
  static void write(node* v) {
    if (!v)
      return;
    write(v->left);
    cout << v->x << ' ';
    write(v->right);
  }
  static node* merge(node* l, node* r) {
    if (!l)
      return r;
    if (!r)
      return l;
    while (l->right)
      l = l->right;
    splay(l);
    l->right = r;
    r->parent = l;
    return l;
  }
  static void erase(int x, node* &v) {
    node* p = nullptr;
    while (v && v->x != x) {
      p = v;
      if (x < v->x)
        v = v->left;
      else
        v = v->right;
    }
    if (v) {
      splay(v);
      if (v->left)
        v->left->parent = nullptr;
      if (v->right)
        v->right->parent = nullptr;
      v = merge(v->left, v->right);
      return;
    }
    if (p) {
      splay(p);
      v = p;
    }
  }
  static bool find(int x, node* &v) {
    node* p = nullptr;
    while (v && v->x != x) {
      p = v;
      if (x < v->x)
        v = v->left;
      else
        v = v->right;
    }
    if (v) {
      splay(v);
      return true;
    }
    if (p) {
      splay(p);
      v = p;
    }
    return false;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  node* T = nullptr;
  int q;
  cin >> q;
  while (q--) {
    string s;
    cin >> s;
    if (s == "insert") {
      int x;
      cin >> x;
      if (!node::find(x, T))
        node::insert(x, T);
    }
    if (s == "delete") {
      int x;
      cin >> x;
      node::erase(x, T);
    }
    if (s == "exists") {
      int x;
      cin >> x;
      if (node::find(x, T))
        cout << "true\n";
      else
        cout << "false\n";
    }
    if (s == "write") {
      node::write(T);
      cout << endl;
    }
  }
  return 0;
}
