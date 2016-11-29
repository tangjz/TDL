#include <cstdio>
#include <cstring>
const int maxn = 12, maxs = 100001, INF = 0x3f3f3f3f;
typedef long long LL;
int t, alen, anum[maxn], blen, bnum[maxn], f[maxn][maxs], ans;
LL a, b;
void str2num(LL x, int &len, int num[])
{
	for(len = 0; x; x /= 10)
		num[len++] = x % 10;
	if(!len)
		num[len++] = 0;
}
void upd(int &x, int y)
{
	if(x > y)
		x = y;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		ans = INF;
		scanf("%lld%lld", &a, &b);
		str2num(a, alen, anum);
		if(b < a / b)
		{
			memset(f[0], 0x3f, (int)b * sizeof(int));
			f[0][0] = 0;
			for(int i = 0; i < alen; ++i)
			{
				memset(f[i + 1], 0x3f, (int)b * sizeof(int));
				for(int j = 0; j < (int)b; ++j)
				{
					if(f[i][j] == INF)
						continue;
					for(int k = 0; k < 10; ++k)
						upd(f[i + 1][(j * 10 + k) % (int)b], f[i][j] + (anum[alen - 1 - i] != k));
				}
			}
			ans = f[alen][0];
		}
		else
		{
			LL lim = 1;
			for( ; lim <= a; lim *= 10);
			for(LL a2 = 0; a2 < lim; a2 += b)
			{
				str2num(a2, blen, bnum);
				int cnt = 0;
				for(int i = 0; i < alen; ++i)
					cnt += anum[i] != (i < blen ? bnum[i] : 0);
				if(ans > cnt)
					ans = cnt;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
