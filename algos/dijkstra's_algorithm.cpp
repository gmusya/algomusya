#include <iostream>
#include <vector>
#include <set>

typedef long long ll;

using namespace std;

const ll INF = 1e18;

struct graph {
    int n;
    vector <ll> d;
    vector <vector <pair <int, ll>>> g;

    explicit graph(int _n) {
        n = _n;
        d.resize(n, INF);
        g.resize(n);
    }

    void read(int m) {
        while (m--) {
            int u, v, w;
            cin >> u >> v >> w;
            u--, v--;
            g[u].push_back({v, w}), g[v].push_back({u, w});
        }
    }

    void dijkstra(int s) {
        set <pair <ll, int>> q;
        d[s] = 0;
        q.insert({0, s});
        while (!q.empty()) {
            ll v = q.begin()->second;
            q.erase(q.begin());
            for (auto &tmp : g[v]) {
                int u = tmp.first;
                ll w = tmp.second;
                if (d[v] + w < d[u]) {
                    if (d[u] != INF) q.erase({d[u], u});
                    d[u] = d[v] + w;
                    q.insert({d[u], u});
                }
            }
        }
    }

};

int main () {
    int n, m;
    cin >> n >> m;
    graph g(n);
    g.read(m);
    int s;
    cin >> s;
    g.dijkstra(s - 1);
    for (int i = 0; i < n; i++)
        cout << g.d[i] << ' ';
    return 0;
}
