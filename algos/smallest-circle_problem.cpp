#include <iostream>
#include <vector>
#include <iomanip>
#include <math.h>
#include <algorithm>
#include <random>
#include <chrono>

#define fsp(x) fixed << setprecision(x)

typedef long double ld;
typedef long long ll;

using namespace std;

const ld eps = 1e-6;

mt19937 gen(time(0));

ld myabs(ld x) {
  if (x > eps)
    return x;
  return -x;
}

struct circle {
  ld x, y, r2;
  void write() {
    cout << fsp(10) << x << ' ' << y << ' ' << sqrt(r2) << endl;
  }
};

struct line {
  // ax + by + c = 0
  ld a, b, c;
  void write() {
    cout << fsp(10) << a << " * x + " << b << " * y + " << c << " = 0" << endl;
  }
};

struct vec {
  ld x, y;
  void read() {
    cin >> x >> y;
  }
  void write() {
    cout << fsp(5) << "(" << x << "," << y << ")" << endl;
  }
  vec operator-(vec p) {
    vec a = {p.x - x, p.y - y};
    return a;
  }
  vec operator+(vec p) {
    vec a = {p.x + x, p.y + y};
    return a;
  }
  vec operator^(ld k) {
    vec a = {x * k, y * k};
    return a;
  }
  ld operator%(vec p) {
    return x * p.y - y * p.x;
  }
  ld operator*(vec p) {
    return x * p.x + y * p.y;
  }
  static ld sqr(ld x) {
    return x * x;
  }
  static ld dis2(vec a, vec b) {
    return sqr(a.x - b.x) + sqr(a.y - b.y);
  }
  static bool belongs_to_circle(vec a, circle o) {
    vec p = {o.x, o.y};
    return dis2(a, p) - eps < o.r2;
  }
  static vec intersect_line_line(line l, line r) {
    ld al = l.a, bl = l.b, cl = l.c;
    ld ar = r.a, br = r.b, cr = r.c;
    ld xres, yres;
    // l не параллельно r, поэтому они пересекаются
    // al * x + bl * y + cl = 0
    // ar * x + br * y + cr = 0

    // al * br * x + bl * br * y + cl * br = 0
    // ar * bl * x + bl * br * y + cr * bl = 0
    // x * (al * br - ar * bl) = cr * bl - cl * br
    xres = (cr * bl - cl * br) / (al * br - ar * bl);

    // al * ar * x + bl * ar * y + cl * ar = 0
    // ar * al * x + br * al * y + cr * al = 0
    // y * (bl * ar - br * al) = cr * al - cl * ar
    yres = (cr * al - cl * ar) / (bl * ar - br * al);

    vec res = {xres, yres};
    return res;
  }
  static line line_point_point(vec a, vec b) {
    ld ax = a.x, ay = a.y;
    ld bx = b.x, by = b.y;
    ld ares, bres, cres;
    if (abs(ay - by) < eps) {
      // не зависит от x
      ares = 0;
      bres = 1;
      cres = -ay;
    } else {
      ares = 1;
      // b * ay + c = -ax
      // b * by + c = -bx
      // b * (ay - by) = (bx - ax)
      bres = (bx - ax) / (ay - by);
      cres = -(bres * ay + ax);
    }
    line res = {ares, bres, cres};
    return res;
  }
  static vec per(vec p) {
    vec a = {-p.y, p.x};
    return a;
  }
  static circle circle_point_point(vec a, vec b) {
    vec o = ((a + b) ^ 0.5);
    ld r2 = dis2(a, o);
    circle res = {o.x, o.y, r2};
    return res;
  }
  static circle covering_circle(vec a, vec b, vec c) {
    // середины сторон
    if ((a - b) * (c - b) < eps)
      return circle_point_point(a, c);
    if ((a - c) * (b - c) < eps)
      return circle_point_point(a, b);
    if ((b - a) * (c - a) < eps)
      return circle_point_point(b, c);
    if (abs((a - b) % (a - c)) < eps) {
      circle ans1 = circle_point_point(a, b);
      circle ans2 = circle_point_point(a, c);
      circle ans3 = circle_point_point(b, c);
      if (ans1.r2 > ans2.r2)
        swap(ans1, ans2);
      if (ans2.r2 > ans3.r2)
        swap(ans2, ans3);
      return ans3;
    }
    vec midab = ((a + b) ^ 0.5);
    vec midac = ((a + c) ^ 0.5);
    // перпендикуляры к сторонам
    vec perab = per(a - b);
    vec perac = per(a - c);
    // взяли точку на перпендикуляре
    vec _midab = (midab + perab);
    vec _midac = (midac + perac);
    // выразили прямые
    line lineperab = line_point_point(midab, _midab);
    line lineperac = line_point_point(midac, _midac);
    // нашли центр описанной окружности
    vec reso = intersect_line_line(lineperab, lineperac);
    ld resr2 = dis2(reso, a);
    circle res = {reso.x, reso.y, resr2};
    return res;
  }
};

int main() {
  int n;
  cin >> n;
  vector <pair <int, int>> arr(n);
  for (int i = 0; i < n; i++)
    cin >> arr[i].first >> arr[i].second;
  sort(arr.begin(), arr.end());
  arr.resize(unique(arr.begin(), arr.end()) - arr.begin());
  n = (int)arr.size();
  if (n == 1) {
    cout << arr[0].first << ' ' << arr[0].second << '\n' << 0;
    return 0;
  }
  if (n == 2) {
    vec a = {(ld)arr[0].first, (ld)arr[0].second};
    vec b = {(ld)arr[1].first, (ld)arr[1].second};
    vec o = ((a + b) ^ 0.5);
    ld r = sqrt(vec::dis2(a, o));
    cout << fsp(10) << o.x << ' ' << o.y << '\n' << r;
    return 0;
  }
  vector <vec> p(n);
  for (int i = 0; i < n; i++)
    p[i] = {(ld)arr[i].first, (ld)arr[i].second};
  shuffle(p.begin(), p.end(), default_random_engine(gen()));
  circle ans = vec::covering_circle(p[0], p[1], p[2]);
  for (int i = 3; i < n; i++) {
    if (vec::belongs_to_circle(p[i], ans))
      continue;
    ans = vec::covering_circle(p[0], p[1], p[i]);
    for (int j = 2; j < i; j++) {
      if (vec::belongs_to_circle(p[j], ans))
        continue;
      ans = vec::covering_circle(p[0], p[i], p[j]);
      for (int k = 1; k < j; k++) {
        if (vec::belongs_to_circle(p[k], ans))
          continue;
        ans = vec::covering_circle(p[i], p[j], p[k]);
      }
    }
  }
  cout << fsp(10) << ans.x << ' ' << ans.y << '\n' << sqrt(ans.r2);
  return 0;
}
