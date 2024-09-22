#include<iostream>
#include<vector>

// https://codeforces.com/edu/course/2/lesson/9/2/practice/contest/307093/problem/B

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	int n;
	long long s;
	std::cin >> n >> s;
	std::vector<int> a(n);
	for (int i = 0; i < n; i++)
		std::cin >> a[i];
	long long sum = 0;
	int res = INT_MAX;
	for (int l = 0, r = 0; r < n; r++) {
		sum += a[r];
		while (sum - a[l] >= s) {
			sum -= a[l];
			l++;
		}
		if (sum >= s)
			res = std::min(res, r - l + 1);
	}
	if (res == INT_MAX)
		std::cout << -1;
	else
		std::cout << res;
	return 0;
}