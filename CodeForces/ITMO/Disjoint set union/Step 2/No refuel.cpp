#include<iostream>
#include<vector>
#include<algorithm>

// https://codeforces.com/edu/course/2/lesson/7/2/practice/contest/289391/problem/G

class DisjointSetUnion {
private:
	std::vector<int> p, size;

	int get(int set) {
		if (set == p[set])
			return set;
		return p[set] = get(p[set]);
	}

public:
	DisjointSetUnion(int n) {
		p.resize(n + 1);
		for (int i = 1; i <= n; i++)
			p[i] = i;
		size.assign(n + 1, 1);
	}

	int union_sets(int set1, int set2) {
		set1 = get(set1);
		set2 = get(set2);
		if (set1 == set2)
			return size[set1];
		if (size[set1] < size[set2])
			std::swap(set1, set2);
		p[set2] = set1;
		size[set1] += size[set2];
		return size[set1];
	}

	bool is_same_set(int set1, int set2) {
		return get(set1) == get(set2);
	}
};

struct Edge {
	int u, v, w;
};

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	int n, k;
	std::cin >> n >> k;
	std::vector<Edge> edge_arr(k);
	for (int i = 0; i < k; i++)
		std::cin >> edge_arr[i].u >> edge_arr[i].v >> edge_arr[i].w;
	std::sort(edge_arr.begin(), edge_arr.end(), [](const Edge& e1, const Edge& e2) {
		return e1.w < e2.w;
	});
	DisjointSetUnion dsu(n);
	for (int i = 0; i < k; i++) {
		if (dsu.is_same_set(edge_arr[i].u, edge_arr[i].v))
			continue;
		if (dsu.union_sets(edge_arr[i].u, edge_arr[i].v) == n) {
			std::cout << edge_arr[i].w << std::endl;
			return 0;
		}
	}
	return 0;
}