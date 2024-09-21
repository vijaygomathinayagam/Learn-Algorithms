#include<iostream>
#include<vector>
#include<sstream>

// https://codeforces.com/edu/course/2/lesson/7/2/practice/contest/289391/problem/A

const char LEAVE_QUERY = '-';
const char ASK_QUERY = '?';

class DisjointSetUnion {
private:
	std::vector<int> p, size, max;

	int get(int set) {
		if (set == p[set])
			return set;
		return p[set] = get(p[set]);
	}

public:
	DisjointSetUnion(int n) {
		p.resize(n + 2);
		max.resize(n + 2);
		for (int i = 1; i <= n + 1; i++)
			p[i] = max[i] = i;
		size.assign(n + 2, 1);
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
		max[set1] = std::max(max[set1], max[set2]);
	}

	int get_max(int set) {
		return max[get(set)];
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
		char query_type;
		int pos;
		std::cin >> query_type >> pos;
		if (query_type == LEAVE_QUERY)
			disjoint_set_union.union_sets(pos, pos + 1);
		else if (query_type == ASK_QUERY) {
			int max = disjoint_set_union.get_max(pos);
			ss << (max == n + 1 ? - 1 : max) << std::endl;
		}
	}
	std::cout << ss.str();
	return 0;
}