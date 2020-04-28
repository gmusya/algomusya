#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct query {
    int id, cnt;
};

struct node {
    int x, y, sz;
    node *l, *r;
    node()= default;
    explicit node(int _x) {
        x = _x;
        y = (rand() << 16) + rand();
        sz = 1;
        l = r = nullptr;
    }
    static int size(node *p) {
        return p ? p->sz : 0;
    }
    static void upd_size(node *p) {
        p->sz = 1 + size(p->l) + size(p->r);
    }
    static pair<node *, node *> split(node *p, int x) {
        if (!p) return {};
        if (p->x <= x) {
            pair<node *, node *> q = split(p->r, x);
            p->r = q.first;
            upd_size(p);
            return {p, q.second};
        }
        pair<node *, node *> q = split(p->l, x);
        p->l = q.second;
        upd_size(p);
        return {q.first, p};
    }
    static node *merge(node *l, node *r) {
        if (!l) return r;
        if (!r) return l;
        if (l->y > r->y) {
            l->r = merge(l->r, r);
            upd_size(l);
            return l;
        }
        r->l = merge(l, r->l);
        upd_size(r);
        return r;
    }
    static void insert(int val, node *&root) {
        pair<node *, node *> q = split(root, val);
        node *t = new node(val);
        root = merge(q.first, merge(t, q.second));
    }
    static void erase(int val, node *&p) {
        if (p->x == val) {
            p = merge(p->l, p->r);
            if (p) upd_size(p);
            return;
        }
        if (p->x > val) {
            erase(val, p->l);
            upd_size(p);
            return;
        }
        erase(val, p->r);
        upd_size(p);
    }
    static int get(int x, node *&root) {
        pair<node *, node *> q = split(root, x - 1);
        int ans = size(q.second);
        merge(q.first, q.second);
        return ans;
    }
};

int n, q;
vector <node*> treap;

struct graph {
    vector<bool> used;
    vector<int> color, ans;
    vector<vector<int>> g;
    vector<map<int, int>> cnt;
    vector<vector<query>> queries;
    graph()=default;
    void read_edges(int m) {
        while (m--) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            g[u].push_back(v);
            g[v].push_back(u);
        }
    }
    void read_queries(int q) {
        for (int i = 0; i < q; i++) {
            int v, x;
            cin >> v >> x;
            v--;
            queries[v].push_back({ i, x });
        }
    }
    void graph_build(int n, int q) {
        used.resize(n), color.resize(n);
        ans.resize(n);
        g.resize(n);
        cnt.resize(n), queries.resize(n);
        treap.resize(n);
        for (int i = 0; i < n; i++)
            cin >> color[i];
        read_edges(n - 1);
        read_queries(q);
    }
    void dfs(int v) {
        used[v] = true;
        cnt[v][color[v]] = 1;
        node::insert(1, treap[v]);
        for (int u : g[v])
            if (!used[u]) {
                dfs(u);
                if (cnt[u].size() > cnt[v].size()) {
                    swap(cnt[u], cnt[v]);
                    swap(treap[u], treap[v]);
                }
                for (auto now : cnt[u]) {
                    int key = now.first;
                    int val = now.second;
                    if (cnt[v].find(key) != cnt[v].end()) node::erase(cnt[v][key], treap[v]);
                    cnt[v][key] += val;
                    node::insert(cnt[v][key], treap[v]);
                }
            }
        for (auto now : queries[v]) {
            int id = now.id;
            int val = now.cnt;
            ans[id] = node::get(val, treap[v]);
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> q;
    graph g;
    g.graph_build(n, q);
    g.dfs(0);
    for (int i = 0; i < q; i++)
        cout << g.ans[i] << '\n';
    return 0;
}
