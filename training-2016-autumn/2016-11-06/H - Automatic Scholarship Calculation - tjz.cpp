#include <stdio.h>
#include <cstring>
const int maxn = 401;
int n, m, s[maxn], ans;
int main()
{
	while(scanf("%d%d", &n, &m) == 2 && n + m)
	{
		ans = 0;
		memset(s, 0, sizeof s);
		while(n--)
		{
			int x, y;
			scanf("%1d.%2d", &x, &y);
			++s[x * 100 + y];
		}
		for(int i = 399; i >= 0; --i)
			s[i] += s[i + 1];
		for(int low = 399; low >= 250; --low)
		{
			if(s[low] * 100 < m)
				continue;
			for(int len = 1; low + len <= 400; ++len)
			{
				int x = 0, y = 0, mx = 0;
				for(int i = low, c = 0; i <= 400; i += len, ++c)
				{
					int num = s[i] - (i + len <= 400 ? s[i + len] : 0);
					x += num;
					y += num * c;
					mx = c;
				}
				for(int d = 1; d * mx <= 100; ++d)
				{
					int ax = m - d * y;
					if(ax % x == 0)
					{
						int a = ax / x;
						if(a >= 1 && a + d * mx <= 100)
							++ans;
					}
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
