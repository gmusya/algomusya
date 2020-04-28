#include <iostream>
#include <vector>
#include <deque>

using namespace std;

const int INF = 1e9;

struct graph {
    int n;
    vector <bool> used;
    vector <int> distance;
    vector <vector <pair <int, int>>> g;

    explicit graph(int _n) {
        n = _n;
        used.resize(n);
        distance.resize(n, INF);
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

    void bfs(int s) {
        deque <int> dq;
        distance[s] = 0;
        dq.push_back(s);
        while (!dq.empty()) {
            int v = dq.front();
            dq.pop_front();
            if (used[v]) continue;
            used[v] = true;
            for (auto &tmp : g[v]) {
                int u = tmp.first, w = tmp.second;
                if (distance[v] + w < distance[u]) {
                    distance[u] = distance[v] + w;
                    if (w == 1) dq.push_back(u);
                    else dq.push_front(u);
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
    g.bfs(s - 1);
    for (int i = 0; i < n; i++)
        cout << g.distance[i] << ' ';
    return 0;
}
