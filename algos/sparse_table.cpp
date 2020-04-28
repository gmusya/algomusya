#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int n, q;
	cin >> n >> q;
	vector <int> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	vector <int> lg(n + 1);
	for (int i = 2; i < n + 1; i++)
		lg[i] = lg[i >> 1] + 1;
	vector <vector <int>> st(n, vector <int>(lg[n] + 1));
	for (int i = 0; i < n; i++)
		st[i][0] = a[i];
	for (int p = 1; p <= lg[n]; p++)
		for (int i = 0; i < n; i++) {
			st[i][p] = st[i][p - 1];
			if (i + (1 << (p - 1)) < n)
				st[i][p] = min(st[i][p], st[i + (1 << (p - 1))][p - 1]);
		}
	while (q--) {
		int l, r;
		cin >> l >> r;
		l--, r--;
		int _lg = lg[r - l + 1];
		cout << min(st[l][_lg], st[r - (1 << _lg) + 1][_lg]) << '\n';
	}
	return 0;
}
