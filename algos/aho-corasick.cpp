#include <iostream>
#include <vector>
#include <string>
#include <map>

#define endl '\n'

using namespace std;

struct prefix_tree {
    struct vertex {
        int p = -1, sp = -1, par = 0, dep = 0;
        char symb;
        vector <int> id;
        map <char, int> next, d;
    };
    int cnt;
    int root;
    int tail;
    vector <vertex> ver;

    explicit prefix_tree(int n) {
        cnt = 0;
        root = 0;
        tail = 1;
        ver.resize(n);
    }

    int d(int v, char c) {
        if (ver[v].d.find(c) != ver[v].d.end()) return ver[v].d[c];
        if (ver[v].next.find(c) != ver[v].next.end()) return ver[v].d[c] = ver[v].next[c];
        if (v == root) return ver[v].d[c] = root;
        return ver[v].d[c] = d(p(v), c);
    }
    int p(int v) {
        if (ver[v].p != -1) return ver[v].p;
        if (v == root || ver[v].par == root) return ver[v].p = root;
        return ver[v].p = d(p(ver[v].par), ver[v].symb);
    }
    int sp(int v) {
        if (ver[v].sp != -1) return ver[v].sp;
        if (!ver[p(v)].id.empty()) return ver[v].sp = p(v);
        if (v == root) return ver[v].sp = root;
        return ver[v].sp = sp(p(v));
    }

    void add(string s) {
        int v = root;
        int it = 0;
        while (it != s.size() && ver[v].next.find(s[it]) != ver[v].next.end())
            v = ver[v].next[s[it++]];
        while (it != s.size()) {
            int u = tail++;
            ver[v].next[s[it]] = u;
            ver[u].symb = s[it];
            ver[u].par = v;
            ver[u].dep = ver[v].dep + 1;
            v = u;
            it++;
        }
        ver[v].id.push_back(cnt++);
    }

    vector <vector <int>> corasick(string t) {
        vector <vector <int>> ans(cnt);
        int v = root;
        int it = 0;
        while (it != t.size()) {
            char c = t[it];
            v = d(v, c);
            int u = v;
            while (u != root) {
                for (int i : ver[u].id)
                    ans[i].push_back(it - ver[u].dep + 2);
                u = sp(u);
            }
            it++;
        }
        return ans;
    }
};

int main() {
    string t;
    cin >> t;
    int n;
    cin >> n;
    vector <string> s(n);
    int sum = 1;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        sum += s[i].size();
    }
    prefix_tree trie(sum);
    for (int i = 0; i < n; i++)
        trie.add(s[i]);
    vector <vector <int>> ans = trie.corasick(t);
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i].size() << " ";
        for (int j = 0; j < ans[i].size(); j++)
            cout << ans[i][j] << " ";
        cout << endl;
    }
    return 0;
}
