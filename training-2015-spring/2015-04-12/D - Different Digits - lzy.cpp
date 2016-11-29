#include <cstdio>

int n,m,ans;
bool f[10];

int main()
{
	while (scanf("%d%d",&n,&m)==2)
	{
		ans=0;
		for (int i=n;i<=m;++i)
		{
			int num=i;
			for (int j=0;j<10;++j) f[j]=false;
			do
			{
				if (f[num%10]) goto NEXT;
				else f[num%10]=true;
			}
			while (num/=10);
			++ans;
			NEXT:;
		}
		printf("%d\n",ans);
	}
	return 0;
}
