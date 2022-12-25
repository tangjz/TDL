#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <queue>
using namespace std;
typedef long long ll;
const ll oo = 1e17;
const int MAXN = 1030;
int n,k,x[MAXN],w[MAXN],q[MAXN],now,last,head,tail;
ll ws[MAXN],wx[MAXN],qx[MAXN],qy[MAXN],f[2][MAXN],tmp;

bool chk0(ll xx){
	return qy[head + 1] - qy[head] > (qx[head + 1] - qx[head]) * xx;
}

bool chk1(ll yy,ll xx){
	return (yy - qy[tail - 1]) * (qx[tail - 1] - qx[tail - 2]) > (qy[tail - 1] - qy[tail - 2]) * (xx - qx[tail - 1]);
}

int main(){
	while(scanf("%d%d",&n,&k) != EOF){
		for(int i = 0;i < n;++ i){
			scanf("%d%d",&x[i],&w[i]);
			ws[i] = i ? ws[i - 1] + (ll)w[i] : (ll)w[i];
			wx[i] = i ? wx[i - 1] + (ll)w[i] * (ll)x[i] : (ll)w[i] * (ll)x[i];
		}
		for(int i = 0;i < n;++ i)
			f[0][i] = ws[i] * x[i] - wx[i];
		now = 0; last = 1;
		for(int i = 2;i <= k;++ i){
			now ^= 1; last ^= 1;
			head = tail = 0;
			qy[tail] = f[last][i - 2] + wx[i - 2];
			qx[tail] = ws[i - 2];
			q[tail ++] = i - 2;
			for(int j = i - 1;j < n;++ j){
				while(head + 1 < tail && !chk0(x[j])) ++ head;
				tmp = q[head];
				f[now][j] = ws[j] * x[j] - wx[j] + f[last][tmp] + wx[tmp] - ws[tmp] * x[j];
				while(head + 1 < tail && !chk1(f[last][j] + wx[j],ws[j])) -- tail;
				qy[tail] = f[last][j] + wx[j]; qx[tail] = ws[j]; q[tail ++] = j;
			}
		}
		printf("%lld\n",f[now][n - 1]);
	}
	return 0;
}
