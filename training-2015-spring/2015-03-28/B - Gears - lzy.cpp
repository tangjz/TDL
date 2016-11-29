#include <cstdio>

#define N 200009

int n,m,u,v,x,y,f[N];
int s[10 * N],p[10 * N],z[10 * N];

void join(int x,int y,int b)
{
	s[x] = y;
	p[x] = b;
	z[y] += z[x];
}
int find(int u)
{
	if (u==s[u]) return u;
	else
	{
		int su = find(s[u]);
		p[u] ^= p[s[u]];
		s[u] = su;
		return su;
	}
}
int main()
{
	while (scanf("%d%d",&n,&m)==2)
	{
		for (int i=1;i<=n;++i)
		{
			f[i] = i;
			s[f[i]] = f[i];
			p[f[i]] = 0;
			z[f[i]] = 1;
		}
		while (m--)
		{
			getchar();
			int chr = getchar();
			if (chr == 'L')
			{
				scanf("%d%d",&u,&v);
				u = f[u];
				v = f[v];
				x = find(u);
				y = find(v);
				if (x != y) join(x,y,p[u]^p[v]^1);
			}
			else if (chr == 'Q')
			{
				scanf("%d%d",&u,&v);
				u = f[u];
				v = f[v];
				
				x = find(u);
				y = find(v);
				//printf("%d %d\n",x,y);
				if (x == y) puts(p[u]^p[v]?"Different":"Same");
				else puts("Unknown");
			}
			else if (chr == 'D')
			{
				scanf("%d",&u);
				--z[find(f[u])];
				u = f[u] = ++n;
				s[u] = u;
				p[u] = 0;
				z[u] = 1;
			}
			else if (chr == 'S')
			{
				scanf("%d",&u);
				u = f[u];
				printf("%d\n",z[find(u)]);
			}
		}
	}
	return 0;
}
