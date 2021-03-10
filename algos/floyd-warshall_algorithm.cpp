#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector <ll> vl;
typedef vector <vl> vvl;

const ll INF = 1e18;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vvl mat(n, vl(n));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) {
      cin >> mat[i][j];
      if (mat[i][j] == -1)
        mat[i][j] = INF;
    }
  for (int k = 0; k < n; k++)
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++)
      cout << mat[i][j] << ' ';
    cout << '\n';
  }
  return 0;
}
