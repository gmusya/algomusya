#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <iostream>
#include <complex>
#include <vector>
#include <algorithm>
#include <math.h>
#include <chrono>

using namespace std;

typedef complex<double> cd;
typedef vector<cd> vcd;

int n = (1 << 19);
vcd roots;

vcd fft(const vcd &arr, int k = 1) {
  int n = arr.size();
  if (n == 1)
    return vcd(1, arr[0]);
  vcd a(n / 2), b(n / 2);
  for (int i = 0; i < n / 2; i++) {
    a[i] = arr[i * 2];
    b[i] = arr[i * 2 + 1];
  }
  vcd av = fft(a, k * 2);
  vcd bv = fft(b, k * 2);
  vcd res(n);
  for (int i = 0; i < n; i++) {
    int pos = i;
    if (pos >= n / 2)
      pos -= n / 2;
    res[i] = av[pos] + roots[i * k] * bv[pos];
  }
  return res;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  string s1, s2;
  cin >> s1 >> s2;
  // s1 = a, s2 = b, ans = a * b
  if (s1.size() < s2.size())
    swap(s1, s2);
  bool flag = true;
  if (s1[0] == '-') {
    flag = !flag;
    s1.erase(s1.begin());
  }
  if (s2[0] == '-') {
    flag = !flag;
    s2.erase(s2.begin());
  }
  string t;
  for (int i = 0; i < s1.size() - s2.size(); i++)
    t += "0";
  s2 = t + s2;
  n = 1;
  while (n <= s1.size() && n <= s2.size())
    n *= 2;
  n *= 2;
  int m = s1.size() + s2.size() - 1;
  roots.resize(n);
  for (int i = 0; i < n; i++) {
    double alpha = 2 * M_PI * i / n;
    roots[i] = cd(cos(alpha), sin(alpha));
  }
  vcd a(n, 0), b(n, 0);
  for (int i = 0; i < (int)s1.size(); i++)
    a[i] = s1[i] - '0';
  for (int i = 0; i < (int)s2.size(); i++)
    b[i] = s2[i] - '0';
  vcd newa = fft(a), newb = fft(b);
  vcd c(n, 0);
  for (int i = 0; i < n; i++)
    c[i] = newa[i] * newb[i];
  vcd newc = fft(c);
  reverse(newc.begin() + 1, newc.end());
  cd tmp = n;
  vector <long long> ans;
  for (int i = 0; i + 1 < n; i++)
    ans.push_back(round((newc[i] / tmp).real()));
  for (int i = (int)ans.size() - 1; i >= 1; i--) {
    ans[i - 1] += ans[i] / 10;
    ans[i] %= 10;
  }
  int i = 0;
  for (; i + 1 < m; i++)
    if (ans[i])
      break;
  if (i + 1 == m && ans[i] == 0)
    flag = true;
  if (!flag)
    cout << '-';
  for (; i < m; i++)
    cout << ans[i];
  return 0;
}
