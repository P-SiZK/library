#include <vector>

using namespace std;

template<class T, class F>
class SparseTable {
private:
	vector<vector<T>> table;
	vector<int> log_table;
	F f;

public:
	SparseTable(const vector<T> &v, F f) : f(f) {
		int n = v.size(), h = 1;
		while ((1 << h) <= n) ++h;
		table.assign(h, vector<T>(n));
		log_table.assign(n + 1, 0);
		for (int i = 2; i <= n; ++i) log_table[i] = log_table[i >> 1] + 1;

		for (int i = 0; i < n; ++i) table[0][i] = v[i];
		for (int i = 1, k = 1; i < h; ++i, k <<= 1)
			for (int j = 0; j < n; ++j)
				table[i][j] =
					f(table[i - 1][j], table[i - 1][min(j + k, n - 1)]);
	}

	T query(int l, int r) { // [l, r)
		int k = log_table[r - l];
		return f(table[k][l], table[k][r - (1 << k)]);
	}
};
