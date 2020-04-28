#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1e9;

struct graph {
    int n;
    vector <int> distance;
    vector <vector <int>> g;

    explicit graph(int _n) {
        n = _n;
        g.resize(n);
    }

    void read(int m) {
        while (m--) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            g[u].push_back(v), g[v].push_back(u);
        }
    }

    void bfs(int s) {
        queue <int> q;
        distance.assign(n, INF);
        distance[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int u : g[v])
                if (distance[v] + 1 < distance[u]) {
                    distance[u] = distance[v] + 1;
                    q.push(u);
                }
        }
    }

};

int main () {
    int n;
    cin >> n;
    graph g(n);
    g.read(n - 1);
    g.bfs(0);
    int s = 0;
    for (int i = 1; i < n; i++)
        if (g.distance[s] < g.distance[i])
            s = i;
    g.bfs(s);
    int f = 0;
    for (int i = 1; i < n; i++)
        if (g.distance[f] < g.distance[i])
            f = i;
    cout << s + 1 << ' ' << f + 1 << ' ' << g.distance[f];
    return 0;
}
