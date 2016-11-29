#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXN = 100005;
int n,k,val[MAXN],ord[MAXN],tot,a[MAXN],next[MAXN],first[MAXN],now[MAXN],ret;

inline bool cmp(const int &x,const int &y){
	return val[x] < val[y];
}

int main(){
	while(scanf("%d%d",&n,&k) != EOF){
		for(int i = 0;i < n;++ i){
			ord[i] = i; scanf("%d",&val[i]);
		}
		sort(ord,ord + n,cmp);
		tot = 1; a[ord[0]] = 0;
		for(int i = 1;i < n;++ i)
		if(val[ord[i]] != val[ord[i - 1]])
			a[ord[i]] = tot ++;
		else
			a[ord[i]] = tot - 1;
		for(int i = 0;i < tot;++ i) first[i] = -1;
		for(int i = n - 1;i >= 0;-- i)
		if(first[a[i]] == -1){
			next[i] = -1; first[a[i]] = i; now[i] = 1;
		}else{
			next[i] = first[a[i]]; now[i] = now[next[i]] + 1; first[a[i]] = i;
		}
		ret = 0;
		for(int i = 0;i < tot;++ i){
			for(int l = first[i],r = first[i];r < n && r != -1;r = next[r]){
				while(r - l - now[l] + now[r] > k) l = next[l];
				if(now[l] - now[r] + 1 > ret) ret = now[l] - now[r] + 1;
			}
		}
		printf("%d\n",ret);
	}
	return 0;
}
