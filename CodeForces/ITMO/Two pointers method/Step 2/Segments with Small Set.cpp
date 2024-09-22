#include<iostream>
#include<vector>

// https://codeforces.com/edu/course/2/lesson/9/2/practice/contest/307093/problem/E

int n, k, num = 0;
int cnt[100001];

void add(int x) {
	cnt[x]++;
	if (cnt[x] == 1)
		num++;
}

void remove(int x) {
	cnt[x]--;
	if (cnt[x] == 0)
		num--;
}

bool good() {
	return num <= k;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	for (int i = 0; i < 100001; i++)
		cnt[i] = 0;
	std::cin >> n >> k;
	std::vector<int> a(n);
	for (int i = 0; i < n; i++)
		std::cin >> a[i];
	long long res = 0;
	for (int l = 0, r = 0; r < n; r++) {
		add(a[r]);
		while (!good()) {
			remove(a[l]);
			l++;
		}
		res += r - l + 1;
	}
	std::cout << res;
	return 0;
}