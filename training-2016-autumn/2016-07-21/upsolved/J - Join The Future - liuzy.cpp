#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int NMAX = 50, MOD = 1000000007;

int T, N, M;
int father[NMAX], weight[NMAX], lw[NMAX], hi[NMAX], sum[NMAX][2], mask[2] = {1, 6};
int flag, exist, ans, ans2[NMAX], state[NMAX], choose[NMAX], sol[2][NMAX];

int find(int x)
{
	int p, w, ptmp, wtmp;
	for(p = x, w = 0;father[p] >= 0;p = father[p])
		w = w ^ weight[p];
	for(;x != p;)
	{
		ptmp = father[x];
		wtmp = weight[x];
		father[x] = p;
		weight[x] = w;
		x = ptmp;
		w = w ^ wtmp;
	}
	return p;
}

bool check(int x, int y, int w)
{
	int X = find(x), Y = find(y);
	return X != Y || (weight[x] ^ weight[y]) == w;
}

void Union(int x, int y, int w)
{
	int X = find(x), Y = find(y);
	if(X == Y)
		return;
	if(X > Y)
		swap(X, Y);
	w = w ^ weight[x] ^ weight[y];
	father[X] += father[Y];
	father[Y] = X;
	weight[Y] = w;
}

/*
  choose: l .    .    . h
            ^ even valid
                 ^ odd valid
                      ^ which one is smaller
  6 = (110)_2 means even solution is invalid, odd solution is valid and odd solution is smaller
  3 = (011)_2 means both even and odd solution are valid, and even solution is smaller
*/
void DFS(int x, int even, int odd, int tot)
{
	int i, j, pre[2] = {even, odd}, valid[2] = {choose[x - 1] & 1, (choose[x - 1]>>1) & 1};
	int prime[2] = {choose[x - 1]>>2, 1 - (choose[x - 1]>>2)}, can;
	if(!(choose[x - 1] & 3))
		return;
	if(x == N + 1)
	{
		ans = (ans + tot * ((long long)even + odd)) % MOD;
		if((choose[N] & 3) && !exist)
		{
			exist = 1;
			for(i = N, j = (choose[N]>>2);i;i -= 1)
			{
				ans2[i] = sol[j][i];
				j = j ^ (sol[j][i] & 1);
			}
		}
		return;
	}
	pair<int, int> e(2, 2), o(2, 2);
	for(i = 0;i < 2 && lw[x] + i <= hi[x];i += 1)
	{
		choose[x] |= valid[(lw[x] + i) & 1] | (valid[1 - ((lw[x] + i) & 1)]<<1);
		if(valid[(lw[x] + i) & 1])
			e = min(e, make_pair(prime[(lw[x] + i) & 1], i));
		if(valid[1 - ((lw[x] + i) & 1)]<<1)
			o = min(o, make_pair(prime[1 - ((lw[x] + i) & 1)], i));
	}
	can = choose[x] | 4;
	choose[x] |= ((bool)(o < e))<<2;
	sol[0][x] = lw[x] + e.second;
	sol[1][x] = lw[x] + o.second;
	if(father[x] == -1)
	{
		DFS(x + 1, ((long long)even * sum[x][0] + (long long)odd * sum[x][1]) % MOD,
			((long long )even * sum[x][1] + (long long)odd * sum[x][0]) % MOD, tot);
	}
	else if(father[x] < 0)
	{
		for(i = 0, j = choose[x]>>2;i < 2;i += 1, j = 1 - j)
		{
			state[x] = j;
			choose[x] = mask[j] & can;
			DFS(x + 1, 1 - j, j, ((long long)sum[x][0] * pre[j] + (long long)sum[x][1] * pre[1 - j]) % MOD * tot % MOD);
		}
	}
	else
	{
		choose[x] = mask[j = (state[father[x]] ^ weight[x])] & can;
		DFS(x + 1, 1 - j, j, ((long long)sum[x][0] * pre[j] + (long long)sum[x][1] * pre[1 - j]) % MOD * tot % MOD);
	}
}

int main()
{
	int t, i, l, r, s;
	scanf("%d", &T);
	for(t = 1;t <= T;t += 1)
	{
		memset(father, ~0u, sizeof(father));
		memset(sol, 0, sizeof(sol));
		memset(weight, 0, sizeof(weight));
		memset(choose, 0, sizeof(choose));
		memset(state, 0, sizeof(state));
		memset(ans2, 0, sizeof(ans2));
		ans = exist = 0;
		flag = 1;
		scanf("%d %d", &N, &M);
		choose[0] = 1;
		for(i = 1;i <= N;i += 1)
		{
			scanf("%d %d", &lw[i], &hi[i]);
			sum[i][0] = (hi[i]>>1) - ((lw[i] - 1)>>1);
			sum[i][1] = ((hi[i] + 1)>>1) - (lw[i]>>1);
		}
		for(i = 1;i <= M;i += 1)
		{
			scanf("%d %d %d", &l, &r, &s);
			l -= 1;
			if(check(l, r, s))
				Union(l, r, s);
			else
				flag = 0;
		}
		for(i = 1;i <= N;i += 1)
			find(i);
		if(flag)
			DFS(1, 1, 0, 1);
		flag = flag && exist;
		printf("%d\n", ans);
		if(flag)
		{
			for(i = 1;i <= N;i += 1)
				printf("%d%c", ans2[i], i == N?'\n':' ');
		}
		else
			printf("-1\n");
	}
	exit(0);
}
