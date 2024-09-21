#include<iostream>
#include<vector>
#include<sstream>

// https://codeforces.com/edu/course/2/lesson/9/1/practice/contest/307092/problem/A

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	int n, m;
	std::cin >> n >> m;
	std::vector<int> a(n), b(m), c(n + m);
	for (int i = 0; i < n; i++)
		std::cin >> a[i];
	for (int i = 0; i < m; i++)
		std::cin >> b[i];
	int i = 0, j = 0, k = 0;
	while (i < a.size() && j < b.size())
		if (a[i] < b[j])
			c[k++] = a[i++];
		else
			c[k++] = b[j++];
	while (i < a.size())
		c[k++] = a[i++];
	while (j < b.size())
		c[k++] = b[j++];
	std::stringstream ss;
	for (auto& x : c)
		ss << x << " ";
	std::cout << ss.str();
	return 0;
}