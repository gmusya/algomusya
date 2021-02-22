#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector <int> z_function(string &s) {
  int n = s.size();
  vector <int> z(n);
  int l = 0, r = 0;
  for (int i = 1; i < n; i++) {
    z[i] = max(0, min(r - i, z[i - l]));
    while (i < n && s[z[i]] == s[i + z[i]]) z[i]++;
    if (i + z[i] > r) l = i, r = i + z[i];
  }
  return z;
}

int main() {
  string s;
  cin >> s;
  vector <int> z = z_function(s);
  for (int i = 0; i < (int)z.size(); i++)
    cout << z[i] << ' ';
  return 0;
}
