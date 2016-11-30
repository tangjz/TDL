#include <stdio.h>
#include <algorithm>
typedef long long LL;
int t;
LL da, db, dc, sa, sb, sc;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%lld%lld%lld", &da, &db, &dc);
		sa += da, sb += db, sc += dc;
		LL out = std::min(sa, std::min(sb, sc));
		if(out < 30)
		{
			puts("NO");
			continue;
		}
		printf("%lld\n", out);
		sa -= out, sb -= out, sc -= out;
	}
	return 0;
}
