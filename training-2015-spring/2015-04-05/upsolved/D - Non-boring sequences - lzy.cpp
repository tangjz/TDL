#include <algorithm>
#include <cstdio>

#define N 200000

using namespace std;

typedef long long i64;
struct Seg{int l,r,m;} s[4*N+9];

int mark[4*N+9];
int T,n,a[N+9],b[N+9],x[N+9],p[N+9],cnt[N+9];

void con(int k,int l,int r)
{
	s[k].l=l,s[k].r=r,s[k].m=0;
	if (l==r) return;
	else
	{
		mark[k]=0;
		con(2*k+1,l,(l+r)/2);
		con(2*k+2,(l+r)/2+1,r);
	}
}
void add(int k,int l,int r,int d)
{
	if (l<=s[k].l && s[k].r<=r)
	{
		s[k].m+=d;
		mark[k]+=d;
	}
	else
	{
		if (mark[k])
		{
			s[2*k+1].m+=mark[k];
			s[2*k+2].m+=mark[k];
			mark[2*k+1]+=mark[k];
			mark[2*k+2]+=mark[k];
			mark[k]=0;
		}
		int m=(s[k].l+s[k].r)/2;
		if (l<=m) add(2*k+1,l,r,d);
		if (r>m) add(2*k+2,l,r,d);
		s[k].m=min(s[2*k+1].m,s[2*k+2].m);
	}
}
int get(int k,int l,int r)
{
	if (l<=s[k].l && s[k].r<=r)
	{
		return s[k].m;
	}
	else
	{
		if (mark[k])
		{
			s[2*k+1].m+=mark[k];
			s[2*k+2].m+=mark[k];
			mark[2*k+1]+=mark[k];
			mark[2*k+2]+=mark[k];
			mark[k]=0;
		}
		int ret=0X7FFFFFFF;
		int m=(s[k].l+s[k].r)/2;
		if (l<=m) ret=min(ret,get(2*k+1,l,r));
		if (r>m) ret=min(ret,get(2*k+2,l,r));
		return ret;
	}
}
int gin()
{
	int chr,ret=0;
	LOOP:
	{
		chr=getchar();
		if (chr==' ' || chr=='\n') return ret;
		else ret=ret*10+chr;
	}
	goto LOOP;
}
int main()
{
	scanf("%d",&T);
	while (T--)
	{
		scanf("%d%*c",&n);
		for (int i=1;i<=n;++i) b[i]=a[i]=gin();
		sort(b+1,b+n+1);
		int *c=unique(b+1,b+n+1);
		for (int i=1;i<=n;++i)
		{
			a[i]=lower_bound(b+1,c,a[i])-b;
			p[i]=n+1;
			cnt[i]=0;
		}
		x[n+1]=n+1;
		for (int i=n;i>=1;--i)
		{
			x[i]=p[a[i]];
			p[a[i]]=i;
		}
		
		con(0,1,n);
		
		for (int i=1;i<=n;++i)
		{
			if (++cnt[a[i]]==1) add(0,i,x[i]-1,1);
		}
		//printf("%d\n",get(0,1,n));
		if (!get(0,1,n)) goto NO;
		for (int i=2;i<=n;++i)
		{
			add(0,i-1,x[i-1]-1,-1);
			if (x[i-1]!=n+1) add(0,x[i-1],x[x[i-1]]-1,1);
			//printf("%d\n",get(0,i,n));
			if (!get(0,i,n)) goto NO;
		}
		puts("non-boring");
		continue;
		NO:puts("boring");
	}
	return 0;
}
