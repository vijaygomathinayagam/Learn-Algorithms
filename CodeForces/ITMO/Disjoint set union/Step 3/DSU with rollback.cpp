#include<iostream>
#include<vector>
#include<stack>
#include<sstream>

// https://codeforces.com/edu/course/2/lesson/7/3/practice/contest/289392/problem/A

const std::string UNION_QUERY = "union";
const std::string PERSIST_QUERY = "persist";
const std::string ROLLBACK_QUERY = "rollback";

class DSU {
private:
	std::vector<int> p, size;
	std::stack<int> checkpoints;
	std::stack<int> cc_stack;
	std::stack<std::pair<std::pair<int, int>, std::pair<int, int>>> operations;
	int connected_components;

	int get(int set) {
		if (set == p[set])
			return set;
		return get(p[set]);
	}

public:
	DSU(int n) : connected_components(n) {
		p.resize(n + 1);
		for (int i = 1; i <= n; i++)
			p[i] = i;
		size.assign(n + 1, 1);
	}

	void persist() {
		checkpoints.push(operations.size());
		cc_stack.push(connected_components);
	}

	void rollback() {
		while (operations.size() > checkpoints.top()) {
			auto p_size_pair = operations.top();
			std::pair<int, int> p_pair = p_size_pair.first;
			std::pair<int, int> size_pair = p_size_pair.second;
			p[p_pair.first] = p_pair.second;
			size[size_pair.first] = size_pair.second;
			operations.pop();
		}
		checkpoints.pop();
		connected_components = cc_stack.top();
		cc_stack.pop();
	}

	int get_connected_components() {
		return connected_components;
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

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	int n, m;
	std::cin >> n >> m;
	std::stringstream ss;
	DSU dsu(n);
	for (int i = 0; i < m; i++) {
		std::string query_type;
		std::cin >> query_type;
		if (query_type == UNION_QUERY) {
			int u, v;
			std::cin >> u >> v;
			dsu.union_sets(u, v);
			ss << dsu.get_connected_components() << std::endl;
		}
		else if (query_type == PERSIST_QUERY)
			dsu.persist();
		else if (query_type == ROLLBACK_QUERY) {
			dsu.rollback();
			ss << dsu.get_connected_components() << std::endl;
		}
	}
	std::cout << ss.str();
	return 0;
}