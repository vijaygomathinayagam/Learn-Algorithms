#include<iostream>
#include<vector>
#include<stack>
#include<cmath>
#include<algorithm>
#include<sstream>

// https://codeforces.com/edu/course/2/lesson/7/3/practice/contest/289392/problem/B

class DSU {
private:
	std::vector<int> p, size;
	std::stack<int> checkpoints, cc_stack;
	std::stack<std::pair<std::pair<int, int>, std::pair<int, int>>> operations;
	int n, connected_components;

	int get(int set) {
		if (set == p[set])
			return set;
		return get(p[set]);
	}

public:
	DSU(int n) : n(n), connected_components(n) {
		reset();
	}

	void reset() {
		p.resize(n + 1);
		for (int i = 1; i <= n; i++)
			p[i] = i;
		size.assign(n + 1, 1);
		while (!checkpoints.empty())
			checkpoints.pop();
		while (!operations.empty())
			operations.pop();
		connected_components = n;
	}

	void persist() {
		checkpoints.push(operations.size());
		cc_stack.push(connected_components);
	}

	int get_connected_components() {
		return connected_components;
	}

	void rollback() {
		while (operations.size() > checkpoints.top()) {
			const auto& p_size_pair = operations.top();
			const auto& p_pair = p_size_pair.first;
			const auto& size_pair = p_size_pair.second;
			size[size_pair.first] = size_pair.second;
			p[p_pair.first] = p_pair.second;
			operations.pop();
		}
		checkpoints.pop();
		connected_components = cc_stack.top();
		cc_stack.pop();
	}

	void union_sets(int set1, int set2) {
		set1 = get(set1);
		set2 = get(set2);
		if (set1 == set2)
			return;
		if (size[set1] < size[set2])
			std::swap(set1, set2);
		if (!checkpoints.empty()) {
			std::pair<int, int> p_pair = {set2, p[set2]};
			std::pair<int, int> size_pair = {set1, size[set1]};
			operations.push({p_pair, size_pair});
		}
		p[set2] = set1;
		size[set1] += size[set2];
		connected_components--;
	}
};

struct Query {
	int u, v, index;
};

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	int n, m, k;
	std::cin >> n >> m;
	std::vector<std::pair<int, int>> edge_arr(m);
	for (int i = 0; i < m; i++)
		std::cin >> edge_arr[i].first >> edge_arr[i].second;
	std::cin >> k;
	std::vector<Query> query_arr(k);
	for (int i = 0; i < k; i++) {
		std::cin >> query_arr[i].u >> query_arr[i].v;
		query_arr[i].u--;
		query_arr[i].v--;
		query_arr[i].index = i;
	}
	const int block_size = std::sqrt(k);
	std::sort(query_arr.begin(), query_arr.end(), [&block_size](const auto &query1, const auto &query2) {
		if (query1.u / block_size == query2.u / block_size)
			return query1.v < query2.v;
		return query1.u / block_size < query2.u / block_size;
	});
	DSU dsu(n);
	std::vector<int> ans_arr(k);
	for (int i = 0; i < k; ) {
		dsu.reset();
		int current_block = query_arr[i].u / block_size;
		while (i < k && query_arr[i].v < (current_block + 1) * block_size) {
			dsu.persist();
			for (int j = query_arr[i].u; j <= query_arr[i].v; j++)
				dsu.union_sets(edge_arr[j].first, edge_arr[j].second);
			ans_arr[query_arr[i].index] = dsu.get_connected_components();
			dsu.rollback();
			i++;
		}
		int prev_r = (current_block + 1) * block_size - 1;
		while (i < k && query_arr[i].u / block_size == current_block) {
			for (auto j = query_arr[i].v; j > prev_r; j--)
				dsu.union_sets(edge_arr[j].first, edge_arr[j].second);
			dsu.persist();
			for (auto j = query_arr[i].u; j < (current_block + 1) * block_size; j++)
				dsu.union_sets(edge_arr[j].first, edge_arr[j].second);
			ans_arr[query_arr[i].index] = dsu.get_connected_components();
			dsu.rollback();
			prev_r = query_arr[i].v;
			i++;
		}
	}
	std::stringstream ss;
	for (const int& ans : ans_arr)
		ss << ans << std::endl;
	std::cout << ss.str();
	return 0;
}