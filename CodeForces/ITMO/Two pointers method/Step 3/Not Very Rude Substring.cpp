#include<iostream>

// https://codeforces.com/edu/course/2/lesson/9/3/practice/contest/307094/problem/G

long long a = 0, b = 0, rude = 0;

void add(char c) {
	if (c > 'b')
		return;
	if (c == 'a')
		a++;
	else if (c == 'b') {
		rude += a;
		b++;
	}
}

void remove(char c) {
	if (c > 'b')
		return;
	if (c == 'b')
		b--;
	else if (c == 'a') {
		rude -= b;
		a--;
	}
}

bool good(long long c) {
	return rude <= c;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	int n;
	long long c;
	std::cin >> n >> c;
	std::string s;
	std::cin >> s;
	int l = 0;
	int res = 0;
	for (int r = 0; r < n; r++) {
		add(s[r]);
		while (l < n && !good(c)) {
			remove(s[l]);
			l++;
		}
		res = std::max(res, r - l + 1);
	}
	std::cout << res;
	return 0;
}