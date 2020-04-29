#include <iostream>

typedef long long ll;

using namespace std;

ll bin_exp(ll a, ll p, ll m) {
    ll res = 1;
    while (p) {
        if (p & 1) res = (res * a) % m;
        a = (a * a) % m;
        p /= 2;
    }
    return res;
}

int main () {
    ll a, p, m;
    cin >> a >> p >> m;
    cout << bin_exp(a, p, m);
    return 0;
}
