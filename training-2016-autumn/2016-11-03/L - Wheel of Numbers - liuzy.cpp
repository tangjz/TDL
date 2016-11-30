#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int NMAX = 200;

int T;
int N, M, ans, number[NMAX];
int X, Y;

int main()
{
	int t, i, j, x;
	scanf("%d", &T);
	for(t = 1;t <= T;t += 1)
	{
		ans = 0;
		scanf("%d %d", &N, &M);
		for(X = i = 0;i < M;i += 1)
		{
			scanf("%d", &x);
			X = X * 10 + x;
		}
		for(Y = i = 0;i < M;i += 1)
		{
			scanf("%d", &x);
			Y = Y * 10 + x;
		}
		for(i = 0;i < N;i += 1)
			scanf("%d", &number[i]);
		for(i = 0;i < N;i += 1)
		{
			for(x = j = 0;j < M;j += 1)
				x = x * 10 + number[(i + j) % N];
			if(X <= x && x <= Y)
				ans += 1;
		}
		printf("%d\n", ans);
	}
	exit(0);
}
