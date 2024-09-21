#include<iostream>
#include<vector>
#include<sstream>

// https://codeforces.com/edu/course/2/lesson/7/2/practice/contest/289391/problem/I

const int ADD_EDGE_QUERY = 0;
const int COLOR_CHECK_QUERY = 1;

class DSU {
private:
	std::vector<int> p, len, size;

	std::pair<int, int> get(int set) {
		if (set == p[set])
			return {set, 0};
		std::pair<int, int> result = get(p[set]);
		p[set] = result.first;
		len[set] = (len[set] + result.second) % 2;
		return { p[set], len[set] };
	}

public:
	DSU(int n) {
		p.resize(n);
		for (int i = 0; i < n; i++)
			p[i] = i;
		size.assign(n, 1);
		len.assign(n, 0);
	}

	void union_sets(int set1, int set2) {
		std::pair<int, int> result1 = get(set1);
		std::pair<int, int> result2 = get(set2);
		if (size[result1.first] < size[result2.first])
			std::swap(result1, result2);
		p[result2.first] = result1.first;
		len[result2.first] = (1 + result1.second + result2.second) % 2;
		size[result1.first] += size[result2.first];
	}

	bool is_in_same_part(int set1, int set2) {
		std::pair<int, int> result1 = get(set1);
		std::pair<int, int> result2 = get(set2);
		if (result1.first != result2.first)
			return false;
		return result1.second == result2.second;
	}
};

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	int n, m, shift = 0;
	std::cin >> n >> m;
	DSU dsu(n);
	std::stringstream ss;
	for (int i = 0; i < m; i++) {
		int type, u, v;
		std::cin >> type >> u >> v;
		u = (u + shift) % n;
		v = (v + shift) % n;
		if (type == ADD_EDGE_QUERY)
			dsu.union_sets(u, v);
		else if (type == COLOR_CHECK_QUERY) {
			bool result = dsu.is_in_same_part(u, v);
			ss << (result ? "YES" : "NO") << std::endl;
			if (result)
				shift = (shift + 1) % n;
		}
	}
	std::cout << ss.str();
	return 0;
}