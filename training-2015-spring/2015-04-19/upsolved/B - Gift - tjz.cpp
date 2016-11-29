#include <cstdio>
const int maxn = 101;
int t, n;
char str[maxn][maxn];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		for(int i = 0; i < 2 * n - 1; ++i)
		{
			char ch = i & 1 ? 'Z' : 'A' + (i >> 1);
			int L = i, R = 4 * n - 4 - i;
			for(int j = L; j <= R; ++j)
				str[L][j] = str[R][j] = ch;
			for(int j = L + 1; j < R; ++j)
				str[j][L] = str[j][R] = ch;
		}
		for(int i = 0; i < 4 * n - 3; ++i)
		{
			str[i][4 * n - 3] = '\0';
			puts(str[i]);
		}
	}
	return 0;
}
