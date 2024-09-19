#include<iostream>
#include<vector>
#include<sstream>

// https://codeforces.com/edu/course/2/lesson/7/1/practice/contest/289390/problem/B

const std::string GET_QUERY_TYPE = "get";
const std::string UNION_QUERY_TYPE = "union";

struct GetQueryResult {
	int min, max, size;
};

class DisjointSetUnion {
private:
	int n;
	std::vector<int> p, size;
	std::vector<int> min, max;

	int get(int set) {
		if (set == p[set])
			return set;
		return (p[set] = get(p[set]));
	}

public:
	DisjointSetUnion(int n): n(n) {
		p.resize(n + 1);
		min.resize(n + 1);
		max.resize(n + 1);
		for (int i = 1; i <= n; i++)
			p[i] = min[i] = max[i] = i;
		size.assign(n + 1, 1);
	}

	GetQueryResult get_size_min_max(int set) {
		set = get(set);
		return { min[set], max[set], size[set] };
	}

	void union_sets(int set1, int set2) {
		set1 = get(set1);
		set2 = get(set2);
		if (set1 == set2)
			return;
		if (size[set1] < size[set2]) {
			std::swap(set1, set2);
		}
		p[set2] = set1;
		size[set1] += size[set2];
		min[set1] = std::min(min[set1], min[set2]);
		max[set1] = std::max(max[set1], max[set2]);
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
		if (query_type == GET_QUERY_TYPE) {
			int u;
			std::cin >> u;
			GetQueryResult result = disjoint_set_union.get_size_min_max(u);
			ss << result.min << " " << result.max << " " << result.size << std::endl;
		}
		else if (query_type == UNION_QUERY_TYPE) {
			int u, v;
			std::cin >> u >> v;
			disjoint_set_union.union_sets(u, v);
		}
	}
	std::cout << ss.str();
	return 0;
}