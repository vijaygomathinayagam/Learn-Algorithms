#include<iostream>
#include<vector>

// https://codeforces.com/edu/course/2/lesson/9/1/practice/contest/307092/problem/C

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
	long long result = 0;
	for (int i = 0, j = 0, prev_count = 0; j < b.size(); j++) {
		int current_count = 0;
		while (i < a.size() && a[i] < b[j])
			i++;
		while (i < a.size() && a[i] == b[j]) {
			current_count++;
			i++;
		}
		result += current_count;
		while (j + 1 < b.size() && b[j + 1] == b[j]) {
			result += current_count;
			j++;
		}
	}
	std::cout << result;
	return 0;
}