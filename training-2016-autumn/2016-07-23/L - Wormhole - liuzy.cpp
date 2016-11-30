#include <map>
#include <cmath>
#include <cstdio>
#include <string>
#include <cstring>
using namespace std;
const int maxn = 65, maxs = 55;
map<string, int> Hash;
char name[maxn][maxs], str[maxs];
int t, n, m, tot, x[maxn], y[maxn], z[maxn];
double f[maxn][maxn];
int getID(char s[])
{
	if(Hash.count(s))
		return Hash[s];
	strcpy(name[tot], s);
	return Hash[s] = tot++;
}
long long sqr(int x)
{
	return (long long)x * x;
}
inline void upd(double &x, double y)
{
	if(x > y)
		x = y;
}
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		tot = 0;
		map<string, int>().swap(Hash);
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
		{
			scanf("%s%d%d%d", str, x + i, y + i, z + i);
			getID(str);
		}
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				f[i][j] = sqrt(sqr(x[i] - x[j]) + sqr(y[i] - y[j]) + sqr(z[i] - z[j]));
		scanf("%d", &m);
		while(m--)
		{
			int u, v;
			scanf("%s", str);
			u = getID(str);
			scanf("%s", str);
			v = getID(str);
			f[u][v] = 0;
		}
		for(int k = 0; k < n; ++k)
			for(int i = 0; i < n; ++i)
				for(int j = 0; j < n; ++j)
					upd(f[i][j], f[i][k] + f[k][j]);
		printf("Case %d:\n", Case);
		scanf("%d", &m);
		while(m--)
		{
			int u, v;
			scanf("%s", str);
			u = getID(str);
			scanf("%s", str);
			v = getID(str);
			printf("The distance from %s to %s is %.0f parsecs.\n", name[u], name[v], f[u][v]);
		}
	}
	return 0;
}
