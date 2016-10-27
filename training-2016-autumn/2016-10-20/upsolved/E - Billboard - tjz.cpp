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
	while(scanf("%d%d%d%d", &m, &n, &r, &s) == 4 && m + n + r + s)
	{
		for(int j = 1; j <= m; ++j)
			for(int i = 1; i <= n; ++i)
			{
				scanf("%d", f[i] + j);
				f[i][j] = f[i - 1][j] + !f[i][j];
			}
		ans = 0;
		for(int i = 1; i <= m; ++i)
			ord[i] = i;
		for(int len = n; len >= 1 && ans < m * len; --len)
			for(int L = 0, R = len; R <= n && ans < m * len; ++L, ++R)
			{
				int mx = 0;
				for(int i = 1; i <= m; ++i)
					g[i] = f[R][i] - f[L][i];
				sort(ord + 1, ord + m + 1, cmp);
				for(int i = 1; i <= m; ++i)
					pos[ord[i]] = i;
				memset(seg, 0, (m + 1 << 1) * sizeof(Segment));
				for(int i = 1, j = 1; i <= m; ++i)
				{
					for(upd(1, m, i, 1); j + r <= i && chk(1, m, r) > s; upd(1, m, j++, -1));
					if(mx < i - j + 1)
						mx = i - j + 1;
				}
				if(ans < mx * len)
					ans = mx * len;
			}
		printf("%d\n", ans);
	}
	return 0;
}
