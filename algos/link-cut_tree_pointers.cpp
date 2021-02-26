#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int INF = 1e9;

struct node {
  int x = 0;
  int sz = 1;
  bool rev = false;
  node* left = nullptr;
  node* right = nullptr;
  node* parent = nullptr;
  node* pathparent = nullptr;
  node() {}
  explicit node(int _x) {
    x = _x;
    left = right = parent = nullptr;
    sz = 1;
    rev = false;
  }
  static int get(node* v) {
    if (!v)
      return 0;
    return v->sz;
  }
  static void upd(node* v) {
    if (!v)
      return;
    v->sz = 1 + get(v->left) + get(v->right);
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
      if (v->parent->pathparent) {
        v->pathparent = v->parent->pathparent;
        v->parent->pathparent = nullptr;
      }
      if (v->parent->parent) {
        push(v->parent->parent);
        if (v->parent->parent->pathparent) {
          v->pathparent = v->parent->parent->pathparent;
          v->parent->parent->pathparent = nullptr;
        }
      }
      push(v->parent);
      push(v);
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
  static void write(node* v) {
    if (!v)
      return;
    push(v);
    write(v->left);
    cout << v->x << ' ';
    write(v->right);
  }
  static void expose(node* v) {
    splay(v);
    while (v->pathparent) {
      node* p = v->pathparent;
      splay(p);
      if (p->right) {
        p->right->parent = nullptr;
        p->right->pathparent = p;
      }
      p->right = v;
      v->parent = p;
      v->pathparent = p->pathparent;
      p->pathparent = nullptr;
      upd(p);
      splay(v);
    }
  }
  static int get_min(node* v) {
    push(v);
    while (v->left) {
      v = v->left;
      push(v);
    }
    return v->x;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, q;
  cin >> n >> q;
  vector <node*> nodes(n);
  for (int i = 0; i < n; i++)
    nodes[i] = new node(i + 1);
  while (q--) {
    string s;
    cin >> s;
    if (s == "get") {
      int u, v;
      cin >> u >> v;
      u--, v--;
      node::expose(nodes[u]);
      int r1 = node::get_min(nodes[u]);
      int dist1 = node::get(nodes[u]->left);
      node::expose(nodes[v]);
      int r2 = node::get_min(nodes[v]);
      int dist2 = node::get(nodes[v]->left);
      if (r1 != r2) {
        cout << -1 << '\n';
      } else {
        node::splay(nodes[u]);
        if (nodes[u]->pathparent) {
          int dist3 = dist1 - node::get(nodes[u]->left) - 1;
          cout << dist1 + dist2 - 2 * dist3 << '\n';
        } else {
          cout << abs(dist1 - dist2) << '\n';
        }
      }
    }
    if (s == "link") {
      int u, v;
      cin >> u >> v;
      u--, v--;
      node::expose(nodes[v]);
      if (nodes[v]->right) {
        nodes[v]->right->parent = nullptr;
        nodes[v]->right->pathparent = nodes[v];
        nodes[v]->right = nullptr;
      }
      node::upd(nodes[v]);
      nodes[v]->rev ^= 1;
      node::push(nodes[v]);
      node::expose(nodes[u]);
      nodes[v]->pathparent = nodes[u];
    }
    if (s == "cut") {
      int u, v;
      cin >> u >> v;
      u--, v--;
      node::expose(nodes[u]);
      int x = node::get(nodes[u]->left);
      node::expose(nodes[v]);
      int y = node::get(nodes[v]->left);
      if (x > y)
        swap(u, v);
      node::expose(nodes[v]);
      node::push(nodes[v]);
      nodes[v]->left->parent = nullptr;
      nodes[v]->left = nullptr;
      node::upd(nodes[v]);
    }
  }
  return 0;
}
