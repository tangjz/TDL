#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

int N, M, K;

int main()
{
	int limit;
	while(1)
	{
		scanf("%d %d %d", &N, &M, &K);
		if(!N && !M && !K)
			break;
		limit = N / 2 + 1;
		if(N - K >= limit)
			printf("%d\n", max(0, limit - M));
		else
			printf("-1\n");
	}
	exit(0);
}
