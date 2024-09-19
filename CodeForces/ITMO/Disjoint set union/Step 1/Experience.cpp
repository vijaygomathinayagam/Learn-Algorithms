#include<iostream>
#include<vector>
#include<sstream>

// https://codeforces.com/edu/course/2/lesson/7/1/practice/contest/289390/problem/C

const std::string QUERY_ADD = "add";
const std::string QUERY_JOIN = "join";
const std::string QUERY_GET = "get";

class DisjointSetUnion {
private:
	std::vector<int> p, exp, r;

	int get(int set) {
		int root = set;
		while (root != p[root])
			root = p[root];
		while (p[set] != root) {
			int parent_of_set = p[set];
			exp[set] += exp[parent_of_set];
			p[set] = p[parent_of_set];
		}
		return root;
	}

public:
	DisjointSetUnion(int n) {
		p.resize(n + 1);
		for (int i = 1; i <= n; i++)
			p[i] = i;
		exp.assign(n + 1, 0);
		r.assign(n + 1, 1);
	}

	int get_exp(int set) {
		int result = 0;
		while (set != p[set]) {
			result += exp[set];
			set = p[set];
		}
		result += exp[set];
		return result;
	}

	void add(int set, int v) {
		exp[get(set)] += v;
	}

	void union_sets(int set1, int set2) {
		set1 = get(set1);
		set2 = get(set2);
		if (set1 == set2)
			return;
		if (r[set1] == r[set2])
			r[set1]++;
		if (r[set1] > r[set2]) {
			p[set2] = set1;
			exp[set2] += -1 * exp[set1];
		}
		else {
			p[set1] = set2;
			exp[set1] += -1 * exp[set2];
		}
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
		std::string query_type;
		std::cin >> query_type;
		if (query_type == QUERY_ADD) {
			int u, v;
			std::cin >> u >> v;
			disjoint_set_union.add(u, v);
		}
		else if (query_type == QUERY_GET) {
			int u;
			std::cin >> u;
			ss << disjoint_set_union.get_exp(u) << std::endl;
		}
		else if (query_type == QUERY_JOIN) {
			int u, v;
			std::cin >> u >> v;
			disjoint_set_union.union_sets(u, v);
		}
	}
	std::cout << ss.str();
	return 0;
}