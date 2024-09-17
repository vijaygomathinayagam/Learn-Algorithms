#include<iostream>
#include<vector>
#include<algorithm>
#include<sstream>

// https://codeforces.com/edu/course/2/lesson/6/1/practice/contest/283911/problem/D

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);
	int n;
	std::cin >> n;
	std::vector<int> a(n);
	for (int i = 0; i < n; i++)
		std::cin >> a[i];
	std::sort(a.begin(), a.end());
	int k;
	std::cin >> k;
	std::stringstream ss;
	for (int i = 0; i < k; i++) {
		int x, y;
		std::cin >> x >> y;
		int before = 0, after = 0;
		for (int l = -1, r = n; l + 1 < r; before = l) {
			int m = (l + r) / 2;
			if (a[m] < x)
				l = m;
			else
				r = m;
		}
		for (int l = -1, r = n; l + 1 < r; after = r) {
			int m = (l + r) / 2;
			if (a[m] > y)
				r = m;
			else
				l = m;
		}
		ss << (after - before - 1) << " ";
	}
	std::cout << ss.str();
	return 0;
}