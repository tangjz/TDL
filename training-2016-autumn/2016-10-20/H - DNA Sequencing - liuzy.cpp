#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int ALPHA = 26, LMAX = 600, NodeMAX = 350000;

struct Node
{
	int v;
	int next[ALPHA];
};

int N, M, tot;
int root, pid;
Node pool[NodeMAX];

int index(char x)
{
	return x - 'A';
}

void insert(char str[], int v)
{
	int i, pos = root;
	for(i = 0;str[i];i += 1)
	{
		if(!pool[pos].next[index(str[i])])
			pool[pos].next[index(str[i])] = ++pid;
		pos = pool[pos].next[index(str[i])];
	}
	pool[pos].v += v;
}

int DFS(int pos, int depth)
{
	int i, v = pool[pos].v;
	for(i = 0;i < ALPHA;i += 1)
	{
		if(pool[pos].next[i])
			v += DFS(pool[pos].next[i], depth + 1);
	}
	if(depth >= M && v)
		v -= 1;
	return v;
}

int main()
{
	int i, x;
	char str[LMAX];
	while(1)
	{
		pid = tot = 0;
		memset(pool, 0, sizeof(pool));
		scanf("%d %d", &N, &M);
		if(!N && !M)
			break;
		for(i = 1;i <= N;i += 1)
		{
			scanf("%d %s", &x, str);
			insert(str, x);
			tot += x;
		}
		printf("%d\n", tot - DFS(root, 0));
	}
	exit(0);
}
