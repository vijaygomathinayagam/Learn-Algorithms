#include<iostream>
#include<vector>
#include<algorithm>

// https://codeforces.com/edu/course/2/lesson/6/4/practice/contest/285069/problem/B

std::vector<int> find_min_avg_path(const std::vector<std::vector<std::pair<int, int>>> &edges,
	const int &n) {
	auto can_reach = [&edges, &n](double avg, bool need_trace) -> std::pair<bool, std::vector<int>> {
		std::vector<double> dp(n + 1, 1126);
		std::vector<int> prev(n + 1, -1);
		dp[1] = 0.0;
		for (auto i = 0; i < n; i++) {
			if (i != 1 && prev[i] == -1)
				continue;
			for (const auto& edge : edges[i]) {
				if (dp[i] + edge.second - avg < dp[edge.first]) {
					dp[edge.first] = dp[i] + edge.second - avg;
					prev[edge.first] = i;
				}
			}
			if (dp[n] <= 0)
				break;
		}
		std::vector<int> trace;
		if (need_trace && dp[n] <= 0) {
			trace.push_back(n);
			while (prev[trace.back()] != -1)
				trace.push_back(prev[trace.back()]);
			std::reverse(trace.begin(), trace.end());
		}
		return { dp[n] <= 0, trace };
	};
	double lo = -1, hi = 100.1;
	const auto iterations = 30;
	for (auto i = 0; i < iterations; i++) {
		auto mid = lo + (hi - lo) / 2;
		if (can_reach(mid, false).first)
			hi = mid;
		else
			lo = mid;
	}
	return can_reach(hi, true).second;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	int n, m;
	std::cin >> n >> m;
	std::vector<std::vector<std::pair<int, int>>> edges(n + 1);
	for (auto i = 0; i < m; i++) {
		int from, to, weight;
		std::cin >> from >> to >> weight;
		edges[from].push_back({to, weight});
	}
	auto trace = find_min_avg_path(edges, n);
	std::cout << trace.size() - 1 << std::endl;
	for (const auto& x : trace)
		std::cout << x << " ";
	return 0;
}