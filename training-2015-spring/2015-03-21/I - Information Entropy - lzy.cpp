#include <cstdio>
#include <cmath>

int n,pint;
char str[10];
double p,ans;

int main()
{
	int T;
	scanf("%d",&T);
	while (T--)
	{
		ans=0.0;
		scanf("%d%s",&n,str);
		while (n--)
		{
			scanf("%d",&pint);
			if (pint)
			{
				p=pint/100.0;
				if (*str=='b') ans+=p*log2(p);
				else if (*str=='n') ans+=p*log(p);
				else ans+=p*log10(p);
			}
		}
		printf("%.8f\n",-ans);
	}
	return 0;
}
