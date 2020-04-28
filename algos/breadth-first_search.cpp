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
        distance.resize(n, INF);
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
