#include<iostream>

// https://cses.fi/problemset/task/1737

const int MAXN = 200001;

int n, q;
int a[MAXN];

struct Node {
	long long val;
	Node* l, * r;

	Node(long long vall) : val(vall), l(nullptr), r(nullptr) {}

	Node(Node* ll, Node* rr) {
		l = ll;
		r = rr;
		val = 0;
		if (l)
			val += l->val;
		if (r)
			val += r->val;
	}
	Node(Node* cp) : val(cp->val), l(cp->l), r(cp->r) {}
};

Node *roots[MAXN];
int cnt = 1;

Node* build(int l = 1, int r = n) {
	if (l == r)
		return new Node(a[l]);
	else {
		int mid = (l + r) / 2;
		return new Node(build(l, mid), build(mid + 1, r));
	}
}

Node* update(Node* node, int pos, int val, int l = 1, int r = n) {
	if (l == r)
		return new Node(val);
	int mid = (l + r) / 2;
	if (pos <= mid)
		return new Node(update(node->l, pos, val, l, mid), node->r);
	return new Node(node->l, update(node->r, pos, val, mid + 1, r));
}

long long query(Node *node, int a, int b, int l = 1, int r = n) {
	if (l > b || r < a)
		return 0;
	if (l >= a && r <= b)
		return node->val;
	int mid = (l + r) / 2;
	return query(node->l, a, b, l, mid)
		+ query(node->r, a, b, mid + 1, r);
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cin >> n >> q;
	for (int i = 1; i <= n; i++)
		std::cin >> a[i];
	roots[cnt++] = build();
	for (int i = 0; i < q; i++) {
		int type;
		std::cin >> type;
		if (type == 1) {
			int k, a, x;
			std::cin >> k >> a >> x;
			roots[k] = update(roots[k], a, x);
		}
		else if (type == 2) {
			int k, a, b;
			std::cin >> k >> a >> b;
			std::cout << query(roots[k], a, b) << std::endl;
		}
		else if (type == 3) {
			int k;
			std::cin >> k;
			roots[cnt++] = new Node(roots[k]);
		}
	}
	return 0;
}