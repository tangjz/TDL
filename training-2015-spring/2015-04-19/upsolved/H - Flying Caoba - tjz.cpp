#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 100002;
typedef pair<int, int> Point;
int n, m, t, fa[maxn];
Point p[maxn];
struct Hash
{
	int idx;
	Point val;
	bool operator == (const Hash &t) const
	{
		return val == t.val;
	}
	bool operator < (const Hash &t) const
	{
		return val < t.val;
	}
} e[maxn];
int dsu_find(int x)
{
	return x == fa[x] ? x : fa[x] = dsu_find(fa[x]);
}
void dsu_merge(int x, int y)
{
	if((x = dsu_find(x)) != (y = dsu_find(y)))
		fa[x] = y;
}
int main()
{
	for(int Case = 1; scanf("%d%d%d", &n, &m, &t) == 3; ++Case)
	{
		for(int i = 1; i <= t; ++i)
			scanf("%d%d", &p[i].first, &p[i].second);
		sort(p + 1, p + t + 1);
		t = unique(p + 1, p + t + 1) - p - 1;
		for(int i = 0; i <= t + 1; ++i)
			fa[i] = i;
		for(int i = 1; i <= t; ++i)
		{
			e[i] = (Hash){i, p[i]};
			if(p[i].first == 1 || p[i].second == m)
				dsu_merge(0, i);
			if(p[i].first == n || p[i].second == 1)
				dsu_merge(i, t + 1);
		}
		for(int i = 1; i <= t; ++i)
			for(int dx = -1; dx <= 1; ++dx)
				for(int dy = -1; dy <= 1; ++dy)
				{
					Hash pp = (Hash){0, {p[i].first + dx, p[i].second + dy}};
					int pos = lower_bound(e + 1, e + t + 1, pp) - e;
					if(pos <= t && pp == e[pos])
						dsu_merge(i, e[pos].idx);
				}
		printf("Case #%d: %s\n", Case, dsu_find(0) != dsu_find(t + 1) ? "YES" : "NO");
	}
	return 0;
}
