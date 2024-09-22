#include<iostream>
#include<vector>

// https://codeforces.com/edu/course/2/lesson/9/3/practice/contest/307094/problem/E

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	int n;
	long long s;
	std::cin >> n >> s;
	std::vector<std::pair<int, int>> wc_pair_arr(n);
	for (int i = 0; i < n; i++)
		std::cin >> wc_pair_arr[i].first;
	for (int i = 0; i < n; i++)
		std::cin >> wc_pair_arr[i].second;
	long long total_weight = 0, total_cost = 0;
	long long best_cost = 0;
	for (int l = 0, r = 0; r < n; r++) {
		total_weight += wc_pair_arr[r].first;
		total_cost += wc_pair_arr[r].second;
		while (total_weight > s) {
			total_weight -= wc_pair_arr[l].first;
			total_cost -= wc_pair_arr[l].second;
			l++;
		}
		if (total_cost > best_cost)
			best_cost = total_cost;
	}
	std::cout << best_cost;
	return 0;
}