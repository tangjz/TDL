#include <cstdio>
#include <cstring>

#define D 59
#define N 2509

const int dx[]={-1,0,+1,0};
const int dy[]={0,-1,0,+1};

int R,C,n,m,max_mat,e[N],d[N];
int idx[D][D],mat[N],l[N][4],r[N][4];
bool use[N];

bool aug(int i)
{
	if (i==0) return true;
	for (int j=0;j<e[i];++j) if (!use[l[i][j]])
	{
		use[l[i][j]]=true;
		if (aug(mat[l[i][j]])) return (mat[l[i][j]]=i);
	}
	return false;
}
int match(int banx,int bany)
{
	int cnt=0;
	memset(mat,0,sizeof(mat));
	for (int i=1;i<=n;++i)
	{
		if (i==banx) continue;
		memset(use,0,sizeof(use));
		use[bany]=true;
		if (aug(i)) ++cnt;
	}
	return cnt;
}
int main()
{
	while (scanf("%d%d",&R,&C)==2)
	{
		n=m=0;
		memset(idx,0,sizeof(idx));
		memset(e,0,sizeof(e));
		memset(d,0,sizeof(d));
		for (int i=1;i<=R;++i)
		{
			getchar();
			for (int j=1;j<=C;++j)
			{
				if (getchar()=='.')
				{
					if ((i+j)&1) idx[i][j]=++n;
					else idx[i][j]=++m;
				}
			}
		}
		for (int i=1;i<=R;++i) for (int j=1;j<=C;++j) if (idx[i][j])
		{
			if ((i+j)&1)
			{
				int u=idx[i][j];
				for (int k=0;k<4;++k) if (idx[i+dx[k]][j+dy[k]])
				{
					l[u][e[u]++]=idx[i+dx[k]][j+dy[k]];
				}
			}
			else
			{
				int v=idx[i][j];
				for (int k=0;k<4;++k) if (idx[i+dx[k]][j+dy[k]])
				{
					r[v][d[v]++]=idx[i+dx[k]][j+dy[k]];
				}
			}
		}
		if (n!=m) goto P1;
		max_mat=match(0,0);
		if (max_mat!=n) goto P1;
		puts("2");
		continue;
		P1:puts("1");
	}
	return 0;
}
