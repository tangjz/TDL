#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int NMAX = 1100000;

int T, N;
int head, price[NMAX], id[NMAX];
long long presum[NMAX], ans;

bool cmp(const int &x, const int &y)
{
	if(price[x] == price[y])
		return x > y;
	return price[x] > price[y];
}

int main()
{
	int t, i;
	scanf("%d", &T);
	for(t = 1;t <= T;t += 1)
	{
		scanf("%d", &N);
		for(i = 1;i <= N;i += 1)
		{
			scanf("%d", &price[i]);
			presum[i] = presum[i - 1] + price[i];
			id[i] = i;
		}
		sort(id + 1, id + N + 1, cmp);
		for(ans = head = 0, i = 1;i <= N;i += 1)
		{
			if(id[i] <= head)
				continue;
			ans += (long long)price[id[i]] * (id[i] - head - 1);
			ans -= presum[id[i] - 1] - presum[head];
			head = id[i];
		}
		printf("%lld\n", ans);
	}
	exit(0);
}
