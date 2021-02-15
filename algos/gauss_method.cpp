#include <iostream>
#include <vector>
#include <iomanip>

#define fsp(x) fixed << setprecision(x)

using namespace std;

typedef long double ld;
typedef vector <ld> vld;
typedef vector <vld> vvld;

const ld eps = 1e-9;

int main() {
  int n;
  cin >> n;
  vvld a(n, vld(n));
  vld b(n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++)
      cin >> a[i][j];
    cin >> b[i];
  }
  for (int row = 0, col = 0; row < n && col < n; row++, col++) {
    int id = -1;
    for (int i = row; i < n; i++) {
      if (id == -1) {
        if (abs(a[i][col]) > eps)
          id = i;
        continue;
      }
      if (abs(a[i][col]) > abs(a[id][col]))
        id = i;
    }
    if (id == -1) {
      row--;
      continue;
    }
    swap(a[id], a[row]);
    swap(b[id], b[row]);
    for (int i = row + 1; i < n; i++) {
      ld k = -a[i][col] / a[row][col];
      for (int j = 0; j < n; j++)
        a[i][j] += k * a[row][j];
      b[i] += k * b[row];
    }
  }
  bool tmp = false;
  for (int row = 0; row < n; row++) {
    bool flag = false;
    for (int col = 0; col < n; col++)
      if (abs(a[row][col]) > eps)
        flag = true;
    if (!flag && abs(b[row]) > eps) {
      cout << "impossible\n";
      return 0;
    }
    if (!flag)
      tmp = true;
  }
  if (tmp) {
    cout << "infinity\n";
    return 0;
  }
  for (int row = n - 1; row >= 0; row--) {
    int id = -1;
    for (int col = 0; col < n; col++)
      if (abs(a[row][col]) > eps) {
        id = col;
        break;
      }
    for (int i = row - 1; i >= 0; i--) {
      if (abs(a[i][id]) > eps) {
        ld k = -a[i][id] / a[row][id];
        for (int j = 0; j < n; j++)
          a[i][j] += k * a[row][j];
        b[i] += k * b[row];
      }
    }
  }
  cout << "single\n";
  for (int i = 0; i < n; i++)
    cout << fsp(10) << b[i] / a[i][i] << ' ';
  return 0;
}
