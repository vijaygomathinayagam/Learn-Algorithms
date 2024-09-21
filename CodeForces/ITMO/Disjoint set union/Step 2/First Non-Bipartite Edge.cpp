#include<iostream>
#include<vector>

// https://codeforces.com/edu/course/2/lesson/7/2/practice/contest/289391/problem/J

class DSU {
private:
	std::vector<int> p, size, len;

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
		p.resize(n + 1);
		for (int i = 1; i <= n; i++)
			p[i] = i;
		size.assign(n + 1, 1);
		len.assign(n + 1, 0);
	}

	void union_sets(int set1, int set2) {
		std::pair<int, int> result1 = get(set1);
		std::pair<int, int> result2 = get(set2);
		if (result1.first == result2.first)
			return;
		if (size[result1.first] < size[result2.first])
			std::swap(result1, result2);
		p[result2.first] = result1.first;
		size[result1.first] += size[result2.first];
		len[result2.first] = (1 + result1.second + result2.second) % 2;
	}

	bool is_in_same_part(int set1, int set2) {
		std::pair<int, int> result1 = get(set1);
		std::pair<int, int> result2 = get(set2);
		if (result1.first != result2.first)
			return false;
		return len[set1] == len[set2];
	}
};

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	int n, m;
	std::cin >> n >> m;
	int ans = -1;
	DSU dsu(n);
	for (int i = 0; i < m; i++) {
		int u, v;
		std::cin >> u >> v;
		if (ans != -1)
			continue;
		dsu.union_sets(u, v);
		if (dsu.is_in_same_part(u, v))
			ans = i + 1;
	}
	std::cout << ans;
	return 0;
}