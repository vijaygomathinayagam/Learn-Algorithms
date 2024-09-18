#include<iostream>
#include<vector>

// https://codeforces.com/edu/course/2/lesson/6/3/practice/contest/285083/problem/C

int main() {
	int n, k;
	std::cin >> n >> k;
	std::vector<int> a(n);
	for (int i = 0; i < n; i++)
		std::cin >> a[i];
	auto can_place = [&k, &n, &a](const int& distance) {
		int remaining_cows = k - 1;
		int prev = 0;
		for (int i = 1; i < n; i++) {
			if (a[i] - a[prev] >= distance) {
				prev = i;
				remaining_cows--;
				if (remaining_cows == 0)
					return true;
			}
		}
		return false;
	};
	int lo = 1, hi = 1000000000;
	while (lo + 1 < hi) {
		int m = lo + (hi - lo) / 2;
		if (can_place(m))
			lo = m;
		else
			hi = m;
	}
	std::cout << lo;
	return 0;
}