#include<iostream>
#include<vector>
#include<sstream>

// https://codeforces.com/edu/course/2/lesson/9/1/practice/contest/307092/problem/B

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	int n, m;
	std::cin >> n >> m;
	std::vector<int> a(n), b(m);
	for (int i = 0; i < n; i++)
		std::cin >> a[i];
	for (int i = 0; i < m; i++)
		std::cin >> b[i];
	std::vector<int> res(m);
	for (int i = 0, j = 0; j < b.size(); j++) {
		while (i < a.size() && a[i] < b[j])
			i++;
		res[j] = i;
	}
	std::stringstream ss;
	for (const auto& x : res)
		ss << x << " ";
	std::cout << ss.str();
	return 0;
}