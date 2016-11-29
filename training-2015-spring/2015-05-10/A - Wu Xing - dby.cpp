#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
const int rel[5][5] = {
	{-1,-1,-1,1,0},
	{0,-1,-1,-1,1},
	{1,0,-1,-1,-1},
	{-1,1,0,-1,-1},
	{-1,-1,1,0,-1}
};
char a[30],b[30];
int l,r;

int gettp(char *s){
	if(s[0] == 'e') return 0;
	if(s[0] == 'f') return 1;
	if(s[0] == 'w' && s[1] == 'o') return 2;
	if(s[0] == 'w' && s[1] == 'a') return 3;
	return 4;
}

int main(){
	int T;
	scanf("%d",&T);
	while(T --){
		scanf("%s%s",a,b);
		l = gettp(a); r = gettp(b);
		if(rel[l][r] == 0){
			a[0] = a[0] - 'a' + 'A';
			printf("%s generates %s.\n",a,b);
		}else if(rel[l][r] == 1){
			a[0] = a[0] - 'a' + 'A';
			printf("%s overcomes %s.\n",a,b);
		}else if(rel[r][l] == 0){
			b[0] = b[0] - 'a' + 'A';
			printf("%s generates %s.\n",b,a);
		}else if(rel[r][l] == 1){
			b[0] = b[0] - 'a' + 'A';
			printf("%s overcomes %s.\n",b,a);
		}
	}
	return 0;
}
