#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <queue>

using namespace std;

const int NMAX = 110000;

int N;
long long M;
int h[NMAX];
long long costL[NMAX], costR[NMAX];
deque<int> Q;

void solve(int H, long long cost[])
{
	int i, x, l;
	long long res = 0;
	memset(cost, 0, NMAX * sizeof(long long));
	Q.clear();
	for(i = l = 1;i <= N;i += 1)
	{
		while(!Q.empty())
		{
			x = Q.front();
			if(H - i > h[x] - x)
				break;
			for(;l <= x;l += 1)
				res -= h[l] - l;
			Q.pop_front();
		}
		cost[i] = (long long)(H - i) * (i - l) - res;
		if(l == 1 && H - i > h[1] - 1)
			cost[i] = M + 1;
		while(!Q.empty())
		{
			x = Q.back();
			if(h[x] - x > h[i] - i)
				break;
			Q.pop_back();
		}
		Q.push_back(i);
		res += h[i] - i;
	}
}

bool check(int H)
{
	int i;
	long long res = M + 1;
	reverse(h + 1, h + N + 1);
	solve(H, costR);
	reverse(h + 1, h + N + 1);
	solve(H, costL);
	for(i = 1;i <= N;i += 1)
	{
		if(H <= h[i])
			res = 0;
		else
			res = min(res, costL[i] + costR[N + 1 - i] + H - h[i]);
	}
	return res <= M;
}

int main()
{
	int i, L, R, mid;
	freopen("landscape.in", "r", stdin);
	freopen("landscape.out", "w", stdout);
	scanf("%d %I64d", &N, &M);
	for(i = 1;i <= N;i += 1)
		scanf("%d", &h[i]);
	for(L = 1, R = 101000000;L + 1 < R;)//[)
	{
		mid = (L + R)>>1;
		if(check(mid))
			L = mid;
		else
			R = mid;
	}
	printf("%d\n", L);
	exit(0);
}
