#include <cstdio>
#include <algorithm>

using std::max;

constexpr int n = 100;
int T, s, m;
int f[n + 9][5009];
int w[19];

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &s, &m);
		for (int i = 0; i < m; ++i) scanf("%d", w + i);
		for (int i = 0; i < n + 9; ++i) for (int j = 0; j < 5009; ++j)
			f[i][j] = 0x80000000;
		f[0][0] = 0;
		int ans = -1;
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j <= s; ++j)
				for (int k = 0; k < m; ++k) {
					if (i * w[k] <= j)
						f[i][j] = max(f[i][j], f[i - 1][j - i * w[k]] + w[k]);
				}
			ans = max(ans, f[i][s]);
		}
		printf("%d\n", ans);
	}
	return 0;
}
