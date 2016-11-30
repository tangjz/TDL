#include <cstdio>
#include <cstring>

typedef unsigned long long u64;
int T, n, a[79];
char c;
u64 f[79][10][2][2];

bool check() {
	bool flag = false;
	for (int i = 2; i <= n; ++i) {
		if (a[i] > a[i - 1] && flag) return false;
		if (a[i] < a[i - 1]) flag = true;
	}
	return true;
}

int main() {
	scanf("%d%*c", &T);
	while (T--) {
		n = 0;
		while ((c = getchar()) != '\n') a[++n] = c - '0';
		if (!check()) {
			puts("-1");
			continue;
		}
		memset(f, 0, sizeof f);
		f[0][0][0][0] = 1;
		for (int i = 1; i <= n; ++i) for (int j = 0; j < 10; ++j) {
			for (int k = 0; k < 10; ++k) {
				if (j == a[i]) {
					if (j > k) {
						f[i][j][0][0] += f[i - 1][k][0][0];
						f[i][j][1][0] += f[i - 1][k][1][0];
					}
					if (j < k) {
						f[i][j][0][1] += f[i - 1][k][0][1];
						f[i][j][1][1] += f[i - 1][k][1][1];
						f[i][j][0][1] += f[i - 1][k][0][0];
						f[i][j][1][1] += f[i - 1][k][1][0];
					}
					if (j == k) {
						f[i][j][0][0] += f[i - 1][k][0][0];
						f[i][j][1][0] += f[i - 1][k][1][0];
						f[i][j][0][1] += f[i - 1][k][0][1];
						f[i][j][1][1] += f[i - 1][k][1][1];
					}
				} else if (j > a[i]) {
					if (j > k)
						f[i][j][1][0] += f[i - 1][k][1][0];
					if (j < k) {
						f[i][j][1][1] += f[i - 1][k][1][1];
						f[i][j][1][1] += f[i - 1][k][1][0];
					}
					if (j == k) {
						f[i][j][1][0] += f[i - 1][k][1][0];
						f[i][j][1][1] += f[i - 1][k][1][1];
					}
				} else if (j < a[i]) {
					if (j > k) {
						f[i][j][1][0] += f[i - 1][k][1][0];
						f[i][j][1][0] += f[i - 1][k][0][0];
					}
					if (j < k) {
						f[i][j][1][1] += f[i - 1][k][0][1];
						f[i][j][1][1] += f[i - 1][k][0][0];
						f[i][j][1][1] += f[i - 1][k][1][1];
						f[i][j][1][1] += f[i - 1][k][1][0];
					}
					if (j == k) {
						f[i][j][1][1] += f[i - 1][k][0][1];
						f[i][j][1][0] += f[i - 1][k][0][0];
						f[i][j][1][1] += f[i - 1][k][1][1];
						f[i][j][1][0] += f[i - 1][k][1][0];
					}
				}
			}
		}
		u64 ans = 0;
		for (int i = 0; i < 10; ++i) {
			ans += f[n][i][0][0];
			ans += f[n][i][0][1];
			ans += f[n][i][1][0];
			ans += f[n][i][1][1];
		}
		printf("%I64u\n", ans - 1);
	}
	return 0;
}
