#include<iostream>
#include<vector>

// https://codeforces.com/edu/course/2/lesson/9/3/practice/contest/307094/problem/B

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	int n;
	long long s;
	std::cin >> n >> s;
	std::vector<int> a(n);
	for (int i = 0; i < n; i++)
		std::cin >> a[i];
	long long sum = 0, res = 0;
	for (int l = 0, r = 0; r < n; r++) {
		sum += a[r];
		while (sum > s) {
			sum -= a[l];
			l++;
		}
		res += (1LL * (r - l + 1) * (r - l + 2)) / 2;
	}
	std::cout << res;
	return 0;
}