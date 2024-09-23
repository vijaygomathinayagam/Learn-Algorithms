#include<iostream>

// https://www.hackerrank.com/challenges/xor-key/topics
// problem 1 - Maximum XOR pair

struct Trie {
	Trie* left, * right;

	Trie() : left(nullptr), right(nullptr) {}
};
Trie* root;

void update(int val) {
	Trie* curr = root;
	for (int i = 31; i >= 0; i--) {
		if (val & (1 << i)) {
			if (!curr->right)
				curr->right = new Trie();
			curr = curr->right;
		}
		else {
			if (!curr->left)
				curr->left = new Trie();
			curr = curr->left;
		}
	}
}

int query(int val) {
	Trie* curr = root;
	int ans = 0;
	for (int i = 31; i >= 0; i--) {
		if (val & (1 << i)) {
			if (curr->left)
				curr = curr->left;
			else {
				curr = curr->right;
				ans += (1 << i);
			}
		}
		else {
			if (curr->right) {
				curr = curr->right;
				ans += (1 << i);
			}
			else
				curr = curr->left;
		}
	}
	return ans;
}

int main() {
	root = new Trie();
	int n;
	std::cin >> n;
	int a;
	for (int i = 0; i < n; i++) {
		std::cin >> a;
		update(a);
		if (i > 0)
			std::cout << i + 1 << " " << a << " " << query(a) << std::endl;
	}
	return 0;
}