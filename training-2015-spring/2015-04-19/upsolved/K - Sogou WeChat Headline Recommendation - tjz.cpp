#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 100001, maxm = 1000001;
int t, n, m, d, ans;
struct Article
{
	int num, val, id;
	bool flag;
	bool operator < (const Article &t) const
	{
		return val > t.val || val == t.val && id < t.id;
	}
} p[maxn];
bool cmp(const Article &a, const Article &b)
{
	return a.num < b.num || a.num == b.num && a < b;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		ans = 0;
		scanf("%d%d%d", &n, &m, &d);
		for(int i = 0; i < n; ++i)
		{
			scanf("%d%d", &p[i].val, &p[i].num);
			p[i].id = i;
			p[i].flag = 0;
		}
		sort(p, p + n, cmp);
		for(int i = 0; i < n; ++i)
			if(!i || p[i - 1].num != p[i].num)
			{
				p[i].val += d;
				p[i].flag = 1;
			}
		sort(p, p + n);
		for(int i = 0; i < m; ++i)
		{
			ans += p[i].val;
			if(p[i].flag)
				p[i].val -= d;
		}
		sort(p, p + m);
		printf("%d\n", ans);
		for(int i = 0; i < m; ++i)
			printf("%d%c", p[i].id + 1, " \n"[i == m - 1]);
	}
	return 0;
}
