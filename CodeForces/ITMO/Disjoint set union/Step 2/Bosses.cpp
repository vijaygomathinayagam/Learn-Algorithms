#include<iostream>
#include<vector>
#include<sstream>

// https://codeforces.com/edu/course/2/lesson/7/2/practice/contest/289391/problem/D

const int SUBORDINATE_QUERY = 1;
const int LEVEL_QUERY = 2;

class DisjointSetUnion {
private:
	std::vector<int> p, level;

	int set_root_and_level(int set) {
		if (p[set] == set)
			return set;
		int root = set_root_and_level(p[set]);
		level[set] += level[p[set]];
		p[set] = root;
		return root;
	}

public:
	DisjointSetUnion(int n) {
		p.resize(n + 1);
		for (auto i = 1; i <= n; i++)
			p[i] = i;
		level.assign(n + 1, 0);
	}

	void union_sets(int set1, int set2) {
		level[set1] = 1;
		p[set1] = set2;
	}

	int get_level(int set) {
		set_root_and_level(set);
		return level[set];
	}
};

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	int n, m;
	std::cin >> n >> m;
	DisjointSetUnion disjoint_set_union(n);
	std::stringstream ss;
	for (int i = 0; i < m; i++) {
		int query_type;
		std::cin >> query_type;
		if (query_type == SUBORDINATE_QUERY) {
			int a, b;
			std::cin >> a >> b;
			disjoint_set_union.union_sets(a, b);
		}
		else if (query_type == LEVEL_QUERY) {
			int c;
			std::cin >> c;
			ss << disjoint_set_union.get_level(c) << std::endl;
		}
	}
	std::cout << ss.str();
	return 0;
}