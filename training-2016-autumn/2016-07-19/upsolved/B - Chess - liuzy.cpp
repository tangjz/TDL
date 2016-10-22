#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int MMAX = 30, R = 20;

int T, N, M;
int SG[1<<R];

void init()
{
	int i, j, pre, use[MMAX];
	for(i = 0;i < (1<<R);i += 1)
	{
		memset(use, 0, sizeof(use));
		for(j = 0, pre = -1;j < R;j += 1)
		{
			if(i & (1<<j))
			{
				if(pre >= 0)
					use[SG[(i ^ (1<<j)) | (1<<pre)]] = 1;
			}
			else
				pre = j;
		}
		for(j = 0;j < R && use[j];j += 1);
		SG[i] = j;
	}
}

int main()
{
	int t, i, j, x, state, ans;
	init();
	scanf("%d", &T);
	for(t = 1;t <= T;t += 1)
	{
		ans = 0;
		scanf("%d", &N);
		for(i = 1;i <= N;i += 1)
		{
			state = 0;
			scanf("%d", &M);
			for(j = 1;j <= M;j += 1)
			{
				scanf("%d", &x);
				state |= 1<<(R - x);
			}
			ans ^= SG[state];
		}
		printf("%s\n", ans?"YES":"NO");
	}
		exit(0);
}
