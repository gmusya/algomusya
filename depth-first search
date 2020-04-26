#include <iostream>
#include <vector>

using namespace std;

struct graph {
    int n;
    vector <bool> used;
    vector <int> color;
    vector <vector <int>> g;

    explicit graph(int _n) {
        n = _n;
        used.resize(n);
        color.resize(n);
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

    void dfs(int v, int col) {
        used[v] = true;
        for (int u : g[v])
            if (!used[u])
                dfs(u, col);
        color[v] = col;
    }

};

int main () {
    int n, m;
    cin >> n >> m;
    graph g(n);
    g.read(m);
    int col = 0;
    for (int i = 0; i < n; i++)
        if (!g.used[i])
            g.dfs(i, col++);
    for (int i = 0; i < n; i++)
        cout << g.color[i] << ' ';
    return 0;
}
