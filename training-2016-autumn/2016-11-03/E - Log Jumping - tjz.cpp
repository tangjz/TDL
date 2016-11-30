#include <stdio.h>
#include <algorithm>
const int maxn = 10001;
int t, n, a[maxn];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		std::sort(a, a + n);
		int mx = 0;
		for(int i = 2; i < n; ++i)
			mx = std::max(mx, a[i] - a[i - 2]);
		printf("%d\n", mx);
	}
	return 0;
}
