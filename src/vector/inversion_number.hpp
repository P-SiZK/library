#ifndef VECTOR_INVERSION_NUMBER
#define VECTOR_INVERSION_NUMBER

#include "src/datastructure/fenwick_tree.hpp"
#include "src/vector/coordinate_compression.hpp"

#include <vector>

template<class T>
long long inversion_number(std::vector<T> const &v) {
	int const N = v.size();
	FenwickTree<int> ft(N);
	CoordinateCompression cc(v);
	long long res = 0;
	for (int i = 0; i < N; ++i) {
		int idx = cc.get(v[i]);
		res += i - ft.sum(idx);
		ft.add(idx, 1);
	}
	return res;
}

#endif // VECTOR_INVERSION_NUMBER
