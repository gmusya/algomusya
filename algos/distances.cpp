#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <algorithm>

#define fsp(x) fixed << setprecision(x)

using namespace std;

typedef __int128 lll;
typedef long long ll;
typedef long double ld;

const lll INF = 1e14;

lll myabs(lll x) {
  if (x < 0)
    return -x;
  return x;
}

struct vec {
  lll x, y;
  void read() {
    ll a, b;
    cin >> a >> b;
    x = a, y = b;
  }
  lll operator*(vec p) {  // скалярное произведение
    return x * p.x + y * p.y;
  }
  lll operator%(vec p) {  // "векторное" произведение
    return x * p.y - y * p.x;
  }
  vec operator^(lll t) {
    vec a = {t * x, t * y};
    return a;
  }
  vec operator-(vec p) {
    vec a = {x - p.x, y - p.y};
    return a;
  }
  vec operator+(vec p) {
    vec a = {x + p.x, y + p.y};
    return a;
  }
  lll mod2() {
    return x * x + y * y;
  }
  ld mod() {
    return sqrt((ll)mod2());
  }
  static int sig(lll val) {
    if (val > 0)
      return 1;
    if (val == 0)
      return 0;
    return -1;
  }
  static ll dis_point_point2(vec a, vec b) {
    return (a - b).mod2();
  }
  static ld dis_point_point(vec a, vec b) {
    return sqrt(dis_point_point2(a, b));
  }
  static ld dis_point_line(vec a, vec b, vec c) {
    lll s = myabs((b - a) % (c - a));  // удвоенная площадь треугольника abc
    ld bc = dis_point_point(b, c);
    ld ah = (ld)s / bc;
    return ah;
  }
  static ld dis_point_segment(vec a, vec b, vec c) {
    if ((a - b) * (c - b) >= 0 && (a - c) * (b - c) >= 0)  // проекция a падает внутрь bc
      return dis_point_line(a, b, c);
    return min(dis_point_point(a, b), dis_point_point(a, c));
  }
  static ld dis_point_ray(vec a, vec b, vec c) {
    if ((a - b) * (c - b) >= 0)  // проекция a падает на луч
      return dis_point_line(a, b, c);
    return dis_point_point(a, b);
  }
  static bool intersect_segment_segment(vec a, vec b, vec c, vec d) {
    int flag1 = sig((a - b) % (c - b)) * sig((a - b) % (d - b));
    int flag2 = sig((c - d) % (a - d)) * sig((c - d) % (b - d));
    return (flag1 <= 0 && flag2 <= 0 && !(flag1 == 0 && flag2 == 0));
  }
  static ld dis_segment_segment(vec a, vec b, vec c, vec d) {
    if (intersect_segment_segment(a, b, c, d))
      return 0;
    return min({dis_point_segment(a, c, d), dis_point_segment(b, c, d),
      dis_point_segment(c, a, b), dis_point_segment(d, a, b)});
  }
  static ld dis_segment_ray(vec a, vec b, vec c, vec d) {
    vec newd = (d + ((d - c) ^ INF));  // превращаем луч в отрезок, ТОЛЬКО чтобы проверить пересечение
    if (intersect_segment_segment(a, b, c, newd))
      return 0;
    return min({dis_point_ray(a, c, d), dis_point_ray(b, c, d), dis_point_segment(c, a, b)});
  }
  static ld dis_segment_line(vec a, vec b, vec c, vec d) {
    vec newc = (c + ((c - d) ^ INF));
    vec newd = (d + ((d - c) ^ INF));
    if (intersect_segment_segment(a, b, newc, newd))
      return 0;
    return min(dis_point_line(a, c, d), dis_point_line(b, c, d));
  }
  static ld dis_ray_ray(vec a, vec b, vec c, vec d) {
    vec newb = (b + ((b - a) ^ INF));
    vec newd = (d + ((d - c) ^ INF));
    if (intersect_segment_segment(a, newb, c, newd))
      return 0;
    return min(dis_point_ray(a, c, d), dis_point_ray(c, a, b));
  }
  static ld dis_ray_line(vec a, vec b, vec c, vec d) {
    vec newb = (b + ((b - a) ^ INF));
    vec newc = (c + ((c - d) ^ INF));
    vec newd = (d + ((d - c) ^ INF));
    if (intersect_segment_segment(a, newb, newc, newd))
      return 0;
    return dis_point_line(a, c, d);
  }
  static ld dis_line_line(vec a, vec b, vec c, vec d) {
    vec newa = (a + ((a - b) ^ INF));
    vec newb = (b + ((b - a) ^ INF));
    vec newc = (c + ((c - d) ^ INF));
    vec newd = (d + ((d - c) ^ INF));
    if (intersect_segment_segment(newa, newb, newc, newd))
      return 0;
    return dis_point_line(a, c, d);
  }
};

int main() {
  vec a, b, c, d;
  a.read(), b.read(), c.read(), d.read();
  // 1. Расстояние от точки A до точки C
  cout << fsp(10) << vec::dis_point_point(a, c) << endl;
  // 2. Расстояние от точки A до отрезка CD
  cout << fsp(10) << vec::dis_point_segment(a, c, d) << endl;
  // 3. Расстояние от точки A до луча CD
  cout << fsp(10) << vec::dis_point_ray(a, c, d) << endl;
  // 4. Расстояние от точки А до прямой CD
  cout << fsp(10) << vec::dis_point_line(a, c, d) << endl;
  // 5. Расстояние от отрезка AB до точки C
  cout << fsp(10) << vec::dis_point_segment(c, a, b) << endl;
  // 6. Расстояние от отрезка AB до отрезка CD
  cout << fsp(10) << vec::dis_segment_segment(a, b, c, d) << endl;
  // 7. Расстояние от отрезка AB до луча CD
  cout << fsp(10) << vec::dis_segment_ray(a, b, c, d) << endl;
  // 8. Расстояние от отрезка AB до прямой CD
  cout << fsp(10) << vec::dis_segment_line(a, b, c, d) << endl;
  // 9. Расстояние от луча AB до точки C
  cout << fsp(10) << vec::dis_point_ray(c, a, b) << endl;
  // 10. Расстояние от луча AB до отрезка CD
  cout << fsp(10) << vec::dis_segment_ray(c, d, a, b) << endl;
  // 11. Расстояние от луча AB до луча CD
  cout << fsp(10) << vec::dis_ray_ray(a, b, c, d) << endl;
  // 12. Расстояние от луча AB до прямой CD
  cout << fsp(10) << vec::dis_ray_line(a, b, c, d) << endl;
  // 13. Расстояние от прямой AB до точки C
  cout << fsp(10) << vec::dis_point_line(c, a, b) << endl;
  // 14. Расстояние от прямой AB до отрезка CD
  cout << fsp(10) << vec::dis_segment_line(c, d, a, b) << endl;
  // 15. Расстояние от прямой AB до луча CD
  cout << fsp(10) << vec::dis_ray_line(c, d, a, b) << endl;
  // 16. Расстояние от прямой AB до прямой CD
  cout << fsp(10) << vec::dis_line_line(a, b, c, d) << endl;
  return 0;
}
