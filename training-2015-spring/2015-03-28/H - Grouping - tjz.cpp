#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
const int maxn = 100010;
int n, m, tot, scc[maxn], sze[maxn], f[maxn];
vector<int> e[maxn], re[maxn], sta;
bool vis[maxn];
void dfs(int u)
{
	vis[u] = 1;
	for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
		if(!vis[*it])
			dfs(*it);
	sta.push_back(u);
}
void rdfs(int u)
{
	vis[u] = 1;
	scc[u] = tot;
	++sze[tot];
	for(vector<int>::iterator it = re[u].begin(); it != re[u].end(); ++it)
		if(!vis[*it])
			rdfs(*it);
		else
			f[tot] = max(f[tot], f[scc[*it]]);
}
int main()
{
	while(scanf("%d%d", &n, &m) == 2)
	{
		tot = 0;
		memset(scc, 0, sizeof scc);
		memset(sze, 0, sizeof sze);
		sta.clear();
		for(int i = 1; i <= n; ++i)
		{
			e[i].clear();
			re[i].clear();
		}
		for(int i = 1; i <= m; ++i)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			e[u].push_back(v);
			re[v].push_back(u);
		}
		memset(vis, 0, sizeof vis);
		for(int i = 1; i <= n; ++i)
			if(!vis[i])
				dfs(i);
		memset(f, 0, sizeof f);
		//for(int i = 0; i < (int)sta.size(); ++i)
		//	printf("%d\n", sta[i]);
		memset(vis, 0, sizeof vis);
		for(int i = sta.size() - 1; i >= 0; --i)
			if(!vis[sta[i]])
			{
				//printf("%d\n", sta[i]);
				++tot;
				rdfs(sta[i]);
				f[tot] += sze[tot];
			}
		//for(int i = 1; i <= n; ++i)
		//	printf("%d %d\n", scc[i], f[scc[i]]);
		int ans = 0;
		for(int i = 1; i <= tot; ++i)
			if(ans < f[i])
				ans = f[i];
		printf("%d\n", ans);
	}
	return 0;
}
