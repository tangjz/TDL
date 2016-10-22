#include <stdio.h>
#include <algorithm>
using namespace std;
#define x first
#define y second
const int maxn = 10000;
int tot, a, b;
pair<int, int> p[maxn];
int main()
{
	p[tot++] = make_pair(0, 0);
	for(int i = 1; tot < maxn; ++i)
	{
		pair<int, int> tp = make_pair(i + 1 >> 1, -(i >> 1));
		for( ; tp.y < 0 && tot < maxn; ++tp.x, ++tp.y)
			p[tot++] = tp;
		if(tot == maxn)
			break;
		for( ; tp.y < tp.x && tot < maxn; ++tp.y)
			p[tot++] = tp;
		if(tot == maxn)
			break;
		for( ; tp.x > 0 && tot < maxn; --tp.x)
			p[tot++] = tp;
		if(tot == maxn)
			break;
		for( ; tp.y >= (i + 1 >> 1) && tot < maxn; --tp.x, --tp.y)
			p[tot++] = tp;
	}
	while(scanf("%d%d", &a, &b) == 2 && a + b)
	{
		--a, --b;
		pair<int, int> delta = make_pair(p[a].x - p[b].x, p[a].y - p[b].y);
		if(delta.x < 0)
		{
			delta.x = -delta.x;
			delta.y = -delta.y;
		}
		printf("%d\n", delta.x + abs(delta.y) - max(min(delta.x, delta.y), 0));
	}
	return 0;
}
