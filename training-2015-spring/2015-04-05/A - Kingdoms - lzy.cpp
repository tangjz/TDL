#include <cstdio>
#include <cstring>
#include <bitset>
using std::bitset;

int T,n,g[29][29],s[29];
int m,ans[29];
bitset<20> sta;
bool f[1048576];
bool a[29];

void dfs(int k)
{
	int t=sta.to_ulong();
	if (f[t]) return;
	else f[t]=true;
	if (k==n)
	{
		for (int i=0;i<n;++i) if (sta.test(i))
		{
			a[i]=true;
			break;
		}
	}
	else
	{
		for (int i=0;i<n;++i) if (sta.test(i) && s[i]>0)
		{
			sta.reset(i);
			for (int j=0;j<n;++j) s[j]-=g[j][i];
			dfs(k+1);
			sta.set(i);
			for (int j=0;j<n;++j) s[j]+=g[j][i];
		}
	}
}

int main()
{
	scanf("%d",&T);
	while (T--)
	{
		scanf("%d",&n);
		memset(f,0,sizeof(f));
		memset(s,0,sizeof(s));
		memset(a,0,sizeof(a));
		for (int i=0;i<n;++i) for (int j=0;j<n;++j)
		{
			scanf("%d",g[i]+j);
			s[i]+=g[i][j];
		}
		sta.set();
		dfs(1);
		m=0;
		for (int i=0;i<n;++i) if (a[i]) ans[m++]=i+1;
		if (m)
		{
			printf("%d",ans[0]);
			for (int i=1;i<m;++i) printf(" %d",ans[i]);
			putchar('\n');
		}
		else
		{
			puts("0");
		}
	}
	return 0;
}
