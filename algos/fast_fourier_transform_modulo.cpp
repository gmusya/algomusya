#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <chrono>

using namespace std;

typedef long long ll;
typedef vector<ll> vll;

const int MOD = 998244353, W = 805775211, IW = 46809892;
const int MAXN = (1 << 19), INV2 = 499122177;

int pws[MAXN + 1], ipws[MAXN + 1];

void init() {
  pws[0] = 1;
  ipws[0] = 1;
  for (int i = 1; i <= MAXN; i++) {
    pws[i] = (pws[i - 1] * 1ll * W) % MOD;
    ipws[i] = (ipws[i - 1] * 1ll * IW) % MOD;
  }
}

vll fft(const vll &arr, int k) {
  int n = arr.size();
  if (n == 1)
    return vll(1, arr[0]);
  vll a(n / 2), b(n / 2);
  for (int i = 0; i < n / 2; i++) {
    a[i] = arr[i * 2];
    b[i] = arr[i * 2 + 1];
  }
  vll av = fft(a, k * 2);
  vll bv = fft(b, k * 2);
  vll res(n);
  for (int i = 0; i < n; i++) {
    int pos = i;
    if (pos >= n / 2)
      pos -= n / 2;
    res[i] = (av[pos] + pws[i * k] * 1ll * bv[pos]) % MOD;
  }
  return res;
}

ll binp(ll a, ll p) {
  if (!p)
    return 1;
  if (p & 1)
    return a * binp(a, p - 1) % MOD;
  ll x = binp(a, (p >> 1));
  return x * x % MOD;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  init();
  int m;
  cin >> m;
  int n = (1 << (m + 1));
  vll a(n, 0), b(n, 0);
  for (int i = 0; i < n / 2; i++)
    cin >> a[i];
  for (int i = 0; i < n / 2; i++)
    cin >> b[i];
  int k = MAXN / n;
  vll newa = fft(a, k), newb = fft(b, k);
  vll c(n, 0);
  for (int i = 0; i < n; i++)
    c[i] = (newa[i] * 1ll * newb[i]) % MOD;
  vll newc = fft(c, k);
  reverse(newc.begin() + 1, newc.end());
  ll tmp = binp(n, MOD - 2);
  for (int i = 0; i < n; i++)
    newc[i] = (newc[i] * tmp) % MOD;
  vector <ll> ans;
  for (int i = 0; i < n; i++)
    ans.push_back(newc[i]);
  for (int i = 0; i < n; i++)
    cout << ans[i] << ' ';
  return 0;
}
