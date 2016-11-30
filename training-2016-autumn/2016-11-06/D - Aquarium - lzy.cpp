#include <cstdio>
#include <algorithm>

#define N 100

struct Edge {
	int u, v, w;
	bool operator <(const Edge &o) {
		return w < o.w;
	}
} E[16 * N * N + 9];

int r, c, tot, h, m;
int f[2 * N * N + 9];
int w[N + 9][N + 9], e[N + 9][N + 9], n[N + 9][N + 9], s[N + 9][N + 9];
char g[N + 9][N + 9];

int find(int e) {
	return f[e] == e ? e : f[e] = find(f[e]);
}

void join(int a, int b) {
	f[a] = b;
}

int main() {
	int TT;
	scanf("%d", &TT);
	for (int T = 1; T <= TT; ++T) {
		scanf("%d%d", &r, &c);
		tot = 2 * r * c;
		for (int i = 0; i < tot; ++i)
			f[i] = i;
		for (int i = 0; i < r; ++i) {
			scanf("%s", g[i]);
			for (int j = 0; j < c; ++j) {
				int d = i * c + j;
				if (g[i][j] == '\\') {
					w[i][j] = s[i][j] = 2 * d;
					n[i][j] = e[i][j] = 2 * d + 1;
					
				} else {
					w[i][j] = n[i][j] = 2 * d;
					s[i][j] = e[i][j] = 2 * d + 1;
				}
				if (i) join(find(n[i][j]), find(s[i - 1][j]));
				if (j) join(find(w[i][j]), find(e[i][j - 1]));
			}
		}
		m = 0;
		for (int i = 0; i < r; ++i)
			for (int j = 0; j < c; ++j) {
				E[m].u = w[i][j];
				E[m].v = e[i][j];
				scanf("%d", &E[m++].w);
			}
		std::sort(E, E + m);
		int ans = 0;
		for (int i = 0; i < m; ++i) {
			if (find(E[i].u) == find(E[i].v)) continue;
			ans += E[i].w;
			join(find(E[i].u), find(E[i].v));
		}
		printf("Case %d: %d\n", T, ans);
	}
	return 0;
}
