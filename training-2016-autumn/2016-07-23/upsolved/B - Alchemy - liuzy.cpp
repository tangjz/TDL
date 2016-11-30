#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 2010, EMAX = 4100000;

struct Edge
{
	int y;
	int next;
};

int T, N, ans;
int X[NMAX], Y[NMAX], R[NMAX], C[NMAX][2];
int maximum[NMAX], sum[NMAX], minCan[NMAX], pre[NMAX];
int eid, V[NMAX], indegree[NMAX], father[NMAX];
bool ban[NMAX], in[NMAX];
Edge E[EMAX];
int Q[NMAX], head, tail;

void insert(int x, int y)
{
	E[++eid] = (Edge){y, V[x]};
	V[x] = eid;
	indegree[y] += 1;
}

int dist2(int x, int y)
{
	return (X[x] - X[y]) * (X[x] - X[y]) + (Y[x] - Y[y]) * (Y[x] - Y[y]);
}

bool inside(int x, int y)
{
	return R[x] < R[y] && dist2(x, y) < R[y] * R[y];
}

void BFS(int x)
{
	int i;
	Q[tail++] = x;
	father[x] = pre[x] = 0;
	while(head < tail)
	{
		x = Q[head++];
		for(i = 1, minCan[x] = sum[x] = maximum[x] = 0;i <= pre[x];i += 1)
		{
			sum[x] += C[x][i & 1];
			if(maximum[x] < sum[x])
			{
				maximum[x] = sum[x];
				minCan[x] = i;
			}
		}
		ans += maximum[x];
		for(i = V[x];i;i = E[i].next)
		{
			indegree[E[i].y] -= 1;
			if(!indegree[E[i].y] && pre[E[i].y] < 0)
			{
				pre[E[i].y] = pre[x] + 1;
				father[E[i].y] = x;
				Q[tail++] = E[i].y;
			}
		}
	}
}

int main()
{
	int t, i, j, x;
	scanf("%d", &T);
	for(t = 1;t <= T;t += 1)
	{
		head = tail = ans = eid = 0;
		memset(V, 0, sizeof(V));
		memset(pre, ~0u, sizeof(pre));
		memset(in, 0, sizeof(in));
		scanf("%d", &N);
		for(i = 1;i <= N;i += 1)
		{
			scanf("%d %d %d %d %d", &X[i], &Y[i], &R[i], &C[i][1], &C[i][0]);
			for(j = 1;j < i;j += 1)
			{
				if(inside(i, j))
					insert(j, i);
				if(inside(j, i))
					insert(i, j);
			}
		}
		for(i = 1;i <= N;i += 1)
		{
			if(pre[i] < 0 && !indegree[i])
				BFS(i);
		}
		printf("%d\n", ans);
		for(i = 1;i <= N;i += 1)
		{
			memset(ban, 0, sizeof(ban));
			for(j = N - 1;j >= 0;j -= 1)
			{
				if(father[Q[j]] && ((!in[Q[j]] && pre[Q[j]] == minCan[Q[j]]) || ban[Q[j]]))
					ban[father[Q[j]]] = 1;
				if(sum[Q[j]] != maximum[Q[j]])
					ban[Q[j]] = 1;
			}
			for(x = 1;x <= N;x += 1)
			{
				if(!in[x] && !ban[x])
					break;
			}
			in[x] = true;
			for(j = V[x];j;j = E[j].next)
			{
				sum[E[j].y] -= C[E[j].y][pre[E[j].y] & 1];
				pre[E[j].y] -= 1;
			}
			printf("%d%c", x, " \n"[i == N?1:0]);
		}
	}
	exit(0);
}
