#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 1100;

struct Node
{
	int type;
	int x;
	int v;
};

int T, N, ans, top;
int tree[NMAX];
int matrix[NMAX][NMAX], one[4][NMAX][NMAX];
Node Q[3 * NMAX];

inline int lowbit(int x)
{
	return x & (-x);
}

void add(int x, int v)
{
	for(;x <= N;x += lowbit(x))
		tree[x] += v;
}

int query(int x)
{
	int res = 0;
	for(;x;x -= lowbit(x))
		res += tree[x];
	return res;
}

void findOne(int pos, int si, int ei, int di, int sj, int ej, int dj, int curi, int curj)
{
	int i, j;
	for(i = si;i != ei;i += di)
	{
		for(j = sj;j != ej;j += dj)
			one[pos][i][j] = matrix[i][j]?(one[pos][i + curi][j + curj] + 1):0; 
	}
}

void init()
{
	//up
	findOne(0, 1, N + 1, 1, 1, N + 1, 1, -1, 0);
	//down
	findOne(1, N, 0, -1, 1, N + 1, 1, 1, 0);
	//left
	findOne(2, 1, N + 1, 1, 1, N + 1, 1, 0, -1);
	//right
	findOne(3, 1, N + 1, 1, N, 0, -1, 0, 1);
}

bool cmp(const Node &x, const Node &y)
{
	if(x.x == y.x)
		return x.type < y.type;
	return x.x > y.x;
}

int main()
{
	int t, i, j, type, x, y, v;
	scanf("%d", &T);
	for(t = 1;t <= T;t += 1)
	{
		memset(matrix, 0, sizeof(matrix));
		memset(one, 0, sizeof(one));
		ans = 0;
		scanf("%d", &N);
		for(i = 1;i <= N;i += 1)
		{
			for(j = 1;j <= N;j += 1)
				scanf("%d", &matrix[i][j]);
		}
		init();
		for(i = -(N - 1);i <= N - 1;i += 1)//i = x - y
		{
			top = 0;
			for(y = 1;y <= N;y += 1)
			{
				x = i + y;
				if(x < 1 || x > N)
					continue;
				Q[top++] = (Node){1, x, x};
				Q[top++] = (Node){2, x - min(one[0][x][y], one[2][x][y]), x};
				Q[top++] = (Node){3, x, x + min(one[1][x][y], one[3][x][y]) - 1};
			}
			sort(Q, Q + top, cmp);
			for(j = 0;j < top;j += 1)
			{
				type = Q[j].type;
				x = Q[j].x;
				v = Q[j].v;
				if(type != 3)
					add(v, type == 1?1:-1);
				else
					ans += query(v);
			}
		}
		printf("Case %d: %d\n", t, ans);
	}
	exit(0);
}
