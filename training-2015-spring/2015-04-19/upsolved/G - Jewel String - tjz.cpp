#include <cstdio>
const int maxn = 100001, maxs = 10;
int a[maxs], b[maxs], ans;
char str[maxn];
bool check()
{
	for(int i = 0; i < maxs; ++i)
		if(a[i] > b[i])
			return 0;
	return 1;
}
int main()
{
	while(scanf("%s", str) == 1)
	{
		ans = maxn;
		for(int i = 0; i < maxs; ++i)
		{
			scanf("%d", a + i);
			b[i] = 0;
		}
		for(int i = 0, j = 0; str[i]; ++i)
		{
			++b[str[i] - '0'];
			for( ; j <= i && check(); --b[str[j++] - '0'])
				if(ans > i - j + 1)
					ans = i - j + 1;
		}
		if(ans < maxn)
			printf("%d\n", ans);
		else
			puts("No Solution");
	}
	return 0;
}
