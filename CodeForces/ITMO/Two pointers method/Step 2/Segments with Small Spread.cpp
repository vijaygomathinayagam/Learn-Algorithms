#include<iostream>
#include<vector>

// https://codeforces.com/edu/course/2/lesson/9/2/practice/contest/307093/problem/F

int n;
long long k;

struct Stack {
	std::vector<long long> s, s_min = { LLONG_MAX }, s_max = { LLONG_MIN };

	void push(long long x) {
		s.push_back(x);
		s_min.push_back(std::min(s_min.back(), x));
		s_max.push_back(std::max(s_max.back(), x));
	}

	long long pop() {
		long long res = s.back();
		s.pop_back();
		s_min.pop_back();
		s_max.pop_back();
		return res;
	}

	bool empty() {
		return s.empty();
	}

	long long min() {
		return s_min.back();
	}

	long long max() {
		return s_max.back();
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
	long long min = std::min(s1.min(), s2.min());
	long long max = std::max(s1.max(), s2.max());
	return (max - min) <= k;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cin >> n >> k;
	std::vector<long long> a(n);
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