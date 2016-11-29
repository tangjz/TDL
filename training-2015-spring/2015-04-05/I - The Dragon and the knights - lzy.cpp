#include <cstdio>
#include <bitset>
#include <set>
#include <string>
using namespace std;

#define N 109

int n,m,x,y,cnt;
int a[N],b[N],c[N];
bitset<128> t;
set<string> s;

int main()
{
	int T;
	scanf("%d",&T);
	while (T--)
	{
		scanf("%d%d",&n,&m);
		cnt=1;
		for (int i=0;i<n;++i)
		{
			scanf("%d%d%d",a+i,b+i,c+i);
			++cnt;
			for (int j=0;j<i;++j) cnt+=(long long)a[i]*b[j]!=(long long)b[i]*a[j];
		}
		s.clear();
		
		for (int i=0;i<m;++i)
		{
			scanf("%d%d",&x,&y);
			t.reset();
			for (int j=0;j<n;++j)
			{
				t[j]=(long long)a[j]*x+(long long)b[j]*y+c[j]<0;
			}
			s.insert(t.to_string());
		}
		//printf("%d %lu\n",cnt,s.size());
		puts((s.size()==cnt)?"PROTECTED":"VULNERABLE");
	}
	return 0;
}
