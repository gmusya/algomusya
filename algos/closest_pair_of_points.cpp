#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

typedef long long ll;

const ll INF = 8e18;

struct vec {
  ll x, y;
  void read() {
    cin >> x >> y;
  }
  void write() {
    cout << x << " " << y << endl;
  }
};

int n;
vector <vec> a;

bool cmp_x(vec a, vec b) {
  return (a.x < b.x) || (a.x == b.x && a.y < b.y);
}

bool cmp_y(vec a, vec b) {
  return a.y < b.y;
}

ll sqr(ll a) {
  return a * a;
}

ll ans;
vec ansa, ansb;

ll dist(vec a, vec b) {
  return sqr(a.x - b.x) + sqr(a.y - b.y);
}

void upd_ans(vec a, vec b) {
  ll d = dist(a, b);
  if (d < ans) ans = d, ansa = a, ansb = b;
}

void rec(int l, int r) {
  if (r - l <= 3) {
    for (int i = l; i <= r; i++)
      for (int j = i + 1; j <= r; j++)
        upd_ans(a[i], a[j]);
    sort(a.begin() + l, a.begin() + r + 1, cmp_y);
    return;
  }
  int m = (l + r) / 2;
  ll mx = a[m].x;
  rec(l, m), rec(m + 1, r);
  vector <vec> t(r-l+1);
  merge(a.begin() + l, a.begin() + m + 1, a.begin() + m + 1, a.begin() + r + 1, t.begin(), cmp_y);
  for (int i = l; i <= r; i++) a[i] = t[i - l];
  int tsz = 0;
  for (int i = l; i <= r; i++) {
    if (sqr(a[i].x - mx) < ans) {
      for (int j = tsz - 1; j >= 0 && sqr(a[i].y - t[j].y) < ans; j--)
        upd_ans(a[i], t[j]);
      t[tsz++] = a[i];
    }
  }
}

int main() {
  cin >> n;
  a.resize(n);
  for (int i = 0; i < n; i++)
    a[i].read();
  sort(a.begin(), a.end(), cmp_x);
  ans = INF + 2;
  rec(0, n - 1);
  ansa.write(), ansb.write();
  return 0;
}
