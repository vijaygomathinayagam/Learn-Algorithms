#include<iostream>
#include<vector>
#include<unordered_set>
#include<sstream>
#include<stack>

// https://codeforces.com/edu/course/2/lesson/7/1/practice/contest/289390/problem/D

const std::string QUERY_ASK = "ask";
const std::string QUERY_CUT = "cut";

struct Query{
	std::string query_type;
	int u, v;
};

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

	bool is_same_set(int set1, int set2) {
		set1 = get(set1);
		set2 = get(set2);
		return set1 == set2;
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
};

void get_solution(const int &n, const std::vector<std::unordered_set<int>> &edges,
	const std::vector<Query> &query_arr) {
	std::stringstream ss;
	DisjointSetUnion disjoint_set_union(n);
	std::stack<bool> ans_arr;
	for (int i = query_arr.size() - 1; i >= 0; i--) {
		if (query_arr[i].query_type == QUERY_ASK)
			ans_arr.push(disjoint_set_union.is_same_set(query_arr[i].u, query_arr[i].v));
		else if (query_arr[i].query_type == QUERY_CUT)
			if (edges[query_arr[i].u].find(query_arr[i].v) != edges[query_arr[i].u].end()
				|| edges[query_arr[i].v].find(query_arr[i].u) != edges[query_arr[i].v].end())
				disjoint_set_union.union_sets(query_arr[i].u, query_arr[i].v);
	}
	for (;!ans_arr.empty(); ans_arr.pop())
		ss << (ans_arr.top() ? "YES" : "NO") << std::endl;
	std::cout << ss.str();
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	int n, m, k;
	std::cin >> n >> m >> k;
	std::vector<std::unordered_set<int>> edges(n + 1);
	for (int i = 0; i < m; i++) {
		int u, v;
		std::cin >> u >> v;
		edges[u].insert(v);
		edges[v].insert(u);
	}
	std::vector<Query> query_arr(k);
	for (int i = 0; i < k; i++)
		std::cin >> query_arr[i].query_type >> query_arr[i].u >> query_arr[i].v;
	get_solution(n, edges, query_arr);
	return 0;
}