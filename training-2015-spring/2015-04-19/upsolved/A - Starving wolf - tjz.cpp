#include <cstdio>
const int maxn = 1000001;
int t, n, f[maxn];
int main()
{
	for(int i = 1; i < maxn; ++i)
	{
		for(int j = i; j < maxn; j += i)
			++f[j];
		f[i] += f[i - 1];
	}
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		printf("%d\n", f[n]);
	}
	return 0;
}
