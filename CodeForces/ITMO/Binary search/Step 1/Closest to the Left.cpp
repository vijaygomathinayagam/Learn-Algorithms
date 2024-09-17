#include<iostream>
#include<vector>
#include<sstream>

// https://codeforces.com/edu/course/2/lesson/6/1/practice/contest/283911/problem/B

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);
	int n, k;
	std::cin >> n >> k;
	std::vector<int> a(n);
	for (int i = 0; i < n; i++)
		std::cin >> a[i];
	std::stringstream ss;
	for (int i = 0; i < k; i++) {
		int x;
		std::cin >> x;
		int l = -1, r = n;
		while (l + 1 < r) {
			int m = (l + r) / 2;
			if (a[m] <= x)
				l = m;
			else
				r = m;
		}
		ss << l + 1 << std::endl;
	}
	std::cout << ss.str();
	return 0;
}