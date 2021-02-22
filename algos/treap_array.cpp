#pragma GCC optimize("O3")

#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <string>

using namespace std;

const int MAXN = 5000000;

mt19937 rnd(time(0));

int x[MAXN], y[MAXN];
int sz[MAXN];
int left_kid[MAXN], right_kid[MAXN];

struct treap {
  int rt = 0;
  int tail = 1;
  treap() {
    sz[0] = 0;
  }
  int new_node(int _x) {
    x[tail] = _x;
    y[tail] = rnd();
    sz[tail] = 1;
    left_kid[tail] = right_kid[tail] = 0;
    return tail++;
  }
  int get_sz(int p) {
    return sz[p];
  }
  void upd(int p) {
    if (!p)
      return;
    sz[p] = 1 + get_sz(left_kid[p]) + get_sz(right_kid[p]);
  }
  void heapify(int p) {
    if (!p)
      return;
    int id = p;
    if (left_kid[p] && y[left_kid[p]] > y[id])
      id = left_kid[p];
    if (right_kid[p] && y[right_kid[p]] > y[id])
      id = right_kid[p];
    if (id != p) {
      swap(y[id], y[p]);
      heapify(id);
    }
  }
  int build(int l, int r, vector <int> &a) {
    if (l > r)
      return 0;
    int m = (l + r) / 2;
    int p = new_node(a[m]);
    left_kid[p] = build(l, m - 1, a);
    right_kid[p] = build(m + 1, r, a);
    heapify(p);
    upd(p);
    return p;
  }
  int merge(int l, int r) {
    if (!l)
      return r;
    if (!r)
      return l;
    if (y[l] > y[r]) {
      right_kid[l] = merge(right_kid[l], r);
      upd(l);
      return l;
    } else {
      left_kid[r] = merge(l, left_kid[r]);
      upd(r);
      return r;
    }
  }
  pair <int, int> split(int key, int p) {
    if (!p)
      return {0, 0};
    if (key <= x[p]) {
      pair <int, int> tmp = split(key, left_kid[p]);
      left_kid[p] = tmp.second;
      upd(p);
      return {tmp.first, p};
    } else {
      pair <int, int> tmp = split(key, right_kid[p]);
      right_kid[p] = tmp.first;
      upd(p);
      return {p, tmp.second};
    }
  }
  void int_insert(int key, int &root) {
    int n = new_node(key);
    pair <int, int> tmp = split(key, root);
    root = merge(tmp.first, merge(n, tmp.second));
  }
  void node_insert(int n, int &p) {
    if (!p) {
      p = n;
    } else if (y[n] > y[p]) {
      pair <int, int> tmp = split(x[n], p);
      left_kid[n] = tmp.first, right_kid[n] = tmp.second;
      p = n;
    } else {
      node_insert(n, x[n] < x[p] ? left_kid[p] : right_kid[p]);
    }
    upd(p);
  }
  void erase_many(int key, int &root) {
    pair <int, int> tmp1 = split(key, root);
    pair <int, int> tmp2 = split(key + 1, root);
    root = merge(tmp1.first, tmp2.second);
  }
  void erase_one(int key, int &p) {
    if (!p)
      return;
    if (key == x[p])
      p = merge(left_kid[p], right_kid[p]);
    else
      erase_one(key, key < x[p] ? left_kid[p] : right_kid[p]);
    upd(p);
  }
  int kth_element(int k, int p) {
    if (!p)
      return -1;
    if (get_sz(left_kid[p]) + 1 == k)
      return x[p];
    if (get_sz(left_kid[p]) + 1 < k)
      return kth_element(k - get_sz(left_kid[p]) - 1, right_kid[p]);
    else
      return kth_element(k, left_kid[p]);
  }
  int lower_than(int key, int p) {
    if (!p)
      return 0;
    if (key <= x[p])
      return lower_than(key, left_kid[p]);
    else
      return get_sz(left_kid[p]) + 1 + lower_than(key, right_kid[p]);
  }
  void write(int p) {
    if (!p)
      return;
    write(left_kid[p]);
    cout << x[p] << ' ';
    write(right_kid[p]);
  }

  void insert(int key) {
    int n = new_node(key);
    node_insert(n, rt);
  }
  void erase(int key) {
    erase_one(key, rt);
  }
  int kth_element(int k) {
    return kth_element(k, rt);
  }
  int lower_than(int key) {
    return lower_than(key, rt);
  }
  void write() {
    write(rt);
  }
  void build(vector <int> &a) {
    rt = build(0, (int)a.size() - 1, a);
  }
};

int main() {
  treap tr;
  int n;
  cin >> n;
  vector <int> a(n);
  for (int i = 0; i < n; i++)
    a[i] = i;
  tr.build(a);
  int q;
  cin >> q;
  while (q--) {
    string s;
    cin >> s;
    if (s == "insert") {
      int x;
      cin >> x;
      tr.insert(x);
    }
    if (s == "erase") {
      int x;
      cin >> x;
      tr.erase(x);
    }
    if (s == "kth_element") {
      int k;
      cin >> k;
      cout << tr.kth_element(k) << endl;
    }
    if (s == "lower_than") {
      int x;
      cin >> x;
      cout << tr.lower_than(x) << endl;
    }
    if (s == "write") {
      tr.write();
      cout << endl;
    }
  }
  return 0;
}
