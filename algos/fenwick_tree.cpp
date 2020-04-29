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
    void upd (int pos, int val) {
        while (pos < n) {
            t[pos] += val;
            pos |= pos + 1;
        }
    }
    int get (int pos) {
        int result = 0;
        while (pos != -1) {
            result += t[pos]; 
            pos &= pos + 1;
            pos--; 
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
