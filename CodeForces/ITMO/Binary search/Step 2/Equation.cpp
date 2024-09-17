#include<iostream>
#include<cmath>
#include<iomanip>

// https://codeforces.com/edu/course/2/lesson/6/2/practice/contest/283932/problem/E

double val(double x) {
	return x * x + std::sqrt(x);
}

int main() {
	double c;
	std::cin >> c;
	double l = 0, r = 100000;
	for (int i = 0; i < 100; i++) {
		double m = l + (r - l) / 2;
		if (val(m) >= c)
			r = m;
		else
			l = m;
	}
	std::cout << std::setprecision(20) << r;
	return 0;
}