#include<iostream>
#include<vector>

// https://codeforces.com/edu/course/2/lesson/6/4/practice/contest/285069/problem/A

std::pair<int, int> locate_max_segment(const std::vector<int> &arr, const int &d) {
	const int n = arr.size();
	auto can_segment = [&arr, n, d](double avg, bool need_result) -> std::pair<bool, std::pair<int, int>> {
		std::vector<double> prefix_sum(n + 1), prefix_min(n + 1);
		prefix_sum[0] = 0;
		prefix_min[0] = 0;
		for (auto i = 0; i < n; i++) {
			prefix_sum[i + 1] = prefix_sum[i] + (arr[i] - avg);
			prefix_min[i + 1] = std::min(prefix_min[i], prefix_sum[i + 1]);
		}
		for (auto j = n - 1; j >= d - 1; j--) {
			if (prefix_min[j + 1 - d] <= prefix_sum[j + 1]) {
				auto i = j + 1 - d;
				if (need_result)
					while (prefix_sum[i] > prefix_sum[j + 1])
						i--;
				return { true, {i, j} };
			}
		}
		return { false, { 0, 0 } };
	};
	double lo = 0, hi = 101;
	const int iterations = 25;
	for (auto i = 0; i < iterations; i++) {
		auto mid = lo + (hi - lo) / 2;
		if (can_segment(mid, false).first)
			lo = mid;
		else
			hi = mid;
	}
	return can_segment(lo, true).second;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	int n, d;
	std::cin >> n >> d;
	std::vector<int> arr(n);
	for (int i = 0; i < n; i++)
		std::cin >> arr[i];
	auto res = locate_max_segment(arr, d);
	std::cout << res.first + 1 << " " << res.second + 1 << std::endl;
	return 0;
}