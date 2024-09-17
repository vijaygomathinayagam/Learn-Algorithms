#include<iostream>
#include<vector>

// https://codeforces.com/edu/course/2/lesson/6/2/practice/contest/283932/problem/D

int n, x, y;

inline bool print_n_copies(const int &seconds) {
	if (seconds < std::min(x, y))
		return 0 >= n;
	int copies = 1;
	copies += (seconds - std::min(x, y)) / x;
	copies += (seconds - std::min(x, y)) / y;
	return copies >= n;
}

int main() {
	std::cin >> n >> x >> y;
	int l = 0, r = std::min(x, y) * n;
	while (l + 1 < r) {
		int m = l + (r - l) / 2;
		if (print_n_copies(m))
			r = m;
		else
			l = m;
	}
	std::cout << r;
	return 0;
}