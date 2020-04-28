#include <iostream>
#include <vector>
#include <algorithm>

typedef long long ll;

using namespace std;

struct segment_tree {
    struct ver {
        ver() = default;
        ll mod = 0;
        ll sum = 0;
    };
    int sz = 0;
    vector <ver> t;
    void push (int v, int tl, int tr) {
        int tm = (tl + tr) / 2;
        t[v * 2].mod += t[v].mod;
        t[v * 2 + 1].mod += t[v].mod;
        t[v].mod = 0;
    }
    void setvalue(int v, int tl, int tr) {
        int tm = (tl + tr) / 2;
        t[v].sum = t[v * 2].sum + t[v * 2 + 1].sum +
                   t[v * 2].mod * (tm - tl + 1) + t[v * 2 + 1].mod * (tr - tm);
    }
    void build (int v, int tl, int tr, vector <int> &a) {
        if (tl == tr) {
            t[v].sum = a[tl];
            return;
        }
        int tm = (tl + tr) / 2;
        build(v * 2, tl, tm, a);
        build(v * 2 + 1, tm + 1, tr, a);
        setvalue(v, tl, tr);
    }
    ll get (int v, int tl, int tr, int l, int r) {
        if (l > r) return 0;
        if (l == tl && r == tr) return t[v].sum + t[v].mod * (tr - tl + 1);
        push(v, tl, tr);
        setvalue(v, tl, tr);
        int tm = (tl + tr) / 2;
        ll s1 = get(v * 2, tl, tm, l, min(tm, r));
        ll s2 = get(v * 2 + 1, tm + 1, tr, max(tm + 1, l), r);
        return s1 + s2;
    }
    void update(int v, int tl, int tr, int l, int r, int val) {
        if (l > r) return;
        if (l == tl && r == tr) {
            t[v].mod += val;
            return;
        }
        push(v, tl, tr);
        int tm = (tl + tr) / 2;
        update(v * 2, tl, tm, l, min(tm, r), val);
        update(v * 2 + 1, tm + 1, tr, max(tm + 1, l), r, val);
        setvalue(v, tl, tr);
    }
    ll get(int l, int r) {
        return get(1, 0, sz - 1, l, r);
    }
    void update(int l, int r, int val) {
        update(1, 0, sz - 1, l, r, val);
    }
    void build (vector <int> &a) {
        sz = a.size();
        t.resize(sz << 2);
        build(1, 0, sz - 1, a);
    }
};

using namespace std;

int main () {
    int n;
    cin >> n;
    vector <int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    segment_tree t;
    t.build(a);
    int q;
    cin >> q;
    while (q--) {
        char c;
        cin >> c;
        if (c == '+') {
            int l, r, val;
            cin >> l >> r >> val;
            l--, r--;
            t.update(l, r, val);
        }
        if (c == '?') {
            int l, r;
            cin >> l >> r;
            l--, r--;
            cout << t.get(l, r) << endl;
        }
    }
    return 0;
}
