#include <iostream>

using namespace std;

int mod (int val, int modulo) {
    return (val % modulo + modulo) % modulo;
}

pair <pair <int, int>, int> gcd(int a, int b) {
    if (a % b == 0) {
        int x = 1, y = 1 - (a /  b);
        return { {x, y}, b};
    }
    auto tmp = gcd(b, a % b);
    int x = tmp.first.second, y = tmp.first.first - (a / b) * tmp.first.second;
    return { {x, y}, tmp.second};
}

pair <bool, pair <int, int>> solve (int a, int b, int c) {
    auto tmp = gcd(a, b);
    int x = tmp.first.first, y = tmp.first.second, g = tmp.second;
    if (c % g) return {0, {0, 0}};
    x *= c / g, y *= c / g;
    x = mod(x, b / g);
    y = (c - a * x) / b;
    return {1, {x, y}};
}

int main () {
    int a, b, c;
    cin >> a >> b >> c;
    auto tmp = solve(a, b, c);
    bool tf = tmp.first;
    int x = tmp.second.first, y = tmp.second.second;
    if (!tf) cout << "Impossible" << endl;
    else cout << x << " " << y;
    return 0;
}
