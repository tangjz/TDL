#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 1005,MAXE = 200050,MAXQ = 1006,oo = ~0U>>2;
int q[MAXQ + 10],dis0[MAXN],dis1[MAXN],n,m,x,y,cost,C,ret,p,Q,val[MAXN];
bool v[MAXN],gas[MAXN];
struct Edge{
	int y,c;
	Edge *next;
}pool[MAXE],*f0[MAXN],*f1[MAXN],*mem;
inline void addedge(int a,int b,int c){
	mem->y = b; mem->c = c; mem->next = f0[a]; f0[a] = mem ++;
	mem->y = a; mem->c = c; mem->next = f1[b]; f1[b] = mem ++;
}

void SPFA0(){
	int head = 0,tail = 0,now,dest;
	for(int i = 0;i < n;++ i) dis0[i] = -oo,v[i] = false;
	q[tail ++] = 0; dis0[0] = C; v[0] = true;
	while(head != tail){
		now = q[head]; head = (head + 1) % MAXQ; v[now] = false;
		for(Edge *j = f0[now];j;j = j->next)
		if(j->c <= dis0[now]){
			dest = gas[j->y] ? C : dis0[now] - j->c;
			if(dest > dis0[j->y]){
				dis0[j->y] = dest;
				if(!v[j->y]){
					q[tail] = j->y; v[j->y] = true;
					tail = (tail + 1) % MAXQ;
				}
			}
		}
	}
}

void SPFA1(){
	int head = 0,tail = 0,now,dest;
	for(int i = 0;i < n;++ i) dis1[i] = oo,v[i] = false;
	q[tail ++] = n - 1; dis1[n - 1] = 0; v[n - 1] = true;
	while(head != tail){
		now = q[head]; head = (head + 1) % MAXQ; v[now] = false;
		for(Edge *j = f1[now];j;j = j->next)
		if(j->c + dis1[now] <= C){
			dest = gas[j->y] ? 0 : dis1[now] + j->c;
			if(dest < dis1[j->y]){
				dis1[j->y] = dest;
				if(!v[j->y]){
					q[tail] = j->y; v[j->y] = true;
					tail = (tail + 1) % MAXQ;
				}
			}
		}
	}
}	

int main(){
	while(scanf("%d%d%d",&n,&m,&C) != EOF){
		memset(f0,0,sizeof(f0));
		memset(f1,0,sizeof(f1));
		memset(val,0,sizeof(val));
		memset(gas,0,sizeof(gas));
		mem = pool;
		for(int i = 0;i < m;++ i){
			scanf("%d%d%d",&x,&y,&cost);
			addedge(x - 1,y - 1,cost);
		}
		scanf("%d",&p);
		for(int i = 0;i < p;++ i){
			scanf("%d",&x);
			gas[x - 1] = true;
		}
		scanf("%d",&Q);
		for(int i = 0;i < Q;++ i){
			scanf("%d",&x);
			scanf("%d",&val[x - 1]);
		}
		SPFA0();
		SPFA1();
		if(dis1[0] > C) puts("-1");
		else{
			ret = 0;
			for(int i = 0;i < n;++ i)
			if(val[i] && dis0[i] > dis1[i] && (dis0[i] - dis1[i]) * val[i] > ret)
					ret = (dis0[i] - dis1[i]) * val[i];
			printf("%d\n",ret);
		}
	}
	return 0;
}
