#include <cstdio>

#define N 200000

typedef long long i64;

int T,k,n,m,a,b;
bool s[N*2+9];

int pow(i64 a,int e,int m)
{
	i64 p=1;
	do
	{
		if (e&1) p=p*a%m;
		a=a*a%m;
	}
	while (e>>=1);
	return p;
}
int main()
{
	scanf("%d%*c",&T);
	while (T--)
	{
		n=0;
		for (int chr=getchar();chr!='\n';chr=getchar()) s[++n]=chr=='1';
		
		s[0]=s[n+1]=0;
		for (int i=n+2;i<=2*n+1;++i) s[i]=s[2*n+2-i];
		m=2*n+2;
		k=pow(2,n,m);
		for (int i=1;i<=n;++i)
		{
			a=s[(i+k)%m];
			b=s[(i-k+m)%m];
			if (a^b) goto NO;
		}
		puts("DIES");
		continue;
		NO:puts("LIVES");
	}
	return 0;
}
