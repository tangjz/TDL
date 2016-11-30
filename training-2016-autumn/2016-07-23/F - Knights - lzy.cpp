#include <cstdio>
#include <cstring>

typedef long long i64;

const int mod = 1000000009;

int T, n, m, l;
int b[1 << 8][1 << 8];
int a[81][81], d[81][81];
int u, v, idx[1 << 8];
bool vis[1 << 8];

bool check(int r, int s, int t) {
	for (int i = 0; i < m; ++i)
		if (t & 1 << i) {
			if (i >= 2 && s & 1 << i - 2) return false;
			if (i + 2 < m && s & 1 << i + 2) return false;
			if (i && r & 1 << i - 1) return false;
			if (i + 1 < m && r & 1 << i + 1) return false;
		}
	return true;
}

void add(int s, int t) {
	b[s][t] = 1;
}

void dfs(int u) {
	vis[u] = true;
	for (int i = 0; i < v; ++i)
		if (b[u][i] && !vis[i])
			dfs(i);
}

void mult(int a[][81], int b[][81]) {
	static int c[81][81];
	for (int i = 0; i < l; ++i) for (int j = 0; j < l; ++j) {
		c[i][j] = 0;
		for (int k = 0; k < l; ++k) {
			c[i][j] += (i64)a[i][k] * b[k][j] % mod;
			if (c[i][j] >= mod) c[i][j] -= mod;
		}
	}
	for (int i = 0; i < l; ++i) for (int j = 0; j < l; ++j) a[i][j] = c[i][j];
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &m, &n);
		u = 1 << m;
		v = 1 << 2 * m;
		memset(a, 0, sizeof a);
		memset(b, 0, sizeof b);
		memset(d, 0, sizeof d);
		memset(vis, 0, sizeof vis);
		memset(idx, -1, sizeof idx);
		for (int i = 0; i < u; ++i) for (int j = 0; j < u; ++j)
			for (int k = 0; k < u; ++k)
				if (check(i, j, k)) add(i << m | j, j << m | k);
		dfs(0);
		l = 0;
		for (int i = 0; i < v; ++i) if (vis[i]) idx[i] = l++;
		//printf("%d\n", l);
		for (int i = 0; i < v; ++i) for (int j = 0; j < v; ++j)
			if (idx[i] != -1 && idx[j] != -1)
				a[idx[i]][idx[j]] = b[i][j];
		//~ for (int i = 0; i < l; ++i) for (int j = 0; j < l; ++j) {
			//~ if (a[i][j]) printf("%d %d\n", i, j);
		//~ }
		//for (int i = 0; i < l; ++i) d[i][i] = 1;
		d[0][0] = 1;

		do {
			if (n & 1) mult(d, a);
			mult(a, a);
		} while (n >>= 1);
		int ans = 0;
		for (int i = 0; i < l; ++i) for (int j = 0; j < l; ++j) {
			ans += d[i][j];
			//printf("%d%c", d[i][j], " \n"[j == l - 1]);
			if (ans >= mod) ans -= mod;
		}
		printf("%d\n", ans);
	}
	return 0;
}
