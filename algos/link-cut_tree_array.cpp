#pragma GCC optimize("O3")

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int MAXN = 1e5 + 1;

bool rev[MAXN + 1];
int x[MAXN + 1];
int sz[MAXN + 1];
int left_kid[MAXN + 1], right_kid[MAXN + 1];
int parent[MAXN + 1], pathparent[MAXN + 1];

struct link_cut {
  static int get(int v) {
    if (!v)
      return 0;
    return sz[v];
  }
  static void upd(int v) {
    if (!v)
      return;
    sz[v] = 1 + sz[left_kid[v]] + sz[right_kid[v]];
  }
  static void push(int v) {
    if (!v)
      return;
    if (rev[v]) {
      rev[v] = false;
      swap(left_kid[v], right_kid[v]);
      if (left_kid[v])
        rev[left_kid[v]] ^= 1;
      if (right_kid[v])
        rev[right_kid[v]] ^= 1;
    }
  }
  static void rotate_left(int v) {
    int p = parent[v];
    int r = right_kid[v];
    if (p) {
      if (left_kid[p] == v)
        left_kid[p] = r;
      else
        right_kid[p] = r;
    }
    int tmp = left_kid[r];
    left_kid[r] = v;
    right_kid[v] = tmp;
    parent[v] = r;
    parent[r] = p;
    if (right_kid[v])
      parent[right_kid[v]] = v;
    upd(v);
    upd(r);
  }
  static void rotate_right(int v) {
    int p = parent[v];
    int l = left_kid[v];
    if (p) {
      if (left_kid[p] == v)
        left_kid[p] = l;
      else
        right_kid[p] = l;
    }
    int tmp = right_kid[l];
    right_kid[l] = v;
    left_kid[v] = tmp;
    parent[v] = l;
    parent[l] = p;
    if (left_kid[v])
      parent[left_kid[v]] = v;
    upd(v);
    upd(l);
  }
  static void splay(int v) {
    push(v);
    while (parent[v]) {
      if (pathparent[parent[v]])
        swap(pathparent[parent[v]], pathparent[v]);
      int g = parent[parent[v]];
      if (g) {
        push(g);
        if (pathparent[g])
          swap(pathparent[g], pathparent[v]);
      }
      push(parent[v]);
      push(v);
      if (v == left_kid[parent[v]]) {
        if (!g) {
          rotate_right(parent[v]);
        } else if (parent[v] == left_kid[g]) {
          rotate_right(g);
          rotate_right(parent[v]);
        } else {
          rotate_right(parent[v]);
          rotate_left(parent[v]);
        }
      } else {
        if (!g) {
          rotate_left(parent[v]);
        } else if (parent[v] == right_kid[g]) {
          rotate_left(g);
          rotate_left(parent[v]);
        } else {
          rotate_left(parent[v]);
          rotate_right(parent[v]);
        }
      }
    }
  }
  static void write(int v) {
    if (!v)
      return;
    push(v);
    write(left_kid[v]);
    cout << x[v] << ' ';
    write(right_kid[v]);
  }
  static void expose(int v) {
    splay(v);
    while (pathparent[v]) {
      int p = pathparent[v];
      splay(p);
      if (right_kid[p])
        swap(parent[right_kid[p]], pathparent[right_kid[p]]);
      right_kid[p] = v;
      parent[v] = p;
      pathparent[v] = 0;
      upd(p);
      splay(v);
    }
  }
  static int get_min(int v) {
    push(v);
    while (left_kid[v]) {
      v = left_kid[v];
      push(v);
    }
    splay(v);
    return x[v];
  }
  static void make_root(int v) {
    expose(v);
    if (right_kid[v]) {
      pathparent[right_kid[v]] = v;
      parent[right_kid[v]] = 0;
      right_kid[v] = 0;
      upd(v);
    }
    rev[v] ^= 1;
  }
  static void link(int u, int v) {
    make_root(u);
    pathparent[u] = v;
  }
  static void cut(int u, int v) {
    make_root(u);
    expose(v);
    parent[left_kid[v]] = 0;
    left_kid[v] = 0;
  }
  static int get(int u, int v) {
    make_root(u);
    expose(v);
    int ans = get(left_kid[v]);
    if (get_min(v) == x[u])
      return ans;
    return -1;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  link_cut lc;
  int n, q;
  cin >> n >> q;
  for (int i = 1; i <= n; i++) {
    rev[i] = false;
    x[i] = i;
    sz[i] = 1;
    left_kid[i] = right_kid[i] = 0;
    parent[i] = pathparent[i] = 0;
  }
  while (q--) {
    string s;
    cin >> s;
    if (s == "get") {
      int u, v;
      cin >> u >> v;
      cout << lc.get(u, v) << '\n';
    }
    if (s == "link") {
      int u, v;
      cin >> u >> v;
      lc.link(u, v);
    }
    if (s == "cut") {
      int u, v;
      cin >> u >> v;
      lc.cut(u, v);
    }
  }
  return 0;
}
