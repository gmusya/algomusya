#include <iostream>
#include <vector>
#include <algorithm>

typedef long long ll;

using namespace std;

const ll INF = 1e9;

struct vec {
  ll x, y;
  vec() = default;
  vec(ll _x, ll _y) {
    x = _x;
    y = _y;
  }
  void read () {
    cin >> x >> y;
  }
  void write () {
    cout << '(' << x << ", " << y << ')' << '\n';
  }
  vec operator - (vec a) const {
    return { x - a.x, y - a.y };
  }
  ll operator % (vec a) const {
    return (x * a.y - y * a.x);
  }
  bool belong_to_angle(vec a, vec b, vec o) {
    vec p = {x, y};
    if ((b - o) % (p - o) >= 0 && (p - o) % (a - o) >= 0 && (b - o) % (a - o) >= 0) return true;
    return (b - o) % (p - o) <= 0 && (p - o) % (a - o) <= 0 && (b - o) % (a - o) <= 0;
  }
};

int main() {
  ll n;
  cin >> n;
  vector<vec> a(n);
  for (ll i = 0; i < n; i++)
    a[i].read();
  if ((a[1] - a[0]) % (a[2] - a[1]) < 0)
    reverse(a.begin(), a.end());
  int q;
  cin >> q;
  for (int it = 0; it < q; it++) {
    vec Point{};
    Point.read();
    int Left = 1, Right = n - 1;
    bool kek = false;
    vec Line{};
    if (Point.belong_to_angle(a[n - 1], a[1], a[0])) {
      Line = Point - a[0];
      while (Left + 1 < Right) {
        int M = (Left + Right) / 2;
        if (Point.belong_to_angle(a[Left], a[M], a[0])) Right = M;
        else Left = M;
      }
      if (Point.belong_to_angle(a[0], a[Left], a[Right])) {
        cout << "In\n";
        continue;
      }
    }
    else {
      Line = a[0] - Point;
      kek = true;
    }
    int L = 0, R = n - 1;
    while (L != R) {
      int M = (L + R + 1) / 2;
      if (Line % (a[M] - a[0]) > 0) R = M - 1;
      else L = M;
    }
    int Middle = L;
    int L1 = 0, R1 = Middle;
    int L2 = Middle, R2 = n;
    if (Line % (a[Middle] - a[0]) == 0) R1--, L2++;
    if (kek) swap(L1, L2), swap(R1, R2);
    while (L1 < R1) {
      int M = (L1 + R1 + 1) / 2;
      if ((a[M % n] - a[(M - 1 + n) % n]) % (Point - a[M % n]) < 0) R1 = M - 1;
      else L1 = M;
    }
    Left = L1;
    while (L2 < R2) {
      int M = (L2 + R2 + 1) / 2;
      if ((a[M % n] - a[(M - 1 + n) % n]) % (Point - a[M % n]) > 0) R2 = M - 1;
      else L2 = M;
    }
    Right = L2;
    Left %= n, Right %= n;
    cout << "answer = (" << a[Left].x << ", " << a[Left].y << "), (" << a[Right].x << ", " << a[Right].y << ')' << '\n';
  }
  return 0;
}
