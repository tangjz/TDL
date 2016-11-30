#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int LMAX = 50;

int T, L;
int signA, signB, signC;
char expr[LMAX], tmp[LMAX], A[LMAX], B[LMAX], C[LMAX];

int getNumber(char X[], int x)
{
	int i, ans = 0;
	for(i = 0;X[i];i += 1)
	{
		ans = ans * 10 + (X[i] != '?'?X[i] - '0':x);
		//printf("inter ans:%d\n", ans);
	}
	//printf("ans:%d\n", ans);
	//getchar();
	return ans;
}

bool check(int x, int y, int z, char opt)
{
	switch(opt)
	{
		case '+':
			//printf("%d + %d == %d %d\n", x, y, z, x + y == z);
			return x + y == z;
		case '-':
			return x - y == z;
		case '*':
			return (long long)x * y == z;
	}
	return false;
}

int main()
{
	int i, j, t, opt, last, x, y, z;
	int use[10];
	scanf("%d", &T);
	for(t = 1;t <= T;t += 1)
	{
		memset(use, 0, sizeof(use));
		scanf("%s", expr);
		L = strlen(expr);
		for(i = 0;i < L;i += 1)
		{
			if(expr[i] >= '0' && expr[i] <= '9')
				use[expr[i] - '0'] = 1;
		}
		for(opt = 1;opt < L && expr[opt] != '-' && expr[opt] != '+' && expr[opt] != '*';opt += 1);
		for(last = opt;last < L && expr[last] != '=';last += 1);
		signA = expr[0] == '-'?-1:1;
		signB = expr[opt + 1] == '-'?-1:1;
		signC = expr[last + 1] == '-'?-1:1;
		for(i = signA > 0?0:1, j = 0;i < opt;i += 1, j += 1)
			A[j] = expr[i];
		A[j] = 0;
		for(i = signB > 0?opt + 1:opt + 2, j = 0;i < last;i += 1, j += 1)
			B[j] = expr[i];
		B[j] = 0;
		for(i = signC > 0?last + 1:last + 2, j = 0;i < L;i += 1, j += 1)
			C[j] = expr[i];
		C[j] = 0;
		for(i = 0;i < 10;i += 1)
		{
			if(use[i])
				continue;
			x = getNumber(A, i);
			y = getNumber(B, i);
			z = getNumber(C, i);
			if((signA < 0 && !x) || (signB < 0 && !y) || (signC < 0 && !z))
				continue;
			sprintf(tmp, "%d%c%d=%d", signA * x, expr[opt], signB * y, signC * z);
			if(strlen(tmp) != L)
				continue;
			//printf("%d %d %d i:%d\n", signA * x, signB * y, signC * z, i);
			if(check(signA * x, signB * y, signC * z, expr[opt]))
			{
				printf("%d\n", i);
				break;
			}
		}
		if(i >= 10)
			printf("-1\n");
	}
	exit(0);
}
