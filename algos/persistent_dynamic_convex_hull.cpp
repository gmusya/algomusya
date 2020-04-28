#include <iostream>
#include <vector>

typedef long long ll;

using namespace std;

struct vec {
    ll x = 0, y = 0;
    vec()= default;
    vec(ll _x, ll _y) {
        x = _x;
        y = _y;
    }
    vec(vec const &pt) {
        x = pt.x;
        y = pt.y;
    }
    void read () {
        cin >> x >> y;
    }
    void write () const {
        cout << '(' << x << ", " << y << ')' << '\n';
    }
    vec operator - (vec a) {
        return { x - a.x, y - a.y };
    }
    ll operator % (vec a)  {
        return (x * a.y - y * a.x);
    }
    bool belong_to_angle(vec a, vec b, vec o) const {
        vec p = {x, y};
        if ((b - o) % (p - o) >= 0 && (p - o) % (a - o) >= 0 && (b - o) % (a - o) >= 0) return true;
        return (b - o) % (p - o) <= 0 && (p - o) % (a - o) <= 0 && (b - o) % (a - o) <= 0;
    }
};

struct node {
    vec x;
    ll y{}, sz{};
    node *l{}, *r{};
    node() = default;
    explicit node(vec _x) {
        x = _x;
        y = (rand() << 16) + rand();
        sz = 1;
        l = r = nullptr;
    }
    explicit node (node* cur) {
        if (!cur) {
            sz = 0;
            return;
        }
        x = cur->x;
        y = cur->y;
        sz = cur->sz;
        l = cur->l;
        r = cur->r;
    }
    static ll get_size(node *p) {
        return p ? p->sz : 0;
    }
    static void upd_size(node *p) {
        p->sz = 1 + get_size(p->l) + get_size(p->r);
    }
    static pair <node*, node*> split(node *p, ll x) {
        if (!p) return {};
        node *t = new node(p);
        if (get_size(t->l) + 1 <= x) {
            pair <node*, node*> q = split(t->r, x - get_size(t->l) - 1);
            t->r = q.first;
            upd_size(t);
            return { t, q.second };
        }
        pair <node*, node*> q = split(t->l, x);
        t->l = q.second;
        upd_size(t);
        return { q.first, t };
    }
    static node* merge(node *l, node *r) {
        node *t;
        if (!l) {
            t = new node(r);
            return t;
        }
        if (!r) {
            t = new node(l);
            return t;
        }
        if (l->y > r->y) {
            t = new node(l);
            t->r = merge(l->r, r);
            upd_size(t);
            return t;
        }
        t = new node(r);
        t->l = merge(l, r->l);
        upd_size(t);
        return t;
    }
    static node* insert(const vec& pt, ll x, node* &root) {
        pair <node*, node*> q = split(root, x);
        node *t = new node(pt);
        return root = merge(q.first, merge(t, q.second));
    }
    static pair <node*, node*> cut(ll l, ll r, node* &root) {
        pair <node*, node*> q1;
        auto tmp1 = split(root, r);
        if (tmp1.first) q1.first = (tmp1.first);
        if (tmp1.second) q1.second = (tmp1.second);
        pair <node*, node*> q2;
        auto tmp2 = split(q1.first, l - 1);
        if (tmp2.first) q2.first = (tmp2.first);
        if (tmp2.second) q2.second = (tmp2.second);
        root = (merge(q2.first, q1.second));
        if (root->sz == 0) root = nullptr;
        return {root, q2.second};
    }
    static vec get(ll pos, node *t, bool tf = true) {
        if (tf) pos++;
        if (!t) return {};
        if (get_size(t->l) + 1 < pos)
            return get(pos - get_size(t->l) - 1, t->r, false);
        if (get_size(t->l) + 1 == pos)
            return t->x;
       return get(pos, t->l, false);
    }
    static void write(node* p) {
        if (!p) return;
        write(p->l);
        p->x.write();
        write(p->r);
    }
};

int main() {
    ll q;
    cin >> q;
    vector <node*> T(q + 1);
    {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            vec pt;
            pt.read();
            T[0] = node::insert(pt, i + 1, T[0]);
        }
    }
    vector <vec> a(T[0]->sz + q + 1);
    for (int it = 1; it <= q; it++) {
        int ver;
        cin >> ver;
        T[it] = new node (T[ver]);
        int n = T[it]->sz;
        vec Point{};
        Point.read();
        int Left, Right;
        bool kek = false;
        vec Line{};
        a[n - 1] = node::get(n - 1, T[it]);
        a[1] = node::get(1, T[it]);
        a[0] = node::get(0, T[it]);
        if (Point.belong_to_angle(a[n - 1], a[1], a[0]))
            Line = Point - a[0];
        else {
            Line = a[0] - Point;
            kek = true;
        }
        int L = 0, R = n - 1;
        while (L != R) {
            int M = (L + R + 1) / 2;
            a[M] = node::get(M, T[it]);
            if (Line % (a[M] - a[0]) > 0) R = M - 1;
            else L = M;
        }
        int Middle = L;
        int L1 = 0, R1 = Middle;
        int L2 = Middle, R2 = n;
        a[Middle] = node::get(Middle, T[it]);
        if (Line % (a[Middle] - a[0]) == 0) R1--, L2++;
        if (kek) swap(L1, L2), swap(R1, R2);
        while (L1 < R1) {
            int M = (L1 + R1 + 1) / 2;
            a[M % n] = node::get(M % n, T[it]);
            a[(M - 1 + n) % n] = node::get((M - 1 + n) % n, T[it]);
            if ((a[M % n] - a[(M - 1 + n) % n]) % (a[M % n] - Point) > 0) R1 = M - 1;
            else L1 = M;
        }
        Left = L1;
        while (L2 < R2) {
            int M = (L2 + R2 + 1) / 2;
            a[M % n] = node::get(M % n, T[it]);
            a[(M - 1 + n) % n] = node::get((M - 1 + n) % n, T[it]);
            if ((a[M % n] - a[(M - 1 + n) % n]) % (a[M % n] - Point) < 0) R2 = M - 1;
            else L2 = M;
        }
        Right = L2;
        Left %= n, Right %= n;
        if (Left < Right) {
            T[it] = node::cut(Left + 2, Right, T[it]).first;
            T[it] = node::insert(Point, Left + 1, T[it]);
            node::write(T[it]);
            continue;
        }
        T[it] = node::cut(Left + 2, n, T[it]).first;
        T[it] = node::cut(1, Right, T[it]).first;
        T[it] = node::insert(Point, 0, T[it]);
        node::write(T[it]);
    }
    return 0;
}
