#include <cstdio>

const int mod = 1000000009;

int n,k,m,s,d,a,b;
char s1[109],s2[109];
long long c[109][109];
long long f[109][109];

int main()
{
	c[0][0] = 1;
	for (int i=1;i<109;++i)
	{
		c[i][0] = 1;
		for (int j=1;j<109;++j) c[i][j] = (c[i-1][j-1]+c[i-1][j])%mod;
	}
	while (scanf("%d%d%d",&n,&k,&m)==3)
	{
		getchar();
		gets(s1);
		gets(s2);
		s = 0;
		for (int i=0;i<n;++i) s+=(s1[i]!=s2[i]);
		for (int i=0;i<=n;++i) f[0][i] = 0;
		f[0][s] = 1;
		for (int i=1;i<=k;++i)
		{
			for (int j=0;j<=n;++j)
			{
				f[i][j] = 0;
				for (int l=0;l<=n;++l)
				{
					d = j-l;	
					if ((m-d)&1) continue;
					a = (m-d)/2;
					b = (m+d)/2;
					if (a<0 || b<0) continue;
					if (a>l || b>n-l) continue;
					f[i][j] += f[i-1][l]*(c[l][a]*c[n-l][b] % mod) %mod;
				}
				f[i][j]%=mod;
			}
		}
		printf("%lld\n",f[k][0]);
	}
	return 0;
}
