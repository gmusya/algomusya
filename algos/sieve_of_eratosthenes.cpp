#include <iostream>
#include <vector>

using namespace std;

void sieve_of_eratosthenes (vector <int> &lp, vector <int> &pr) {
  int n = lp.size() - 1;
  for (int i = 2; i <= n; i++) {
    if (!lp[i]) pr.push_back(i), lp[i] = i;
    for (int j = 0; j < (int)pr.size() && pr[j] <= lp[i] && i * pr[j] <= n; j++)
      lp[pr[j] * i] = pr[j];
  }
}

int main () {
  int n;
  cin >> n;
  vector <int> lp(n + 1), pr;
  sieve_of_eratosthenes(lp, pr);
  for (int p : pr)
    cout << p << ' ';
  return 0;
}
