#include<iostream>
#include<vector>

// https://codeforces.com/edu/course/2/lesson/9/3/practice/contest/307094/problem/C

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	int n, r;
	std::cin >> n >> r;
	std::vector<int> dist(n);
	for (int i = 0, prev = 0; i < n; i++) {
		std::cin >> dist[i];
		int temp = dist[i];
		dist[i] -= prev;
		prev = temp;
	}
	long long sum = 0;
	long long res = 0;
	for (int left = 0, right = 0; right < n; right++) {
		sum += dist[right];
		while (sum - dist[left] > r) {
			sum -= dist[left];
			left++;
		}
		if (sum > r)
			res += left;
	}
	std::cout << res;
	return 0;
}