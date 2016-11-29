#include <algorithm>
#include <cstdio>
#include <cstring>
#include <set>
using namespace std;

#define N 200000

int T,n,m,ans,cnt,l,r,ord[N+9],x[N+9],y[N+9],c[N+9];
int X[N+9],s[N+9];
set<int> f[N+9];

bool cmp(int a,int b)
{
	return y[a]<y[b];
}
void add(int k,int d)
{
	for (int i=k;i<=cnt;i+=i&-i) s[i]+=d;
}
int get(int k)
{
	int sum=0;
	for (int i=k;i;i-=i&-i) sum+=s[i];
	return sum;
}
int main()
{
	scanf("%d",&T);
	while (T--)
	{
		scanf("%d%d",&n,&m);
		for (int i=0;i<n;++i)
		{
			ord[i]=i;
			scanf("%d%d%d",x+i,y+i,c+i);
			X[i]=x[i];
		}
		sort(X,X+n);
		cnt=unique(X,X+n)-X;
		for (int i=0;i<n;++i) x[i]=lower_bound(X,X+cnt,x[i])-X+1;
		for (int k=1;k<=m;++k)
		{
			f[k].clear();
			f[k].insert(0);
			f[k].insert(cnt+1);
		}
		ans=0;
		memset(s,0,sizeof(s));
		sort(ord,ord+n,cmp);
		y[ord[n]=n]=0X7FFFFFFF;
		for (int i=0;i<n;++i)
		{
			int j=ord[i];
			int k=c[j];
			if (f[k].find(x[j])==f[k].end())
			{
				set<int>::iterator p=f[k].upper_bound(x[j]);
				r=*p-1;
				l=*--p;
				ans=max(ans,get(r)-get(l));
			}
			if (y[ord[i]]!=y[ord[i+1]])
			{
				for (int j=i;j>=0 && y[ord[j]]==y[ord[i]];--j)
				{
					f[c[ord[j]]].insert(x[ord[j]]);
					add(x[ord[j]],1);
				}
			}
		}
		for (int k=1;k<=m;++k)
		{
			for (set<int>::iterator i=f[k].begin();;++i)
			{
				set<int>::iterator j=i;
				if (++j==f[k].end()) break;
				ans=max(ans,get(*j-1)-get(*i));
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
