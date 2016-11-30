#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <algorithm>

using namespace std;

const int NMAX = 1100;

int N;
char S[NMAX];
bool diff[NMAX];

char re(char x)
{
	return x == '0'?'1':'0';
}

int main()
{
	int i, x;
	scanf("%d", &N);
	srand(time(0));
	while(1)
	{
		for(i = 0;i < N;i += 1)
			S[i] = (rand() & 1) + '0';
		printf("%s\n", S);
		fflush(stdout);
		scanf("%d", &x);
		if(!x)
			continue;
		if(x == N / 2)
			break;
		else
			exit(0);
	}
	S[0] = re(S[0]);
	for(i = 1;i < N;i += 1)
	{
		S[i] = re(S[i]);
		printf("%s\n", S);
		S[i] = re(S[i]);
		fflush(stdout);
		scanf("%d", &x);
		if(x == N / 2)
			diff[i] = true;
		else if(x == N)
			exit(0);
	}
	S[0] = re(S[0]);
	for(i = 0;i < N;i += 1)
	{
		if(diff[i])
			S[i] = re(S[i]);
	}
	printf("%s\n", S);
	fflush(stdout);
	scanf("%d", &x);
	if(!x)
	{
		for(i = 0;i < N;i += 1)
			S[i] = re(S[i]);
		printf("%s\n", S);
		fflush(stdout);
		scanf("%d", &x);
	}
	exit(0);
}
