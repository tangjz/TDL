#include <cstdio>
#include <cstdlib>

int a,h,m;
bool f[189];

int main()
{
	for (int i=1;i<=720;++i)
	{
		m+=6;
		if (i%12==0) h+=6;
		m%=360;
		h%=360;
		int b=abs(h-m);
		if (b>180) b=360-b;
		f[b]=true;
	}
	while (scanf("%d",&a)==1)
	{
		puts(f[a]?"Y":"N");
	}
	return 0;
}
