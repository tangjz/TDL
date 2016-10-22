#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int NMAX = 12, SMAX = 600;

int N, M, mask;
int ban[NMAX][NMAX], f[SMAX][SMAX][NMAX];

inline int id(int x)
{
	switch(x)
	{
		case 1:
			return 1;
		case 2:
			return 2;
		case 4:
			return 3;
		case 8:
			return 4;
		case 16:
			return 5;
		case 32:
			return 6;
		case 64:
			return 7;
		case 128:
			return 8;
		case 256:
			return 9;
	}
	return 0;
}

inline int lowbit(int x)
{
	return x & (-x);
}

inline int value(int x)
{
	return 1<<(x - 1);
}

int DFS(int X, int Y, int last)
{
	int i, j, x, y, res = 2 * N;
	if(X == mask)
		f[X][Y][last] = ban[1][last];
	if(f[X][Y][last] >= 0)
		return f[X][Y][last];
	if(!X)
	{
		for(j = 1;j <= N;j += 1)
			res = min(res, DFS(1, value(j), ban[1][j]?0:j) + ban[1][j]);
	}
	else
	{
		for(i = mask ^ X;i;i -= lowbit(i))
		{
			x = id(lowbit(i));
			for(j = mask ^ Y;j;j -= lowbit(j))
			{
				y = id(lowbit(j));
				res = min(res, DFS(X | value(x), Y | value(y), ban[x][y]?0:y) + ban[x][y] + ban[x][last]);
			}
		}
	}
	return f[X][Y][last] = res;
}

int main()
{
	int i, x, y;
	while(scanf("%d %d", &N, &M) != EOF)
	{
		memset(ban, 0, sizeof(ban));
		memset(f, ~0u, sizeof(f));
		mask = (1<<N) - 1;
		for(i = 1;i <= M;i += 1)
		{
			scanf("%d %d", &x, &y);
			ban[y][x] = 1;
		}
		printf("%d\n", DFS(0, 0, 0));
	}
	exit(0);
}
