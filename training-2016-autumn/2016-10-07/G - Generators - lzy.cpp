#include <cstdio>

#define N 10000
#define C 1000

int n, m, p[N + 9], s, t;
int x[N + 9][C + 9], a, b, c[N + 9];

int main() {
	freopen("generators.in", "r", stdin);
	freopen("generators.out", "w", stdout);
	scanf("%d%d", &n, &m);
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		scanf("%d%d%d%d", x[i], &a, &b, c + i);
		for (int j = 1; j < c[i]; ++j) {
			x[i][j] = (a * x[i][j - 1] + b) % c[i];
			if (x[i][p[i]] < x[i][j]) p[i] = j;
			//printf("%d%c", x[i][j], " \n"[j == c[i] - 1]);
		}
		ans += x[i][p[i]];
	}
	if (ans % m == 0) {
		int det = ans;
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < c[i]; ++j) {
				int d = x[i][p[i]] - x[i][j]; 
				if (d % m && det > d) {
					det = d;
					s = i;
					t = j;
				}
			}
		ans -= det;
		p[s] = t;
	}
	if (ans % m) {
		printf("%d\n", ans);
		for (int i = 0; i < n; ++i) printf("%d%c", p[i], " \n"[i == n - 1]);
	} else {
		puts("-1");
	}
	return 0;
}
