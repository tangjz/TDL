#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100001, maxs = 200001;
typedef long long LL;
int t, n, q, m, len, pos[maxs], sz[maxs];
int sa[maxs], rk[maxs], ht[maxs];
int que[maxs], L, R, cnt[maxn], seg[maxs << 1];
LL f[maxn];
char str[maxs], tmp[maxs];
inline int idx(int L, int R)
{
	return L + R | L != R;
}
inline void upd(int &x, int y)
{
	if(x < y)
		x = y;
}
void update(int L, int R, int l, int r, int x)
{
	if(l <= L && R <= r)
	{
		upd(seg[idx(L, R)], x);
		return;
	}
	int M = L + R >> 1;
	if(l <= M)
		update(L, M, l, r, x);
	if(r > M)
		update(M + 1, R, l, r, x);
}
void query(int L, int R)
{
	int o = idx(L, R);
	if(L == R)
	{
		if(pos[sa[L]] != -1)
			f[pos[sa[L]]] += min(sz[sa[L]], seg[o]);
		return;
	}
	int M = L + R >> 1, lch = idx(L, M), rch = idx(M + 1, R);
	upd(seg[lch], seg[o]);
	upd(seg[rch], seg[o]);
	query(L, M);
	query(M + 1, R);
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d%d", &n, &q, &m);
		// read and merge string
		len = 0;
		for(int i = 0; i < n; ++i)
		{
			scanf("%s", tmp);
			int tlen = strlen(tmp);
			for(int j = 0; j < tlen; ++j)
			{
				str[len] = tmp[j];
				sz[len] = tlen - j;
				pos[len++] = i;
			}
			str[len] = '#';
			pos[len++] = -1;
		}
		str[len] = '\0';
		// construct suffix array
		{
			int tot = 256, *x = rk, *y = ht, *c = que;
			memset(c, 0, tot * sizeof(int));
			for(int i = 0; i < len; ++i)
				++c[x[i] = str[i]];
			for(int i = 1; i < tot; ++i)
				c[i] += c[i - 1];
			for(int i = len - 1; i >= 0; --i)
				sa[--c[x[i]]] = i;
			for(int k = 1; k < len; k <<= 1)
			{
				int tmp = 0;
				for(int i = len - k; i < len; ++i)
					y[tmp++] = i;
				for(int i = 0; i < len; ++i)
					if(sa[i] >= k)
						y[tmp++] = sa[i] - k;
				memset(c, 0, tot * sizeof(int));
				for(int i = 0; i < len; ++i)
					++c[x[y[i]]];
				for(int i = 1; i < tot; ++i)
					c[i] += c[i - 1];
				for(int i = len - 1; i >= 0; --i)
					sa[--c[x[y[i]]]] = y[i];
				swap(x, y);
				tmp = 1;
				x[sa[0]] = 0;
				for(int i = 1; i < len; ++i)
					x[sa[i]] = y[sa[i - 1]] == y[sa[i]] && (sa[i - 1] + k < len ? y[sa[i - 1] + k] : -1) == (sa[i] + k < len ? y[sa[i] + k] : -1) ? tmp - 1 : tmp++;
				if(tmp >= len)
					break;
				tot = tmp;
			}
			for(int i = 0; i < len; ++i)
				rk[sa[i]] = i;
			ht[0] = 0;
			for(int i = 0, j, k = 0; i < len; ++i)
			{
				if(k)
					--k;
				if(!rk[i])
					continue;
				for(j = sa[rk[i] - 1]; str[i + k] == str[j + k]; ++k);
				ht[rk[i]] = k;
			}
		}
		// change the number of dangerous parts
		L = R = 0;
		memset(cnt, 0, n * sizeof(int));
		memset(seg, 0, (len << 1) * sizeof(int));
		for(int i = 0, j = 0, tot = 0; i < len; ++i)
		{
			if(pos[sa[i]] == -1)
			{
				++j;
				continue;
			}
			if(!cnt[pos[sa[i]]])
				++tot;
			++cnt[pos[sa[i]]];
			if(j < i)
			{
				while(L < R && ht[que[R - 1]] >= ht[i])
					--R;
				que[R++] = i;
			}
			for( ; j < i && (L < R && !ht[que[L]]); ++j)
			{
				--cnt[pos[sa[j]]];
				if(!cnt[pos[sa[j]]])
					--tot;
				if(L < R && j + 1 == que[L])
					++L;
			}
			for( ; j <= i && tot > m; ++j)
			{
				update(0, len - 1, j, i, j < i ? ht[que[L]] : sz[sa[i]]);
				if(i + 1 < len && tot == m + 1 && cnt[pos[sa[j]]] == 1)
					break;
				--cnt[pos[sa[j]]];
				if(!cnt[pos[sa[j]]])
					--tot;
				if(L < R && j + 1 == que[L])
					++L;
			}
		}
		// prepare f[i] : number of string i's dangerous parts
		memset(f, 0, n * sizeof(LL));
		query(0, len - 1);
		// deal with query
		sort(f, f + n);
		while(q--)
		{
			LL x;
			scanf("%lld", &x);
			printf("%d\n", n - (upper_bound(f, f + n, x) - f));
		}
	}
	return 0;
}
