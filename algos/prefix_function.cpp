#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector <int> prefix_function(string &s) {
  int n = s.size();
  vector <int> p(n);
  for (int i = 1; i < (int)s.size(); i++) {
    int k = p[i - 1];
    while (k > 0 && s[i] != s[k]) k = p[k - 1];
    if (s[i] == s[k]) k++;
    p[i] = k;
  }
  return p;
}

int main () {
  string s;
  cin >> s;
  vector <int> p = prefix_function(s);
  for (int i = 0; i < (int)p.size(); i++)
    cout << p[i] << ' ';
  return 0;
}
