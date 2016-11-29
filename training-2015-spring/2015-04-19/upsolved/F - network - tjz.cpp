#include <cstdio>
#include <cstring>
const int maxn = 31;
int f[maxn][maxn], t, n, m, deg[maxn];
double ans;
int main()
{
	for(int i = 0; i < maxn; ++i)
	{
		f[i][0] = f[i][i] = 1;
		for(int j = 1; j < i; ++j)
			f[i][j] = f[i - 1][j - 1] + f[i - 1][j];
	}
	for(int i = 0; i < maxn; ++i)
		for(int j = i; j; --j)
			f[i][j - 1] += f[i][j];
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		memset(deg, 0, n * sizeof(int));
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
			{
				int x;
				scanf("%d", &x);
				if(x)
					++deg[i];
			}
		ans = 0;
		for(int i = 0; i < n; ++i)
			ans += f[deg[i]][m] / (double)(1 << deg[i] + 1);
		printf("%.3f\n", ans);
	}
	return 0;
}
