#include<iostream>
#include<vector>
#include<algorithm>

// https://codeforces.com/edu/course/2/lesson/7/2/practice/contest/289391/problem/E

struct Edge {
	int u, v, w;
};

bool edge_comparator(const Edge& edge1, const Edge& edge2) {
	return edge1.w < edge2.w;
}

class DisjointSetUnion {
private:
	std::vector<int> p, size;

	int get(int set) {
		if (set == p[set])
			return set;
		return (p[set] = get(p[set]));
	}

public:
	DisjointSetUnion(int n) {
		p.resize(n + 1);
		for (int i = 1; i <= n; i++)
			p[i] = i;
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
};

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	int n, m;
	std::cin >> n >> m;
	std::vector<Edge> edge_arr(m);
	for (int i = 0; i < m; i++)
		std::cin >> edge_arr[i].u >> edge_arr[i].v >> edge_arr[i].w;
	std::sort(edge_arr.begin(), edge_arr.end(), edge_comparator);
	long long ans = 0;
	DisjointSetUnion disjoint_set_union(n);
	for (int i = 0; i < m; i++) {
		if (disjoint_set_union.is_same_set(edge_arr[i].u, edge_arr[i].v))
			continue;
		ans += edge_arr[i].w;
		disjoint_set_union.union_sets(edge_arr[i].u, edge_arr[i].v);
	}
	std::cout << ans << std::endl;
	return 0;
}