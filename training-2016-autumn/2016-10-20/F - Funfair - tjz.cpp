#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 101;
int n, m, x;
double f[maxn][maxn];
struct Game
{
	int A, L, P;
	bool operator < (const Game &t) const
	{
		return A * P * t.L * (100 - t.P) < t.A * t.P * L * (100 - P);
	}
} a[maxn];
int main()
{
	while(scanf("%d%d%d", &n, &m, &x) == 3 && n + m + x)
	{
		for(int i = 1; i <= n; ++i)
			scanf("%d%d%d", &a[i].A, &a[i].L, &a[i].P);
		sort(a + 1, a + n + 1);
		f[0][0] = x;
		for(int i = 1; i <= n; ++i)
		{
			memcpy(f[i], f[i - 1], i * sizeof(double));
			f[i][i] = 0;
			double k = 1 - a[i].L / 100.0 * (1 - a[i].P / 100.0), b = a[i].A * a[i].P / 100.0;
			for(int j = 1; j <= i; ++j)
			{
				double tmp = k * f[i - 1][j - 1] + b;
				if(f[i][j] < tmp)
					f[i][j] = tmp;
			}
		}
		printf("%.2f\n", f[n][m]);
	}
	return 0;
}
