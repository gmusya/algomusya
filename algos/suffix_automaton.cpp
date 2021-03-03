#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct automaton {
  struct node {
    int nx[26];
    int p = -1;
    int pre = -1;
    bool term = false;
  };
  int tail;
  vector <node> s;
  automaton(int n) {
    s.resize(2 * n + 1);
    for (int i = 0; i <= 2 * n; i++)
      for (int j = 0; j <= 25; j++)
        s[i].nx[j] = -1;
    tail = 1;
  }
  int add(int a, int ch) {
    int b = tail++;
    s[b].p = 0, s[b].pre = a;
    while (a != -1) {
      if (s[a].nx[ch] == -1) {
        s[a].nx[ch] = b;
        a = s[a].p;
        continue;
      }
      int c = s[a].nx[ch];
      if (s[c].pre == a) {
        s[b].p = c;
        break;
      }
      int d = tail++;
      s[d].pre = a;
      for (int i = 0; i <= 25; i++)
        s[d].nx[i] = s[c].nx[i];
      s[d].p = s[c].p;
      s[c].p = d;
      s[b].p = d;
      while (a != -1 && s[a].nx[ch] == c) {
        s[a].nx[ch] = d;
        a = s[a].p;
      }
      break;
    }
    return b;
  }
  void finale(int b) {
    while (b != -1) {
      s[b].term = true;
      b = s[b].p;
    }
  }
  bool get(string str) {
    int rt = 0;
    for (char c : str) {
      if (s[rt].nx[c - 'a'] == -1)
        return false;
      rt = s[rt].nx[c - 'a'];
    }
    return s[rt].term;
  }
};

int main() {
  int n;
  cin >> n;
  string s;
  cin >> s;
  automaton aut(n);
  int last = 0;
  for (char c : s)
    last = aut.add(last, c - 'a');
  aut.finale(last);;
  int q;
  cin >> q;
  while (q--) {
    string s;
    cin >> s;
    if (aut.get(s))
      cout << "YES\n";
    else
      cout << "NO\n";
  }
  return 0;
}
