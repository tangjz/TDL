#include <cstdio>

int T,n,x,y;

int sqr(int x)
{
	return x*x;
}
int main()
{
	scanf("%d",&T);
	while (T--)
	{
		int sum=0;
		scanf("%d",&n);
		while (n--)
		{
			scanf("%d%d",&x,&y);
			for (int r=20;r<=200;r+=20)
			{
				if (sqr(x)+sqr(y)<=sqr(r))
				{
					sum+=11-r/20;
					break;
				}
			}
		}
		printf("%d\n",sum);
	}
	return 0;
}
