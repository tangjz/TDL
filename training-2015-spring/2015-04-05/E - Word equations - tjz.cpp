#include <cstdio>
#include <cstring>
const int maxn = 2010, maxm = 510, maxs = 10, maxd = 10;
const int mod = 960991, mod1 = 1000000007;
int tot, pre[mod];
struct Hash
{
	int nxt, val, idx;
} e[maxm * 2];
int idx(char *s)
{
	int res = 0;
	for(int i = 0; s[i]; ++i)
		res = ((long long)res * 29 + s[i] - 'A') % mod1;
	for(int it = pre[res % mod]; it != -1; it = e[it].nxt)
		if(e[it].val == res)
			return e[it].idx;
	e[tot] = (Hash){pre[res % mod], res, tot + 1};
	pre[res % mod] = tot++;
	//printf("%s : %d\n", s, tot);
	return tot;
}
int t, n, m, l[maxm], r[maxm], f[maxm][maxn][maxd];
char str[maxn], word[maxm][maxs], tmp[maxs * 10], a[maxs], b[maxs], c[maxs];
bool vis[maxm];
int upd(int x, int y)
{
	return x > y ? x : y;
}
int upd(int g[maxn][maxd], int l, int r)
{
	if(r == n)
		return n;
	int len = r - l + 1, d;
	for(d = 1; 1 << d <= len; ++d);
	--d;
	return upd(g[l][d], g[r - (1 << d) + 1][d]);
}
void dfs(int x)
{
	if(vis[x])
		return;
	memset(f[x], 0, sizeof f[x]);
	if(!l[x])
	{
		for(int i = 0; i < n; ++i)
		{
			int j = 0, len = strlen(word[x]);
			for(int k = 0; k < len && i + j < n; ++k)
				if(str[i + j] == word[x][k])
					++j;
			f[x][i][0] = i + j;
		}
		//printf("%s :", word[x]);
		//for(int i = 0; i < n; ++i)
		//	printf(" %d", f[x][i][0]);
		//puts("");
	}
	else
	{
		dfs(l[x]);
		dfs(r[x]);
		for(int i = 0; i < n; ++i)
		{
			f[x][i][0] = upd(f[r[x]], i, f[l[x]][i][0]);
			//printf("%d %d : %d : %d - %d\n", x, i, r[x], i, f[l[x]][i][0]);
		}
		//printf("%d :", x);
		//for(int i = 0; i < n; ++i)
		//	printf(" %d", f[x][i][0]);
		//puts("");
	}
	for(int d = 1; d < maxd; ++d)
		for(int i = 0; i < n; ++i)
		{
			f[x][i][d] = upd(f[x][i][d - 1], i + (1 << d - 1) < n ? f[x][i + (1 << d - 1)][d - 1] : 0);
			//if(d <= 3) printf("%d %d - %d : %d\n", x, i, i + (1 << d) - 1, f[x][i][d]);
		}
	vis[x] = 1;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		tot = 0;
		memset(pre, -1, sizeof pre);
		memset(l, 0, sizeof l);
		memset(vis, 0, sizeof vis);
		scanf("%d\n", &m);
		for(int i = 0; i < m; ++i)
		{
			gets(tmp);
			bool flag = 0;
			for(int j = 0; tmp[j] && !flag; ++j)
				if(tmp[j] == '+')
					flag = 1;
			if(!flag)
			{
				sscanf(tmp, "%s = %s", a, b);
				strcpy(word[idx(a)], b);
			}
			else
			{
				sscanf(tmp, "%s = %s + %s", a, b, c);
				int id = idx(a);
				l[id] = idx(b);
				r[id] = idx(c);
			}
		}
		scanf("%s%s", tmp, str);
		n = strlen(str);
		int root = idx(tmp);
		dfs(root);
		puts(f[root][0][0] >= n ? "YES" : "NO");
	}
	return 0;
}
