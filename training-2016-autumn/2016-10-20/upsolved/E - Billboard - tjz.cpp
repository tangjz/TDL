#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 301;
int n, m, r, s, f[maxn][maxn], g[maxn], ord[maxn], pos[maxn], ans;
bool cmp(const int &x, const int &y)
{
	return g[x] < g[y];
}
struct Segment
{
	int cnt, sum;
} seg[maxn << 1];
inline int seg_idx(int L, int R)
{
	return (L + R) | (L < R);
}
void upd(int L, int R, int idx, int sgn)
{
	int x = pos[idx], v = sgn < 0 ? -g[idx] : g[idx];
	while(1)
	{
		int rt = seg_idx(L, R);
		seg[rt].cnt += sgn;
		seg[rt].sum += v;
		if(L == R)
			break;
		int M = L + R >> 1;
		if(x <= M)
			R = M;
		else
			L = M + 1;
	}
}
int chk(int L, int R, int tot)
{
	int rt = seg_idx(L, R), ret = seg[rt].sum;
	while(tot)
	{
		int M = L + R >> 1, rch = seg_idx(M + 1, R);
		if(seg[rch].cnt <= tot)
		{
			tot -= seg[rch].cnt;
			ret -= seg[rch].sum;
			R = M;
		}
		else
			L = M + 1;
	}
	return ret;
}
int main()
{
	while(scanf("%d%d%d%d", &n, &m, &r, &s) == 4 && n + m + r + s)
	{
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
				scanf("%d", f[i] + j);
		ans = 0;
		for(int i = 0; i < n; ++i)
			ord[i] = i;
		for(int L = 0; L < m; ++L)
		{
			memset(g, 0, n * sizeof(int));
			for(int R = L; R < m; ++ R)
			{
				int mx = 0;
				for(int i = 0; i < n; ++i)
					g[i] += !f[i][R];
				if(ans >= n * (R - L + 1))
					continue;
				sort(ord, ord + n, cmp);
				for(int i = 0; i < n; ++i)
					pos[ord[i]] = i;
				memset(seg, 0, (n << 1) * sizeof(Segment));
				for(int i = 0, j = 0; i < n; ++i)
				{
					for(upd(0, n - 1, i, 1); j + r <= i && chk(0, n - 1, r) > s; upd(0, n - 1, j++, -1));
					if(mx < i - j + 1)
						mx = i - j + 1;
				}
				if(ans < mx * (R - L + 1))
					ans = mx * (R - L + 1);
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
