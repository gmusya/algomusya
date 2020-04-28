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
    void write () {
        cout << '(' << x << ", " << y << ')' << '\n';
    }
    vec operator - (vec a) {
        return { x - a.x, y - a.y };
    }
    ll operator % (vec a)  {
        return (x * a.y - y * a.x);
    }
    bool belong_to_angle(vec a, vec b, vec o) {
        vec p = {x, y};
        if ((b - o) % (p - o) >= 0 && (p - o) % (a - o) >= 0 && (b - o) % (a - o) >= 0) return true;
        return (b - o) % (p - o) <= 0 && (p - o) % (a - o) <= 0 && (b - o) % (a - o) <= 0;
    }
};

struct node {
    vec x;
    ll y, sz;
    node *l, *r;
    node() {}
    node(vec _x) {
        x = _x;
        y = (rand() << 16) + rand();
        sz = 1;
        l = r = nullptr;
    }
    static ll get_size(node *p) {
        return p ? p->sz : 0;
    }
    static void upd_size(node *p) {
        p->sz = 1 + get_size(p->l) + get_size(p->r);
    }
    static pair <node*, node*> split(node *p, ll x) {
        if (!p) return {};
        if (get_size(p->l) + 1 <= x) {
            pair <node*, node*> q = split(p->r, x - get_size(p->l) - 1);
            p->r = q.first;
            upd_size(p);
            return { p, q.second };
        }
        pair <node*, node*> q = split(p->l, x);
        p->l = q.second;
        upd_size(p);
        return { q.first, p };
    }
    static node* merge(node *l, node *r) {
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
    static void insert(vec pt, ll x, node* &root) {
        pair <node*, node*> q = split(root, x);
        node *t = new node(pt);
        root = merge(q.first, merge(t, q.second));
    }
    static node* cut(ll l, ll r, node* &root) {
        if (l > r) return {};
        pair <node*, node*> q1 = split(root, r);
        pair <node*, node*> q2 = split(q1.first, l - 1);
        root = merge(q2.first, q1.second);
        return q2.second;
    }
    static void paste(node* p, ll pos, node* &root) {
        pair <node*, node*> q = split(root, pos - 1);
        root = merge(q.first, merge(p, q.second));
    }
    static vec get(ll pos, node *root) {
        pos++;
        node *p = cut(pos, pos, root);
        vec ans = p->x;
        paste(p, pos, root);
        return ans;
    }
    static void write(node* p) {
        if (!p) return;
        write(p->l);
        p->x.write();
        write(p->r);
    }
};

int main() {
    node *T = 0;
    {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            vec pt;
            pt.read();
            node::insert(pt, i + 1, T);
        }
    }
    ll q;
    cin >> q;
    vector <vec> a(T->sz + q + 1);
    while (q--) {
        int n = T->sz;
        vec Point{};
        Point.read();
        int Left, Right;
        bool kek = false;
        vec Line{};
        a[n - 1] = node::get(n - 1, T);
        a[1] = node::get(1, T);
        a[0] = node::get(0, T);
        if (Point.belong_to_angle(a[n - 1], a[1], a[0]))
            Line = Point - a[0];
        else {
            Line = a[0] - Point;
            kek = true;
        }
        int L = 0, R = n - 1;
        while (L != R) {
            int M = (L + R + 1) / 2;
            a[M] = node::get(M, T);
            if (Line % (a[M] - a[0]) > 0) R = M - 1;
            else L = M;
        }
        int Middle = L;
        int L1 = 0, R1 = Middle;
        int L2 = Middle, R2 = n;
        a[Middle] = node::get(Middle, T);
        if (Line % (a[Middle] - a[0]) == 0) R1--, L2++;
        if (kek) swap(L1, L2), swap(R1, R2);
        while (L1 < R1) {
            int M = (L1 + R1 + 1) / 2;
            a[M % n] = node::get(M % n, T);
            a[(M - 1 + n) % n] = node::get((M - 1 + n) % n, T);
            if ((a[M % n] - a[(M - 1 + n) % n]) % (a[M % n] - Point) > 0) R1 = M - 1;
            else L1 = M;
        }
        Left = L1;
        while (L2 < R2) {
            int M = (L2 + R2 + 1) / 2;
            a[M % n] = node::get(M % n, T);
            a[(M - 1 + n) % n] = node::get((M - 1 + n) % n, T);
            if ((a[M % n] - a[(M - 1 + n) % n]) % (a[M % n] - Point) < 0) R2 = M - 1;
            else L2 = M;
        }
        Right = L2;
        Left %= n, Right %= n;
        if (Left < Right) {
            node::cut(Left + 2, Right, T);
            node::insert(Point, Left + 1, T);
            node::write(T);
            continue;
        }
        node::cut(Left + 2, n, T);
        node::cut(1, Right, T);
        node::insert(Point, 0, T);
        node::write(T);
    }
    return 0;
}
