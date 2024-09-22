#include<iostream>
#include<set>
#include<vector>

// https://codeforces.com/edu/course/2/lesson/9/3/practice/contest/307094/problem/I

const int N = 1e3 + 1;
int cnt[N];
int n, s;

void add(int x) {
	for (int i = s; i - x >= 0; i--)
		cnt[i] += cnt[i - x];
}

void remove(int x) {
	for (int i = 0; i + x <= s; i++)
		cnt[i + x] -= cnt[i];
}

bool good() {
	return cnt[s];
}

int main() {
	cnt[0] = 1;
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cin >> n >> s;
	std::vector<int> a(n);
	for (int i = 0; i < n; i++)
		std::cin >> a[i];
	int res = INT_MAX;
	for (int l = 0, r = 0; r < n; r++) {
		add(a[r]);
		while (l < n && good()) {
			remove(a[l]);
			l++;
			if (!good()) {
				l--;
				add(a[l]);
				break;
			}
		}
		if (good())
			res = std::min(res, r - l + 1);
	}
	if (res == INT_MAX)
		std::cout << -1;
	else
		std::cout << res;
	return 0;
}