#include<iostream>
#include<vector>
#include<numeric>

// https://codeforces.com/edu/course/2/lesson/9/2/practice/contest/307093/problem/G

int n;

struct Stack {
	std::vector<long long> s, s_gcd;

	void push(long long x) {
		s.push_back(x);
		if (s_gcd.empty())
			s_gcd.push_back(x);
		else
			s_gcd.push_back(std::gcd(s_gcd.back(), x));
	}

	long long pop() {
		long long res = s.back();
		s.pop_back();
		s_gcd.pop_back();
		return res;
	}

	bool empty() {
		return s.empty();
	}

	long long gcd() {
		return s_gcd.back();
	}
};

Stack s1, s2;

void add(long long x) {
	s2.push(x);
}

void remove(long long x) {
	if (s1.empty()) {
		while (!s2.empty())
			s1.push(s2.pop());
	}
	s1.pop();
}

bool good() {
	if (s1.empty() && s2.empty())
		return false;
	if (s1.empty())
		return s2.gcd() == 1;
	if (s2.empty())
		return s1.gcd() == 1;
	return std::gcd(s1.gcd(), s2.gcd()) == 1;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cin >> n;
	std::vector<long long> a(n);
	for (int i = 0; i < n; i++)
		std::cin >> a[i];
	int res = INT_MAX;
	for (int l = 0, r = 0; r < n; r++) {
		add(a[r]);
		bool entered_loop = false;
		while (good()) {
			remove(a[l]);
			l++;
			entered_loop = true;
		}
		if (entered_loop) {
			res = std::min(res, r - l + 2);
		}
	}
	if (res == INT_MAX)
		std::cout << -1;
	else
		std::cout << res;
	return 0;
}