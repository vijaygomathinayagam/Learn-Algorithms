#include<iostream>
#include<vector>
#include<iomanip>
#include<cmath>

// https://codeforces.com/edu/course/2/lesson/6/2/practice/contest/283932/problem/B

int n, k;
std::vector<int> a;

bool good(double x) {
	int s = 0;
	for (auto ele : a)
		s += std::floor(ele / x);
	return s >= k;
}

int main() {
	std::cin >> n >> k;
	a.resize(n);
	for (int i = 0; i < n; i++)
		std::cin >> a[i];
	double l = 0, r = 10000001;
	for (int i = 0; i < 100; i++) {
		double m = (l + r) / 2;
		if (good(m))
			l = m;
		else
			r = m;
	}
	std::cout << std::setprecision(20) << l;
	return 0;
}