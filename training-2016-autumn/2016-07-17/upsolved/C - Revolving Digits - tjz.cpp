#include <stdio.h>
#include <cstring>
const int maxn = 100001;
int t, n, z[maxn];
char str[maxn << 1];
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%s", str);
		n = strlen(str);
		for(int i = 0; i < n; ++i)
			str[n + i] = str[i];
		str[n << 1] = '\0';
		for(int i = 1, L = 0, R = 1; i < n; ++i)
		{
			if(i < R && i + z[i - L] < R)
			{
				z[i] = z[i - L];
				continue;
			}
			int x = i < R ? R : i;
			for( ; str[x - i] == str[x]; ++x);
			z[i] = x - i;
			if(i < x)
			{
				L = i;
				R = x;
			}
		}
		int les = 0, eq = 1, gre = 0;
		for(int i = 1; i < n; ++i)
			if(z[i] >= n)
				++eq;
			else
				str[z[i]] < str[i + z[i]] ? ++gre : ++les;
		printf("Case %d: %d %d %d\n", Case, les / eq, 1, gre / eq);
	}
	return 0;
}
