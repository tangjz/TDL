#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int NMAX = 110000;

int T, N, G, L, E, C;
int g[NMAX], l[NMAX], P[NMAX];
char str[NMAX];

void calcNext()
{
	int i, j;
	for(i = 2, j = 0;i <= N;i += 1)
	{
		g[i] = g[i - 1];
		l[i] = l[i - 1];
		while(j && str[j + 1] != str[i])
		{
			if(str[j + 1] > str[i])
				l[i] += 1;
			else
				g[i] += 1;
			g[i] += g[j];
			l[i] += l[j];
			j = P[j];
		}
		if(str[j + 1] == str[i])
			j += 1;
		else
		{
			if(str[j + 1] > str[i])
				l[i] += 1;
			else
				g[i] += 1;
		}
		P[i] = j;
	}
	if(!(N % (N - P[N])))
		C = N / (N - P[N]);
	else
		C = 1;
}

int main()
{
	int t, i, j, pos;
	scanf("%d", &T);
	for(t = 1;t <= T;t += 1)
	{
		G = L = E = 0;
		scanf("%s", str + 1);
		N = strlen(str + 1);
		calcNext();
		for(i = 1, j = 0;i < 2 * N;i += 1)
		{
			pos = (i - 1) % N + 1;
			while(j && str[j + 1] != str[pos])
			{
				if(j < N)
				{
					if(str[j + 1] > str[pos])
						L += 1;
					else
						G += 1;
				}
				G += g[j];
				L += l[j];
				j = P[j];
			}
			if(str[j + 1] == str[pos])
				j += 1;
			else
			{
				if(str[j + 1] > str[pos])
					L += 1;
				else
					G += 1;
			}
			if(j == N)
				E += 1;
		}
		printf("Case %d: %d %d %d\n", t, L / C, E / C, G / C);
	}
	exit(0);
}
