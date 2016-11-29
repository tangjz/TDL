#include <cstdio>
#include <cstdlib>
using namespace std;
int n,m,sum0,sum2,x,A,B;

int main(){
	int T;
	scanf("%d",&T);
	while(T --){
		scanf("%d%d",&n,&m);
		sum0 = 0; sum2 = 0;
		for(int i = 0;i < n - 1;++ i){
			scanf("%d",&x);
			sum0 += x;
		}
		for(int i = 0;i < m;++ i){
			scanf("%d",&x);
			sum2 += x;
		}
		A = sum2 / m + 1;
		B = sum0 / (n - 1) - (sum0 % (n - 1) == 0);
		printf("%d %d\n",A,B);
	}
	return 0;
}
