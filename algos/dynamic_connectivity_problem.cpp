#include <iostream>
#include <vector>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <random>
#include <ctime>

typedef long long ll;

using namespace std;

vector <ll> t;
vector <pair <ll, ll>> e;
unordered_map <ll, ll> pos, birth;
vector <ll> dsu, dsu_rank;
vector <vector <ll>> tree;

void add(ll v, ll tl, ll tr, ll l, ll r, ll pos) {
    if (l > r) return;
    if (l == tl && r == tr) {
        tree[v].push_back(pos);
        return;
    }
    ll tm = (tl + tr) / 2;
    add(v * 2, tl, tm, l, min(tm, r), pos);
    add(v * 2 + 1, tm + 1, tr, max(tm + 1, l), r, pos);
}

ll get(ll v) {
    if (dsu[v] == v) return v;
    return get(dsu[v]);
}

void dsu_merge(ll u, ll v, vector <pair<ll, pair<ll, ll>>> &upd, ll &comp) {
    u = get(u);
    v = get(v);
    if (u != v) comp--;
    if (u == v) return;
    if (dsu_rank[u] < dsu_rank[v])
        swap(u, v);
    upd.push_back({ v, {u, dsu_rank[u] } });
    if (dsu_rank[u] == dsu_rank[v]) ++dsu_rank[u];
    dsu[v] = u;
}

void solve(ll v, ll tl, ll tr, vector <pair <ll, ll>> &e, vector <ll> &ans, ll comp) {
    vector <pair <ll, pair <ll, ll>>> upd;
    for (ll i = 0; i < tree[v].size(); i++)
        dsu_merge(e[tree[v][i]].first, e[tree[v][i]].second, upd, comp);
    if (tl == tr) {
        ans[tl] = comp;
        for (ll i = (ll)upd.size() - 1; i >= 0; i--) {
            dsu[upd[i].first] = upd[i].first;
            dsu_rank[upd[i].second.first] = upd[i].second.second;
        }
        return;
    }
    ll tm = (tl + tr) / 2;
    solve(v * 2, tl, tm, e, ans, comp);
    solve(v * 2 + 1, tm + 1, tr, e, ans, comp);
    for (ll i = (ll)upd.size() - 1; i >= 0; i--) {
        dsu[upd[i].first] = upd[i].first;
        dsu_rank[upd[i].second.first] = upd[i].second.second;
    }
}

mt19937_64 gen(time(0));

int main() {
    srand(time(0));
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll n, q;
    cin >> n >> q;
    if (q == 0) return 0;
    tree.resize(4 * q + 10);
    ll cnt = -1;
    for (ll i = 0; i < q; i++) {
        char c;
        cin >> c;
        if (c == '?') t.push_back(++cnt);
        if (c == '+') {
            ++cnt;
            ll u, v;
            cin >> u >> v;
            u--, v--;
            if (u > v) swap(u, v);
            ll hash = n * u + v;
            pos[hash] = e.size();
            birth[hash] = cnt;
            e.push_back({ u, v });
        }
        if (c == '-') {
            ++cnt;
            ll u, v;
            cin >> u >> v;
            u--, v--;
            if (u > v) swap(u, v);
            ll hash = n * u + v;
            add(1, 0, q - 1, birth[hash], cnt, pos[hash]);
            pos.erase(hash);
            birth.erase(hash);
        }
    }
    for (auto now : pos) {
        ll hash = now.first;
        add(1, 0, q - 1, birth[hash], q - 1, now.second);
    }
    ll comp = n;
    dsu.resize(n), dsu_rank.resize(n);
    iota(dsu.begin(), dsu.end(), 0);
    vector <ll> ans(q);
    solve(1, 0, q - 1, e, ans, comp);
    for (ll i = 0; i < t.size(); i++)
        cout << ans[t[i]] << endl;
    return 0;
}
