#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int LMAX = 12;

int N;

bool digit(char x)
{
	return '1' <= x && x <= '9';
}

bool capital(char x)
{
	return 'A' <= x && x <= 'Z';
}

int main()
{
	int i;
	char id[LMAX];
	bool flag;
	while(scanf("%d", &N) != EOF)
	{
		for(i = 1;i <= N;i += 1)
		{
			flag = true;
			scanf("%s", id + 1);
			if(id[1] != id[2] || !digit(id[1]))
				flag = false;
			if(!digit(id[3]) || !digit(id[4]))
				flag = false;
			if(!capital(id[5]))
				flag = false;
			if(!digit(id[6]) || !digit(id[7]) || !digit(id[8]))
				flag = false;
			if(flag)
				printf("%s\n", id + 1);
		}
	}
	exit(0);
}
