#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

const int NMAX = 1001000;

int N, Q;
int R, C;
long long tot, RAns, CAns;
bool RUse[NMAX], CUse[NMAX];

int main()
{
	int i, x;
	char c;
	freopen("adjustment.in", "r", stdin);
	freopen("adjustment.out", "w", stdout);
	scanf("%d %d", &N, &Q);
	tot = (long long)(1 + N) * N / 2;
	for(i = 0;i < Q;i += 1)
	{
		scanf(" %c %d", &c, &x);
		if(c == 'R')
		{
			if(RUse[x])
				printf("0\n");
			else
			{
				printf("%I64d\n", (long long)(N - C) * x + tot - CAns);
				R += 1;
				RAns += x;
				RUse[x] = true;
			}
		}
		else
		{
			if(CUse[x])
				printf("0\n");
			else
			{
				printf("%I64d\n", (long long)(N - R) * x + tot - RAns);
				C += 1;
				CAns += x;
				CUse[x] = true;
			}
		}
	}
	exit(0);
}
