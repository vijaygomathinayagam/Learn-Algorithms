#include<iostream>
#include<vector>

// https://codeforces.com/edu/course/2/lesson/6/5/practice/contest/285084/problem/A

int find_kth_element(const int &n, const int &k, const std::vector<std::pair<int, int>> &pair_arr) {
	auto has_less_than_k_elements = [&pair_arr, &k](const long long &x) {
		long long cnt = 0;
		for (std::pair<int, int> segment : pair_arr) {
			if (x > segment.first)
				cnt += std::min(x - segment.first, (long long)segment.second - segment.first + 1);
			if (cnt > k)
				return false;
		}
		return true;
	};
	long long lo = -2e9 - 1, hi = 2e9 + 1;
	while (lo + 1 < hi) {
		int m = lo + (hi - lo) / 2;
		if (has_less_than_k_elements(m))
			lo = m;
		else
			hi = m;
	}
	return lo;
}

int main() {
	int n, k;
	std::cin >> n >> k;
	std::vector<std::pair<int, int>> pair_arr(n);
	for (int i = 0; i < n; i++)
		std::cin >> pair_arr[i].first >> pair_arr[i].second;
	std::cout << find_kth_element(n, k, pair_arr) << std::endl;
	return 0;
}