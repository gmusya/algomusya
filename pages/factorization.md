## First Page
```c++
vector <pair <int, int>> factorization;
while (n != 1) {
  int d = lp[n];
  factorization.emplace_back(d, 0);
  while (n % d == 0) {
    factorization.back().second++;
    n /= d;
  }
}
```
