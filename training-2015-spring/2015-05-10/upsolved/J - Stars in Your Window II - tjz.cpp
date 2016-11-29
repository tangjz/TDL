#include <map>
#include <cmath>
#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
#define x first
#define y second
typedef long long LL;
const int maxn = 100001;
int n, sz, m, fir[maxn], ord[maxn], idx[maxn], pos[maxn];
pair<int, int> a[maxn];
map<pair<int, int>, int> Hash;
bool vis[maxn];
LL ans;
bool cmp(const int &u, const int &v)
{
	return a[u].y < a[v].y;
}
int main()
{
	while(scanf("%d", &n) == 1)
	{
		sz = (int)ceil(sqrt(n * 0.1));
		m = 0;
		map<pair<int, int>, int>().swap(Hash);
		ans = 0;
		memset(vis, 0, n * sizeof(bool));
		for(int i = 0; i < n; ++i)
		{
			scanf("%d%d", &a[i].x, &a[i].y);
			ord[i] = i;
		}
		a[n].x = a[n].y = ~0u >> 1;
		sort(a, a + n);
		sort(ord, ord + n, cmp);
		for(int i = 0; i < n; ++i)
		{
			if(!i || a[i - 1].x != a[i].x)
				fir[m++] = i;
			pos[i] = m - 1;
		}
		for(int i = 0; i < n; ++i)
			idx[i] = pos[ord[i]];
		fir[m] = n;
		for(int i = 0; i < m; ++i)
		{
			int L = fir[i], R = fir[i + 1];
			if(R - L <= sz)
			{
				for(int j = L; j < R; ++j)
					for(int k = j + 1; k < R; ++k)
						ans += Hash[make_pair(a[j].y, a[k].y)]++;
				continue;
			}
			for(int j = L; j < R; ++j)
				vis[j] = 1;
			memset(pos, 0, m * sizeof(int));
			for(int j = 0, k = L; j < n && k < R; ++j)
			{
				for( ; k < R && a[k].y < a[ord[j]].y; ++k);
				if(!vis[ord[j]] && a[ord[j]].y == a[k].y)
					ans += pos[idx[j]]++;
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
