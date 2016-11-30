#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int T, n, c, a[9][9];
char s[9][9];
bool ux[9][9], uy[9][9];

bool dfs(int x, int y) {
	if (x == n + 1 && y == n + 1) return true;
	if (x == n + 1) {
		int u = 0, d = 0, m = 0;
		for (int i = 1; i <= n; ++i)
			if (m < a[i][y]) m = a[i][y], ++u;
		m = 0;
		for (int i = n; i >= 1; --i)
			if (m < a[i][y]) m = a[i][y], ++d;
		if (a[0][y] && a[0][y] != u) return false;
		if (a[n + 1][y] && a[n + 1][y] != d) return false;
		return dfs(x, y + 1);
	}
	if (y == n + 1) {
		int l = 0, r = 0, m = 0;
		for (int i = 1; i <= n; ++i)
			if (m < a[x][i]) m = a[x][i], ++l;
		m = 0;
		for (int i = n; i >= 1; --i)
			if (m < a[x][i]) m = a[x][i], ++r;
		if (a[x][0] && a[x][0] != l) return false;
		if (a[x][n + 1] && a[x][n + 1] != r) return false;
		return dfs(x + 1, 1);
	}
	if (a[x][y]) return dfs(x, y + 1);
	for (int i = 1; i <= n; ++i)
		if (!ux[x][i] && !uy[y][i]) {
			ux[x][i] = uy[y][i] = true;
			a[x][y] = i;
			if (dfs(x, y + 1)) return true;
			a[x][y] = 0;
			ux[x][i] = uy[y][i] = false;
		}
	return false;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i <= n + 1; ++i) {
			scanf("%s", s[i]);
			for (int j = 0; j <= n + 1; ++j)
				a[i][j] = s[i][j] == '-'? 0 : s[i][j] - '0';
		}
		memset(ux, 0, sizeof ux);
		memset(uy, 0, sizeof uy);
		for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j)
			if (a[i][j]) ux[i][a[i][j]] = uy[j][a[i][j]] = true;
		if (dfs(1, 1)) {
			for (int i = 1; i <= n; ++i) {
				for (int j = 1; j <= n; ++j)
					printf("%d", a[i][j]);
				putchar('\n');
			}
		} else {
			puts("no");
		}
		putchar('\n');
	}
	return 0;
}
