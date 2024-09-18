#include<iostream>
#include<vector>
#include<algorithm>

// https://codeforces.com/edu/course/2/lesson/6/2/practice/contest/283932/problem/G

int	n, k;
std::vector<int> group_arr;

bool can_form_council(long long councils) {
	long long last = 0;
	int filled = 0;
	for (auto x : group_arr) {
		if (x + last < councils)
			last += x;
		else if (x >= councils)
			filled++;
		else {
			filled++;
			last = (x + last) % councils;
		}
		if (filled >= k)
			return true;
	}
	return false;
}

int main() {
	std::cin >> k >> n;
	group_arr.resize(n);
	for (int i = 0; i < n; i++)
		std::cin >> group_arr[i];
	long long l = 2, r = 1LL * *std::max_element(group_arr.begin(), group_arr.end()) * n / k + 1;
	while (l + 1 < r) {
		long long m = l + (r - l) / 2;
		if (can_form_council(m))
			l = m;
		else
			r = m;
	}
	std::cout << l;
	return 0;
}