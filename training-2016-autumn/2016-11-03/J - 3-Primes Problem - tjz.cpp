#include <stdio.h>
#include <algorithm>
const int maxn = 1001, maxd = 4;
int tot, prime[maxn], d[maxn], f[maxd][maxn], t, n, out[maxd];
int main()
{
	for(int i = 2; i < maxn; ++i)
	{
		if(!d[i])
			prime[tot++] = d[i] = i;
		for(int j = 0; i * prime[j] < maxn; ++j)
		{
			d[i * prime[j]] = prime[j];
			if(d[i] == prime[j])
				break;
		}
	}
	f[0][0] = 1;
	for(int i = 1; i < maxd; ++i)
		for(int j = 1; j < maxn; ++j)
			for(int k = 0; k < tot && prime[k] <= j; ++k)
				if(f[i - 1][j - prime[k]] > 0)
				{
					f[i][j] = prime[k];
					break;
				}
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		if(!f[maxd - 1][n])
		{
			puts("0");
			continue;
		}
		for(int i = maxd - 1, j = n; i > 0; j -= f[i--][j])
			out[i] = f[i][j];
		std::sort(out + 1, out + maxd);
		for(int i = 1; i < maxd; ++i)
			printf("%d%c", out[i], " \n"[i == maxd - 1]);
	}
	return 0;
}
