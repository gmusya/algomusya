#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

long long cnt = 0;

vector <int> z_function(string &s) {
    int n = s.size();
    vector <int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r) z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
}

int get_z(vector <int> &z, int i) {
    if (0 <= i && i < (int) z.size())
        return z[i];
    return 0;
}

void output_tandems(bool left, int l, int k1, int k2) {
    // solve l1 <= k1 && l - k2 <= l1 && l1 <= l && !(left && l1 == l)
    if (left && l <= k1 && 0 <= k2) cnt--;
    cnt += max(0, (min(l, k1) - max(1, (l - k2)) + 1));
}

void solve(string s, int shift = 0) {
    int n = s.size();
    if (n == 1) return;
    int nu = n / 2, nv = n - nu;
    string u = s.substr(0, nu), v = s.substr(nu, nv);
    string ru = string(u.rbegin(), u.rend()), rv = string(v.rbegin(), v.rend());
    solve(u, shift);
    solve(v, shift + nu);
    string uv = ru + "#" + rv, vu = v + "#" + u;
    vector<int> z1 = z_function(ru), z2 = z_function(vu), z3 = z_function(uv), z4 = z_function(v);
    for (int cntr = 0; cntr < n; ++cntr) {
        int l, k1, k2;
        if (cntr < nu) {
            l = nu - cntr;
            k1 = get_z(z1, nu - cntr);
            k2 = get_z(z2, nv + 1 + cntr);
        }
        else {
            l = cntr - nu + 1;
            k1 = get_z(z3, nu + 1 + nv - 1 - (cntr - nu));
            k2 = get_z(z4, (cntr - nu) + 1);
        }
        if (k1 + k2 >= l)
            output_tandems(cntr < nu, l, k1, k2);
    }
}

int main() {
    string s;
    cin >> s;
    solve(s);
    cout << cnt;
    return 0;
}
