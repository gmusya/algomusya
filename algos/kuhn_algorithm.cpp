#include <iostream>
#include <vector>

#define endl '\n'

using namespace std;

int n, m;
vector <bool> used;
vector <int> mt;
vector <vector <int>> g;

bool dfs(int v) {
    if (used[v])
        return false;
    used[v] = true;
    for (auto to : g[v]) {
        if (mt[to] == -1 || dfs(mt[to])) {
            mt[to] = v;
            return true;
        }
    }
    return false;
}

int main() {
    cin >> n >> m;
    g.resize(n);
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        while (k != 0) {
            g[i].push_back(k - 1);
            cin >> k;
        }
    }
    mt.resize(m, -1);
    for (int i = 0; i < n; i++) {
        used.assign(n, false);
        dfs(i);
    }
    vector <pair <int, int>> answer;
    for (int i = 0; i < m; i++)
        if (mt[i] != -1)
            answer.push_back({ mt[i] + 1, i + 1 });
    cout << answer.size() << endl;
    for (auto now : answer)
        cout << now.first << " " << now.second << endl;
    return 0;
}
