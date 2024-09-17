#include<iostream>
#include<vector>
#include<sstream>

// https://codeforces.com/edu/course/2/lesson/6/1/practice/contest/283911/problem/A

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
		int l = 0, r = n - 1;
		bool ok = false;
		while (l <= r) {
			int m = (l + r) / 2;
			if (a[m] == x) {
				ok = true;
				break;
			}
			else if (a[m] > x)
				r = m - 1;
			else
				l = m + 1;
		}
		if (ok)
			ss << "YES" << std::endl;
		else
			ss << "NO" << std::endl;
	}
	std::cout << ss.str();
	return 0;
}