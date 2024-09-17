#include<iostream>
#include<vector>

// https://codeforces.com/edu/course/2/lesson/6/2/practice/contest/283932/problem/D

int main() {
	int n, m;
	std::cin >> m >> n;
	std::vector<int> t(n), z(n), y(n);
	for (int i = 0; i < n; i++)
		std::cin >> t[i] >> z[i] >> y[i];
	auto ballon_num = [&t, &z, &y](int i, int time) {
		int period = t[i] * z[i] + y[i];
		return time / period * z[i] + std::min((time % period) / t[i], z[i]);
	};
	auto can_blow = [m, n, &ballon_num](int time) {
		int cnt = 0;
		for (int i = 0; i < n; i++) {
			cnt += ballon_num(i, time);
			if (cnt >= m)
				return true;
		}
		return false;
		};
	int lo = -1, hi = m * 200;
	while (lo + 1 < hi) {
		int m = lo + (hi - lo) / 2;
		if (can_blow(m))
			hi = m;
		else
			lo = m;
	}
	std::cout << hi << std::endl;
	int remaining = m;
	for (int i = 0; i < n; i++) {
		int cnt = ballon_num(i, hi);
		if (cnt > remaining)
			cnt = remaining;
		std::cout << cnt << " ";
		remaining -= cnt;
	}
	return 0;
}