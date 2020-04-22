#include <iostream>
#include <vector>
#include <math.h>
#include <set>

typedef long long ll;

using namespace std;

pair <int, int> gcd(int a, int b) {
    if (a % b == 0) {
        int x = 1, y = 1 - (a /  b);
        return { x, y };
    }
    auto tmp = gcd(b, a % b);
    int x = tmp.second, y = tmp.first - (a / b) * tmp.second;
    return { x, y };
}

int main() {
    ll m, a, b;
    ll k = ceil(sqrt(m)) + 1;
    vector<ll> kx(k), y(k);
    kx[0] = 1;
    for (ll i = 1; i < k; i++)
        kx[i] = (kx[i - 1] * a) % m;
    auto tmp = gcd(kx[k - 1], m);
    ll _x = tmp.first, _y = tmp.second;
    y[k - 1] = (((_x % m + m) % m) * b) % m;
    for (int i = k - 2; i >= 0; i--)
        y[i] = (y[i + 1] * a) % m;
    for (ll i = 1; i < k; i++)
        kx[1] = (kx[1] * a) % m;
    for (ll i = 2; i < k; i++)
        kx[i] = (kx[i - 1] * kx[1]) % m;
    set<int> match;
    for (ll i = 0; i < k; i++)
        match.insert(y[i]);
    bool flag = false;
    ll answer = -1;
    for (ll i = 0; i < k; i++) {
        if (flag) break;
        if (match.find(kx[i]) != match.end()) {
            flag = true;
            for (ll j = 0; j < k; j++) {
                if (kx[i] == y[j]) {
                    answer = i * k + j;
                    break;
                }
            }
        }
    }
    if (answer == -1)
        cout << "no solution" << endl;
    else
        cout << answer << endl;
    return 0;
}
