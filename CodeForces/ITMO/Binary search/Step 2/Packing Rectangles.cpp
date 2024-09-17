#include<iostream>
#include<vector>

// https://codeforces.com/edu/course/2/lesson/6/2/practice/contest/283932/problem/A

long long w, h, n;

bool good(long long x) {
	return (x / w) * (x / h) >= n;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);
	std::cin >> w >> h >> n;
	long long l = 0, r = 1;
	while (!good(r))
		r *= 2;
	while (l + 1 < r) {
		long long m = (l + r) / 2;
		if (good(m))
			r = m;
		else
			l = m;
	}
	std::cout << r;
	return 0;
}