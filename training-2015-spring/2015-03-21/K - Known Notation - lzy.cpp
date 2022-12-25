#include <cstdio>
#include <cstring>
#include <algorithm>

using std::swap;

int T,l,m,cnt,ans;
char s[1009];

bool find()
{
	for (char *t=s;*t;++t) if (*t=='*') return true;
	return false;
}
int main()
{
	scanf("%d%*c",&T);
	while (T--)
	{
		gets(s);
		l=strlen(s);
		ans=0;
		if (find()==false)
		{
			puts("0");
			continue;
		}
		if (s[l-1]!='*')
		{
			++ans;
			for (char *t=s;*t;++t) if (*t=='*')
			{
				swap(*t,s[l-1]);
				break;
			}
		}
		m=0;
		cnt=0;
		for (int i=0;i<l;++i) m+=s[i]=='*'?-1:1;
		if (m<=0)
		{
			ans+=-m+1;
			cnt=-m+1;
		}
		for (int i=0;i<l;++i)
		{
			cnt+=s[i]=='*'?-1:1;
			if (cnt<=0)
			{
				for (int j=l-1;j>i;--j) if (s[j]!='*')
				{
					++ans;
					swap(s[i],s[j]);
					cnt+=2;
					break;
				}
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
