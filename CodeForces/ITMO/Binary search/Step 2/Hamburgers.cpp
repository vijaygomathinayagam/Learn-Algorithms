#include<iostream>

// https://codeforces.com/edu/course/2/lesson/6/2/practice/contest/283932/problem/H

int main() {
	int rbc = 0, rsc = 0, rcc = 0;
	int bc, sc, cc, bp, sp, cp;
	long long r;
	std::string s;

	std::cin >> s;
	for (char c : s) {
		switch (c) {
		case 'B': rbc++; break;
		case 'S': rsc++; break;
		case 'C': rcc++; break;
		}
	}
	std::cin >> bc >> sc >> cc;
	std::cin >> bp >> sp >> cp;
	std::cin >> r;
	auto can_make = [rbc, rsc, rcc, bc, sc, cc, bp, sp, cp, r](long long cnt) {
		long long pbc = std::max(cnt * rbc - bc, 0LL) * bp;
		long long psc = std::max(cnt * rsc - sc, 0LL) * sp;
		long long pcc = std::max(cnt * rcc - cc, 0LL) * cp;
		return (pbc + psc + pcc) <= r;
	};
	long long lo = -1, hi = r + bc + sc + cc + 1;
	while (lo + 1 < hi) {
		long long m = lo + (hi - lo) / 2;
		if (can_make(m))
			lo = m;
		else
			hi = m;
	}
	std::cout << lo;
	return 0;
}