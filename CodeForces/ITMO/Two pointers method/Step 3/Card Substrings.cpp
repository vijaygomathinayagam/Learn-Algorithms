#include<iostream>

// https://codeforces.com/edu/course/2/lesson/9/3/practice/contest/307094/problem/F

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	int m_cnt[26], c_cnt[26];
	for (int i = 0; i < 26; i++)
		c_cnt[i] = m_cnt[i] = 0;
	int n_s, m_s;
	std::string s, m;
	std::cin >> n_s >>  m_s;
	std::cin >> s;
	std::cin >> m;
	for (const auto& c : m)
		m_cnt[c - 'a']++;
	const auto good = [&m_cnt, &c_cnt]() {
		for (int i = 0; i < 26; i++)
			if (c_cnt[i] > m_cnt[i])
				return false;
		return true;
	};
	unsigned long long res = 0;
	unsigned long long match_count = 0;
	for (int l = 0, r = 0; r < n_s; r++) {
		c_cnt[s[r] - 'a']++;
		match_count++;
		while (!good()) {
			c_cnt[s[l] - 'a']--;
			l++;
			match_count--;
		}
		res += match_count;
	}
	std::cout << res;
	return 0;
}