#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void count_sort(vector <int> &p, vector <int> &c) {
  int n = p.size();
  vector <int> cnt(n), p_new(n), pos(n);
  for (int x : c) cnt[x]++;
  for (int i = 1; i < n; i++) pos[i] = pos[i - 1] + cnt[i - 1];
  for (int x : p) {
    int i = c[x];
    p_new[pos[i]] = x;
    pos[i]++;
  }
  p = p_new;
}

int main() {
  string s;
  cin >> s;
  s += "$";
  int n = s.size();
  vector <int> p(n), c(n);
  vector <pair <char, int>> a(n);
  for (int i = 0; i < n; i++) a[i] = { s[i], i };
  sort(a.begin(), a.end());
  for (int i = 0; i < n; i++) p[i] = a[i].second;
  for (int i = 1; i < n; i++) c[p[i]] = c[p[i - 1]] + (a[i].first != a[i - 1].first);

  int k = 0;
  while ((1 << k) < n) {
    for (int i = 0; i < n; i++)
      p[i] = (p[i] - (1 << k) + n) % n;
    count_sort(p, c);
    vector <int> c_new(n);
    for (int i = 1; i < n; i++) {
      pair <int, int> prev = { c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n] };
      pair <int, int> now = { c[p[i]], c[(p[i] + (1 << k)) % n] };
      c_new[p[i]] = c_new[p[i - 1]] + (prev != now);
    }
    c = c_new;
    k++;
  }
  vector <int> lcp(n);
  k = 0;
  for (int i = 0; i < n - 1; i++) {
    int pi = c[i];
    int j = p[pi - 1];
    while (s[i + k] == s[j + k]) k++;
    lcp[pi] = k;
    k = max(k - 1,0);
  }
  for (int i = 0; i < n; i++)
    cout << lcp[i] << " " << p[i] << " " << s.substr(p[i], n - p[i]) << endl;
  return 0;
}
