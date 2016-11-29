#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int MAXN = 100005,MAXE = 1000005;
int cur[2],f[2],nxt[MAXN],in[2][MAXN],ideg[MAXN],q[MAXN],ans0,ans1,pos[MAXN],topol[MAXN],cnt;
int n,m,x,y;
struct Edge{
	int y;
	Edge *next;
}pool[MAXE],*first[MAXN],*mem;
inline void addedge(int a,int b){
	mem->y = b; mem->next = first[a]; first[a] = mem ++;
}

int calc(int now,int id){
	int ret = 0;
	cur[0] = f[0]; cur[1] = f[1];
	if(in[id][cur[now]] != 0) return n + n;
	for(int i = 0;i < n - 1;++ i){
		for(Edge *j = first[cur[now]];j;j = j->next) -- in[id][j->y];
		if(nxt[cur[now]] == -1 || in[id][nxt[cur[now]]] > 0){
			cur[now] = nxt[cur[now]]; now ^= 1; ++ ret;
		}else{
			cur[now] = nxt[cur[now]];
		}
	}
	return ret;
}

int main(){
	int __;
	scanf("%d",&__);
	while(__ --){
		scanf("%d%d",&n,&m);
		mem = pool;
		for(int i = 0;i < n;++ i) scanf("%d",&pos[i]),first[i] = 0,ideg[i] = in[0][i] = in[1][i] = 0;
		for(int i = 0;i < m;++ i){
			scanf("%d%d",&x,&y);
			addedge(x - 1,y - 1);
			++ ideg[y - 1]; ++ in[0][y - 1]; ++ in[1][y - 1];
		}
		int head = 0,tail = 0,now;
		for(int i = 0;i < n;++ i)
		if(ideg[i] == 0)
			q[tail ++] = i;
		cnt = 0;
		while(head < tail){
			topol[cnt ++] = now = q[head ++];
			for(Edge *j = first[now];j;j = j->next){
				-- ideg[j->y];
				if(ideg[j->y] == 0) q[tail ++] = j->y;
			}
		}
		f[0] = f[1] = -1;
		for(int i,j = n - 1;j >= 0;-- j){
			i = topol[j];
			nxt[i] = f[pos[i] - 1];
			f[pos[i] - 1] = i;
		}
		ans0 = calc(0,0); ans1 = calc(1,1);
		printf("%d\n",ans0 < ans1 ? ans0 : ans1);
	}
	return 0;
}
