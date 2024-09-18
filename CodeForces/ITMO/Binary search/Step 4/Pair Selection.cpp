#include<iostream>
#include<vector>
#include<iomanip>
#include<algorithm>

// https://codeforces.com/edu/course/2/lesson/6/4/practice/contest/285069/problem/C

const int ITERATIONS = 70;

double find_ratio(const int& n, const int& k, const std::vector<std::pair<int, int>>& a) {
	auto has_ratio = [&n, &k, &a](double ratio) {
		std::vector<double> arr(n);
		for (auto i = 0; i < n; i++)
			arr[i] = ratio * a[i].second - a[i].first;
		std::nth_element(arr.begin(), arr.begin() + k - 1, arr.end());
		double acc = 0;
		for (int i = 0; i < k; i++)
			acc += arr[i];
		return acc <= 0;
	};
	double lo = 0, hi = 100000;
	for (int i = 0; i < ITERATIONS; i++) {
		double m = lo + (hi - lo) / 2;
		if (has_ratio(m))
			lo = m;
		else
			hi = m;
	}
	return lo;
}

int main() {
	int n, k;
	std::cin >> n >> k;
	std::vector<std::pair<int, int>> a(n);
	for (auto i = 0; i < n; i++)
		std::cin >> a[i].first >> a[i].second;
	std::cout << std::setprecision(20) << find_ratio(n, k, a) << std::endl;
	return 0;
}