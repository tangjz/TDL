#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
const int MAXL = 18,MAXN = 2008;
int x,y,tot,l,r,n,next[MAXN],beg[MAXN],pre[MAXN],mx,sum,sz[MAXN],ret;
char a[MAXL],b[MAXL],dic[MAXN][MAXL];
bool vis[MAXN];

int main(){
	while(scanf("%d",&n) != EOF){
		tot = 0;
		for(int i = 0;i < n;++ i){
			scanf("%s%s",a,b);
			x = y = -1;
			if(strcmp(a,b) == 0) continue;
			for(int j = 0;j < tot;++ j)
			if(strcmp(dic[j],a) == 0){
				x = j; break;
			}
			for(int j = 0;j < tot;++ j)
			if(strcmp(dic[j],b) == 0){
				y = j; break;
			}
			if(x < 0){
				strcpy(dic[tot],a);
				x = tot ++;
			}
			if(y < 0){
				strcpy(dic[tot],b);
				y = tot ++;
			}
			next[x] = y; pre[y] = x;
		}
		memset(vis,0,sizeof(vis));
		mx = 0; sum = 0;
		for(int i = 0;i < tot;++ i)
		if(!vis[i]){
			beg[sum] = i; sz[sum] = 1;
			vis[i] = true;	
			for(int j = next[i];j != i;j = next[j])
			if(!vis[j]){
				vis[j] = true,++ sz[sum];
			}
			if(sz[sum] > 1 && mx == 0) mx = 1;
			if(sz[sum] > 2) mx = 2;
			++ sum;
		}
		printf("%d\n",mx);
		if(mx == 0) continue;
		ret = 0;
		for(int i = 0;i < sum;++ i)
		if(sz[i] == 2)
			++ ret;
		else
			ret += (sz[i] - 1) >> 1;
		printf("%d\n",ret);
		for(int i = 0;i < sum;++ i){
			l = beg[i]; r = pre[l];
			if(sz[i] != 2 && sz[i] % 2 == 0) r = pre[r];
			int tim = sz[i] == 2 ? 1 : (sz[i] - 1) >> 1;
			for(int pr = 0;pr < tim;l = next[l],r = pre[r],++ pr)
				printf("%s %s\n",dic[l],dic[r]);
		}
		if(mx > 1){
			ret = 0;
			for(int i = 0;i < sum;++ i)
			if(sz[i] > 2)
				ret += sz[i] >> 1;
			printf("%d\n",ret);
			for(int i = 0;i < sum;++ i)
			if(sz[i] > 2){
				l = beg[i]; r = pre[l];
				if(sz[i] % 2) l = next[l];
				int tim = sz[i] >> 1;
				for(int pr = 0;pr < tim;l = next[l],r = pre[r],++ pr)
					printf("%s %s\n",dic[l],dic[r]);
			}
		}
 	}
	return 0;
}
