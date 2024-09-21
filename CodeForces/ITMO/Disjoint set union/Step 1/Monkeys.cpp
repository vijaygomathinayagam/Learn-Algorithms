#include<iostream>
#include<vector>
#include<list>
#include<sstream>

// https://codeforces.com/edu/course/2/lesson/7/1/practice/contest/289390/problem/E

class DisjointSetUnion {
private:
	std::vector<int> p;
	std::vector<std::list<int>> set_list;

	int get(int set) {
		if (set == p[set])
			return set;
		return (p[set] = get(p[set]));
	}

public:
	DisjointSetUnion(int n) {
		p.resize(n + 1);
		set_list.resize(n + 1);
		for (int i = 1; i <= n; i++) {
			p[i] = i;
			set_list[i].push_back(i);
		}
	}

	void union_sets(int set1, int set2) {
		set1 = get(set1);
		set2 = get(set2);
		if (set1 == set2)
			return;
		if (set_list[set1].size() < set_list[set2].size())
			std::swap(set1, set2);
		p[set2] = set1;
		set_list[set1].splice(set_list[set1].end(), set_list[set2]);
		set_list[set2].clear();
	}

	bool is_in_set_1(int set) {
		return get(set) == get(1);
	}

	std::list<int> get_set_list(int set) {
		return set_list[get(set)];
	}
};

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	int n, m;
	std::cin >> n >> m;
	std::vector<std::pair<int, int>> monkey_arr(n + 1);
	for (auto i = 1; i <= n; i++)
		std::cin >> monkey_arr[i].first >> monkey_arr[i].second;
	std::vector<std::pair<int, int>> query_arr(m);
	for (auto i = 0; i < m; i++) {
		int monkey, hand;
		std::cin >> monkey >> hand;
		if (hand == 1) {
			query_arr[i] = { monkey, monkey_arr[monkey].first };
			monkey_arr[monkey].first = -1;
		}
		else {
			query_arr[i] = { monkey, monkey_arr[monkey].second };
			monkey_arr[monkey].second = -1;
		}
	}
	DisjointSetUnion disjoint_set_union(n);
	for (int i = 1; i <= n; i++) {
		if (monkey_arr[i].first != -1)
			disjoint_set_union.union_sets(i, monkey_arr[i].first);
		if (monkey_arr[i].second != -1)
			disjoint_set_union.union_sets(i, monkey_arr[i].second);
	}
	std::vector<int> ans_arr(n + 1, -1);
	for (int i = m - 1; i >= 0; i--) {
		int monkey1 = query_arr[i].first;
		int monkey2 = query_arr[i].second;
		bool monkey2_released_second = false;
		if (disjoint_set_union.is_in_set_1(monkey2) && !disjoint_set_union.is_in_set_1(monkey1)) {
			std::swap(monkey1, monkey2);
			monkey2_released_second = true;
		}
		else if (disjoint_set_union.is_in_set_1(monkey1) && !disjoint_set_union.is_in_set_1(monkey2))
			monkey2_released_second = true;
		if (monkey2_released_second) {
			std::list<int> monkey2_set_list = disjoint_set_union.get_set_list(monkey2);
			for (const int& monkey : monkey2_set_list)
				ans_arr[monkey] = i;
		}
		disjoint_set_union.union_sets(monkey1, monkey2);
	}
	std::stringstream ss;
	for (int i = 1; i <= n; i++)
		ss << ans_arr[i] << std::endl;
	std::cout << ss.str();
	return 0;
}