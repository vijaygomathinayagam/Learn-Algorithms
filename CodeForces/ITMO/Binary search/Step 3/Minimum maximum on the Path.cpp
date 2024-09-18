#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<cstring>

// https://codeforces.com/edu/course/2/lesson/6/3/practice/contest/285083/problem/D

std::vector<std::pair<int, int>> adj[100001];
int vis[100001];
int p[100001], dist[100001];
int n, m, d;

bool bfs(int t) {
	memset(vis, false, sizeof(vis));
	std::queue<int> q;
	q.push(1);
	vis[1] = true;
	dist[1] = 0;
	p[1] = -1;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		if (dist[v] == d)
			continue;
		for (auto e : adj[v]) {
			if (vis[e.second])
				continue;
			if (e.first > t)
				continue;
			vis[e.second] = true;
			q.push(e.second);
			dist[e.second] = dist[v] + 1;
			p[e.second] = v;
		}
	}
	return vis[n];
}

int main() {
	std::cin >> n >> m >> d;
	while(m--) {
		int u, v, w;
		std::cin >> u >> v >> w;
		adj[u].push_back({w, v});
	}
	int l = 0, r = 1e9, ans = INT_MAX;
	while (l <= r) {
		int mid = l + (r - l) / 2;
		if (bfs(mid)) {
			ans = mid;
			r = mid - 1;
		}
		else
			l = mid + 1;
	}
	if (!bfs(ans)) {
		std::cout << -1;
		return 0;
	}
	std::vector<int> res;
	int v = n;
	while (v != -1) {
		res.push_back(v);
		v = p[v];
	}
	std::cout << (int)res.size() - 1 << std::endl;
	std::reverse(res.begin(), res.end());
	for (auto x : res)
		std::cout << x << " ";
	return 0;
}