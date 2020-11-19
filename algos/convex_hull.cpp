#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct vec {
  int x, y;
  void read() {
    cin >> x >> y;
  }
  void write() {
    cout << "(" << x << ", " << y << ")\n";
  }
  int operator% (vec a) { // косое произведение
    return x * a.y - y * a.x;
  }
  int mod2() {
    return x * x + y * y;
  }
  bool operator< (vec a) {
    if (x != a.x)
      return x < a.x;
    return y < a.y;
  }
  vec operator- (vec a) {
    return {x - a.x, y - a.y};
  }
};

int main() {
  int n;
  cin >> n;
  vector <vec> p(n);
  for (int i = 0; i < n; i++)
    p[i].read();
  {
    vec tmp = p[0]; // точка, которая точно будет в выпуклой оболочке
    for (int i = 0; i < n; i++)
      if (p[i] < tmp)
        tmp = p[i];
    sort(p.begin(), p.end(), [&](vec a, vec b) {
      vec _a = a - tmp;
      vec _b = b - tmp;
      int mult = _a % _b;
      if (mult) // если a, b, tmp не на одной прямой
        return mult > 0; // угол (_a, _b) направлен против часовй стрелки
      return _a.mod2() < _b.mod2();
    });
  }
  vector <vec> hull;
  for (vec &c : p) {
    while (hull.size() >= 2) {
      vec a = (c - hull[hull.size() - 1]);
      vec b = (hull[hull.size() - 2] - hull[hull.size() - 1]);
      if (a % b <= 0) // угол (a, b) должен быть положительным
        hull.pop_back();
      else
        break;
    }
    hull.push_back(c);
  }
  cout << hull.size() << '\n';
  for (vec &a : hull)
    a.write();
  return 0;
}
