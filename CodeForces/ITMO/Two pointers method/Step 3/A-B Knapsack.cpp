#include<iostream>
#include<vector>
#include<algorithm>

// https://codeforces.com/edu/course/2/lesson/9/3/practice/contest/307094/problem/H

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	int n, m;
	unsigned long long s, a, b;
	std::cin >> n >> m >> s >> a >> b;
	std::vector<int> a_arr(n), b_arr(m);
	for (int i = 0; i < n; i++)
		std::cin >> a_arr[i];
	for (int i = 0; i < m; i++)
		std::cin >> b_arr[i];
	std::sort(a_arr.begin(), a_arr.end());
	std::sort(b_arr.begin(), b_arr.end());
	if (a > b) {
		std::swap(a, b);
		std::swap(a_arr, b_arr);
		std::swap(n, m);
	}
	unsigned long long total_cost = 0, best_cost = 0;
	unsigned long long total_weight = 0;
	int ai = n - 1, bi = m - 1;
	while (bi >= 0 && total_weight + b <= s) {
		total_weight += b;
		total_cost += b_arr[bi--];
	}
	while (ai >= 0 && total_weight + a <= s) {
		total_weight += a;
		total_cost += a_arr[ai--];
	}
	best_cost = total_cost;
	while (ai >= 0 && bi < m - 1) {
		total_weight -= b;
		total_cost -= b_arr[++bi];
		while (ai >= 0 && total_weight + a <= s) {
			total_weight += a;
			total_cost += a_arr[ai--];
		}
		if (total_cost > best_cost)
			best_cost = total_cost;
	}
	std::cout << best_cost;
	return 0;
}