#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

struct prefix_tree {
  struct vertex {
    int cnt = 0;
    char symb;
    map <char, int> next;
  };
  int root;
  int tail;
  vector <vertex> ver;
  prefix_tree(int n) {
    root = 0;
    tail = 1;
    ver.resize(n);
  }
  void add(string s) {
    int v = root;
    int it = 0;
    while (it != s.size() && ver[v].next.find(s[it]) != ver[v].next.end())
      v = ver[v].next[s[it++]];
    while (it != s.size()) {
      int u = tail++;
      ver[v].next[s[it]] = u;
      ver[u].symb = s[it];
      v = u;
      it++;
    }
    ver[v].cnt++;
  }
  void dfs(int v, string &s, vector <string> &ans) {
    if (v != 0) s.push_back(ver[v].symb);
    while (ver[v].cnt > 0) {
      ans.push_back(s);
      ver[v].cnt--;
    }
    for (auto now : ver[v].next)
      dfs(now.second, s, ans);
    if (v != 0) s.pop_back();
  }
};

int main() {
  int n;
  cin >> n;
  vector <string> t(n);
  for (int i = 0; i < n; i++)
    cin >> t[i];
  int sum = 1;
  for (int i = 0; i < t.size(); i++)
    sum += t[i].size();
  prefix_tree trie(sum);
  for (int i = 0; i < t.size(); i++)
    trie.add(t[i]);
  vector <bool> used(sum);
  vector <string> ans;
  string cur;
  trie.dfs(0, cur, ans);
  for (int i = 0; i < n; i++)
    cout << ans[i] << '\n';
  return 0;
}
