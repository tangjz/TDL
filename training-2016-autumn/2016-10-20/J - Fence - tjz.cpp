#include <stdio.h>
#include <algorithm>
using namespace std;
#define x first
#define y second
typedef long long LL;
const int maxn = 10001;
int n, m;
pair<int, int> p[maxn], q[maxn];
int main()
{
	while(scanf("%d", &n) == 1 && n)
	{
		for(int i = 0; i < n; ++i)
			scanf("%d%d", &p[i].x, &p[i].y);
		sort(p, p + n);
		m = 0;
		for(int i = 0; i < n; ++i)
		{
			for( ; m > 1 && (LL)(q[m - 1].x - q[m - 2].x) * (p[i].y - q[m - 2].y) - (LL)(q[m - 1].y - q[m - 2].y) * (p[i].x - q[m - 2].x) <= 0; --m);
			q[m++] = p[i];
		}
		int t = m;
		for(int i = n - 2; i >= 0; --i)
		{
			for( ; m > t && (LL)(q[m - 1].x - q[m - 2].x) * (p[i].y - q[m - 2].y) - (LL)(q[m - 1].y - q[m - 2].y) * (p[i].x - q[m - 2].x) <= 0; --m);
			q[m++] = p[i];
		}
		if(n > 1)
			--m;
		LL a = 0, b = 0;
		for(int i = 0, j = 1; i < m; ++i, j = j + 1 < m ? j + 1 : 0)
		{
			pair<int, int> delta = make_pair(abs(q[i].x - q[j].x), abs(q[i].y - q[j].y));
			a += delta.x + delta.y - (min(delta.x, delta.y) << 1);
			b += min(delta.x, delta.y);
		}
		printf("%lld %lld\n", a, b);
	}
	return 0;
}
