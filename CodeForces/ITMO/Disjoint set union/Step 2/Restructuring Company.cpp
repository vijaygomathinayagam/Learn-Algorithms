#include<iostream>
#include<vector>
#include<sstream>

// https://codeforces.com/edu/course/2/lesson/7/2/practice/contest/289391/problem/C

const int POINT_MERGE_QUERY = 1;
const int RANGE_MERGE_QUERY = 2;
const int ASK_QUERY = 3;

class DisjointSetUnion {
private:
	std::vector<int> p, size, next;

	int get(int set) {
		if (set == p[set])
			return set;
		return p[set] = get(p[set]);
	}

public: 
	DisjointSetUnion(int n) {
		p.resize(n + 1);
		next.resize(n + 1);
		for (int i = 1; i <= n; i++) {
			p[i] = i;
			next[i] = i + 1;
		}
		size.assign(n + 1, 1);
	}

	void union_sets(int set1, int set2) {
		set1 = get(set1);
		set2 = get(set2);
		if (set1 == set2)
			return;
		if (size[set1] < size[set2])
			std::swap(set1, set2);
		p[set2] = set1;
		size[set1] += size[set2];
	}

	bool is_same_set(int set1, int set2) {
		return get(set1) == get(set2);
	}

	int get_next(int set) {
		if (get(set) != get(next[set]))
			return next[set];
		return next[set] = get_next(next[set]);
	}
};

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	int n, q;
	std::cin >> n >> q;
	std::stringstream ss;
	DisjointSetUnion disjoint_set_union(n);
	for (auto i = 0; i < q; i++) {
		int type, u, v;
		std::cin >> type >> u >> v;
		if (type == POINT_MERGE_QUERY)
			disjoint_set_union.union_sets(u, v);
		else if (type == RANGE_MERGE_QUERY) {
			for (auto j = u + 1; j <= v; j = disjoint_set_union.get_next(j))
				disjoint_set_union.union_sets(j - 1, j);
		}
		else if (type == ASK_QUERY)
			ss << (disjoint_set_union.is_same_set(u, v) ? "YES" : "NO") << std::endl;
	}
	std::cout << ss.str();
	return 0;
}