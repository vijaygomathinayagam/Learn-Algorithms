#include<iostream>
#include<vector>

// https://codeforces.com/edu/course/2/lesson/6/3/practice/contest/285083/problem/B

int main() {
	int n, k;
	std::cin >> n >> k;
	std::vector<int> a(n);
	for (int i = 0; i < n; i++)
		std::cin >> a[i];
	auto is_max_sum_possible = [&n, &a, &k](const long long &max_sum) {
		long long temp_sum = 0;
		int segment_count = 1;
		for (auto x : a) {
			if (temp_sum + x > max_sum) {
				temp_sum = 0;
				segment_count++;
			}
			if (x > max_sum || segment_count > k)
				return false;
			temp_sum += x;
		}
		return true;
	};
	long long l = 0, r = 1LL * n * 1000000000;
	while (l + 1 < r) {
		long long m = l + (r - l) / 2;
		if (is_max_sum_possible(m))
			r = m;
		else
			l = m;
	}
	std::cout << r;
	return 0;
}