#include <iostream>
#include <vector>

using namespace std;

struct fenwick_tree {
    int n;
    vector <int> t;
    explicit fenwick_tree(int _n) {
        n = _n;
        t.resize(n);
    }
    void update (int i, int val) {
        while (i < n) {
            t[i] += val;
            i |= i + 1;
        }
    }
    int get (int i) {
        int result = 0;
        while (i != -1) {
            result += t[i];
            i &= i + 1;
            i--;
        }
        return result;
    }
};

int main () {
    int n;
    cin >> n;
    fenwick_tree t(n);
    int q;
    cin >> q;
    while (q--) {
        char c;
        cin >> c;
        if (c == '?') {
            int pos;
            cin >> pos;
            pos--;
            cout << t.get(pos) << endl;
        }
        if (c == '!') {
            int pos, val;
            cin >> pos >> val;
            pos--;
            t.update(pos, val);
        }
    }
    return 0;
}
