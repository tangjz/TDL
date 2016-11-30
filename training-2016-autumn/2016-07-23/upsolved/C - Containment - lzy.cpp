#include <cstdio>
#include <cstring>
#include <algorithm>

using std::min;

constexpr int N = 1000;
constexpr int inf = 0x7fffffff;

int T, n, x, y, z, s, t;
int l, r, p[N + 9], q[N + 9];
int c[N + 9][N + 9];

inline
int idx(int x, int y, int z) {
	return x * 100 + y * 10 + z;
}

inline
void add(int u, int v, int w) {
	c[u][v] += w;
	c[v][u] += w;
}

bool bfs() {
	memset(p, -1, sizeof p);
	q[(r = 0)++] = s;
	for (l = 0; l < r; ++l) {
		int u = q[l];
		for (int v = 0; v < n; ++v) {
			if (!~p[v] && c[u][v])
				p[q[r++] = v] = u;
		}
		if (~p[t]) return true;
	}
	return false;
}
int main() {
	scanf("%d", &T);
	while (T--) {
		memset(c, 0, sizeof c);
		scanf("%d", &n);
		s = 1000, t = 1001;
		while (n--) {
			scanf("%d%d%d", &x, &y, &z);
			add(s, idx(x, y, z), inf);
		}
		for (int i = 0; i <= 9; ++i)
			for (int j = 0; j <= 9; ++j)
				for (int k = 0; k <= 9; ++k) {
					int d = idx(i, j, k);
					if (i) add(idx(i - 1, j, k), d, 1);
					else add(d, t, 1);
					if (i == 9) add(d, t, 1);
					if (j) add(idx(i, j - 1, k), d, 1);
					else add(d, t, 1);
					if (j == 9) add(d, t, 1);
					if (k) add(idx(i, j, k - 1), d, 1);
					else add(d, t, 1);
					if (k == 9) add(d, t, 1);
				}
		n = t + 1;
		int mxf = 0;
		for (int det; bfs(); mxf += det) {
			det = inf;
			for (int i = t; i != s; i = p[i]) det = min(det, c[p[i]][i]);
			for (int i = t; i != s; i = p[i]) {
				c[p[i]][i] -= det;
				c[i][p[i]] += det;
			}
		}
		printf("%d\n", mxf);
	}
	return 0;
}
