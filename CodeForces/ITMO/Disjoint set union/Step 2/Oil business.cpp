#include<iostream>
#include<vector>
#include<algorithm>
#include<sstream>

// https://codeforces.com/edu/course/2/lesson/7/2/practice/contest/289391/problem/H

struct Edge {
	int u, v, w, index;
};

class DSU {
private:
	std::vector<int> p, size;

	int get(int set) {
		if (set == p[set])
			return set;
		return p[set] = get(p[set]);
	}

public:
	DSU(const int &n) {
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

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	int n, m;
	long long s;
	std::cin >> n >> m >> s;
	std::vector<Edge> edge_arr(m);
	for (int i = 0; i < m; i++) {
		std::cin >> edge_arr[i].u >> edge_arr[i].v >> edge_arr[i].w;
		edge_arr[i].index = i + 1;
	}
	std::sort(edge_arr.begin(), edge_arr.end(), [](const Edge& e1, const Edge& e2) {
		return e1.w > e2.w;
	});
	DSU dsu(n);
	int ei = 0;
	std::vector<Edge> cycle_edge_arr;
	for (; ei < edge_arr.size(); ei++) {
		const Edge& edge = edge_arr[ei];
		if (dsu.is_same_set(edge.u, edge.v)) {
			cycle_edge_arr.push_back(edge);
			continue;
		}
		if (dsu.union_sets(edge.u, edge.v) == n)
			break;
	}
	std::vector<int> index_arr;
	int current_s = 0;
	for (auto i = edge_arr.size() - 1; i > ei; i--) {
		if (current_s + edge_arr[i].w <= s) {
			index_arr.push_back(edge_arr[i].index);
			current_s += edge_arr[i].w;
		}
		else
			break;
	}
	for (int i = cycle_edge_arr.size() - 1; i >= 0; i--) {
		if (current_s + cycle_edge_arr[i].w <= s) {
			index_arr.push_back(cycle_edge_arr[i].index);
			current_s += cycle_edge_arr[i].w;
		}
		else
			break;
	}
	std::sort(index_arr.begin(), index_arr.end());
	std::stringstream ss;
	ss << index_arr.size() << std::endl;
	for (const int& index : index_arr)
		ss << index << " ";
	std::cout << ss.str();
	return 0;
}