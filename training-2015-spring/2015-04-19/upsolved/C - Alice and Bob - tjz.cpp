#include <cstdio>
int t, n, cnt;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		cnt = 0;
		scanf("%d", &n);
		for(int i = 0; n >> i; ++i)
			if(!((n >> i) & 1))
				++cnt;
		printf("%d\n", n ? 1 << cnt : 0);
	}
	return 0;
}
