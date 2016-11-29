#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#define lowbit(x) (x & (-x))
using namespace std;
const int MAXN = 200005;
int n,val[MAXN],ord[MAXN],a[MAXN],first[MAXN],r[MAXN],l[MAXN],tot;
bool flag;

inline bool cmp(const int &a,const int &b){
	return val[a] < val[b];
}

bool boring(int L,int R){
	if(L >= R) return false;
	for(int i = L,j = R;i <= j;++ i,-- j){
		if(l[i] < L && r[i] > R) return boring(L,i - 1) || boring(i + 1,R);
		if(l[j] < L && r[j] > R) return boring(L,j - 1) || boring(j + 1,R);
	}
	return true;
}

int main(){
	int __;
	scanf("%d",&__);
	while(__ --){
		scanf("%d",&n);
		for(int i = 0;i < n;++ i){
			scanf("%d",&val[i]);
			ord[i] = i;
		}
		sort(ord,ord + n,cmp);
		a[ord[0]] = tot = 0; ++ tot;
		for(int i = 1;i < n;++ i)
		if(val[ord[i]] == val[ord[i - 1]])
			a[ord[i]] = tot - 1;
		else
			a[ord[i]] = tot ++;
		
		for(int i = 0;i < tot;++ i) first[i] = n + 1;
		for(int i = n - 1;i >= 0;-- i){
			r[i] = first[a[i]]; first[a[i]] = i;
		}
		for(int i = 0;i < tot;++ i) first[i] = -1;
		for(int i = 0;i < n;++ i){
			l[i] = first[a[i]]; first[a[i]] = i;
		}

		printf("%s\n",boring(0,n - 1) ? "boring" : "non-boring");
	}	
	return 0;
}
