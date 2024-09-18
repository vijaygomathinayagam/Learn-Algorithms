#include<iostream>
#include<vector>
#include<iomanip>

// https://codeforces.com/edu/course/2/lesson/6/3/practice/contest/285083/problem/A

int main() {
	int n;
	std::cin >> n;
	std::vector<int> x(n), v(n);
	
	for (int i = 0; i < n; i++)
		std::cin >> x[i] >> v[i];
	int slowest_i = 0, min_x = INT_MAX, max_x = INT_MIN;
	for (int i = 1; i < n; i++) {
		if (v[slowest_i] > v[i])
			slowest_i = i;
		min_x = std::min(min_x, x[i]);
		max_x = std::max(max_x, x[i]);
	}
	auto has_empty_intersection = [&n, &x, &v](const double &time){
		double lb = INT_MIN, rb = INT_MAX;
		for (int i = 0; i < n; i++) {
			lb = std::max(lb, x[i] - time * v[i]);
			rb = std::min(rb, x[i] + time * v[i]);
		}
		return (rb - lb) < 0;
	};
	double l = 0, r = std::max(std::abs(min_x - x[slowest_i]) / v[slowest_i],
		std::abs(max_x - x[slowest_i]) / v[slowest_i]);
	for (int i = 0; i < 100; i++) {
		double m = l + (r - l) / 2;
		if (has_empty_intersection(m))
			l = m;
		else
			r = m;
	}
	std::cout << std::setprecision(20) << r;
	return 0;
}