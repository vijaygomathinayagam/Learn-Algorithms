#include<iostream>
#include<vector>
#include<algorithm>

// https://codeforces.com/edu/course/2/lesson/6/5/practice/contest/285084/problem/C

long long find_kth(const int& n, const int& k, std::vector<int>& a, std::vector<int>& b) {
	std::sort(b.begin(), b.end());
	auto has_less_than_k = [&n, &k, &a, &b](const long long x) {
		long long cnt = 0;
		for (const int& ai : a) {
			if (x > ai)
				cnt += std::lower_bound(b.begin(), b.end(), x - ai) - b.begin();
			if (cnt >= k)
				return false;
		}
		return true;
	};
	long long lo = 1, hi = 2e9 + 1;
	while (lo + 1 < hi) {
		long long m = lo + (hi - lo) / 2;
		if (has_less_than_k(m))
			lo = m;
		else
			hi = m;
	}
	return lo;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	int n, k;
	std::cin >> n >> k;
	std::vector<int> a(n), b(n);
	for (int i = 0; i < n; i++)
		std::cin >> a[i];
	for (int i = 0; i < n; i++)
		std::cin >> b[i];
	std::cout << find_kth(n, k, a, b);
	return 0;
}