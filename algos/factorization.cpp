#include <iostream>
#include <vector>

using namespace std;

void sieve_of_eratosthenes(vector <int> &lp, vector <int> &pr) {
    int n = lp.size() - 1;
    for (int i = 2; i <= n; i++) {
        if (!lp[i]) pr.push_back(i), lp[i] = i;
        for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= n; j++)
            lp[pr[j] * i] = pr[j];
    }
}

void factorize (int n, vector <int> &lp) {
    if (n == 1) {
        cout << "1 = 1";
        return;
    }
    cout << n << " = ";
    vector <pair <int, int>> factorization;
    while (n!= 1) {
        int d = lp[n];
        factorization.emplace_back(d, 0);
        while (n % d == 0) {
            factorization.back().second++;
            n /= d;
        }
    }
    for (int i = 0; i < factorization.size(); i++) {
        cout << factorization[i].first;
        if (factorization[i].second > 1) cout << "^" << factorization[i].second;
        if (i != factorization.size() - 1) cout << " * ";
    }
}

int main () {
    int n;
    cin >> n;
    vector <int> lp(n + 1), pr;
    sieve_of_eratosthenes(lp, pr);
    int q;
    cin >> q;
    while (q--) {
        int x;
        cin >> x;
        factorize(x, lp);
    }
    return 0;
}
