#include<iostream>
#include<vector>
#include<sstream>

// https://codeforces.com/edu/course/2/lesson/7/1/practice/contest/289390/problem/A

const std::string GET_QUERY_TYPE = "get";
const std::string GET_UNION_TYPE = "union";

class DisjoinSetUnion {
private:
	int n;
	std::vector<int> p;
	std::vector<int> r;

	int get(int a) {
		if (a == p[a])
			return a;
		return (p[a] = get(p[a]));
	}

public:
	DisjoinSetUnion(int n) : n(n) {
		p.resize(n + 1);
		for (int i = 1; i <= n; i++)
			p[i] = i;
		r.assign(n + 1, 1);
	}

	bool is_same_set(int a, int b) {
		return get(a) == get(b);
	}

	void union_set(int a, int b) {
		a = get(a);
		b = get(b);
		if (r[a] == r[b])
			r[a]++;
		if (r[a] > r[b])
			p[b] = a;
		else
			p[a] = b;
	}
};

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	int n, m;
	std::cin >> n >> m;
	DisjoinSetUnion disjoint_set_union(n);
	std::stringstream ss;
	for (int i = 0; i < m; i++) {
		std::string query_type;
		int u, v;
		std::cin >> query_type >> u >> v;
		if (query_type == GET_QUERY_TYPE)
			ss << (disjoint_set_union.is_same_set(u, v) ? "YES" : "NO") << std::endl;
		else
			disjoint_set_union.union_set(u, v);
	}
	std::cout << ss.str();
	return 0;
}