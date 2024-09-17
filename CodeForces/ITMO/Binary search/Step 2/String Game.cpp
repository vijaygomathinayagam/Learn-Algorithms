#include<iostream>
#include<vector>

// https://codeforces.com/edu/course/2/lesson/6/2/practice/contest/283932/problem/F

std::string t, p;
std::vector<int> perm;
std::vector<int> perm_inv;

bool can_remove(const int &num_chars) {
	int tn = t.size();
	int pn = p.size();
	int pi = 0;
	for (int ti = 0; ti < tn && pi < pn; ti++) {
		if (perm_inv[ti + 1] > num_chars && t[ti] == p[pi])
			pi++;
	}
	return pi == pn;
}

int main() {
	std::cin >> t >> p;
	int n = t.size();
	perm.resize(n);
	perm_inv.resize(n + 1);
	for (int i = 0; i < n; i++)
		std::cin >> perm[i];
	for (int i = 0; i < n; i++)
		perm_inv[perm[i]] = i + 1;
	int l = -1, r = n - p.size() + 1;
	while (l + 1 < r) {
		int m = l + (r - l) / 2;
		if (can_remove(m))
			l = m;
		else
			r = m;
	}
	std::cout << l;
	return 0;
}