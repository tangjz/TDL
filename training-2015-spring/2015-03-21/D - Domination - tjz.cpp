#include <cstdio>
#include <cstring>
#include <cmath>
const double eps = 1e-12;
const int maxn = 51;
int n, m;
long double f[maxn * maxn][maxn][maxn], ans, ans2;
int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		ans = 0;
		scanf("%d%d", &n, &m);
		memset(f, 0, sizeof f);
		f[0][0][0] = 1;
		for(int i = 1; i <= n * m; ++i)
		{
			double tot = 0;
			for(int j = 1; j <= n; ++j)
				for(int k = 1; k <= m; ++k)
				{
					double fact = n * m - i + 1;
					if(j * k - i + 1 >= 0 && (j != n || k != m))
						f[i][j][k] += (j * k - i + 1) / fact * f[i - 1][j][k];
					f[i][j][k] += (n - j + 1) * k / fact * f[i - 1][j - 1][k];
					f[i][j][k] += j * (m - k + 1) / fact * f[i - 1][j][k - 1];
					f[i][j][k] += (n - j + 1) * (m - k + 1) / fact * f[i - 1][j - 1][k - 1];
					tot += f[i][j][k];
				}
			ans += f[i][n][m] * i;
		}
		printf("%.8f\n", (double)ans);
	}
	return 0;
}
