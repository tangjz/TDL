#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>
#include <deque>

using namespace std;

const int NMAX = 110000, VMAX = 110000, EMAX = 210000, LMAX = 20, MOD = 116323399;

struct Edge
{
	int y;
	int next;
};

int N;
int A[NMAX], B[NMAX];

class Graph
{
public:
	int pos, eid;
	int indegree[VMAX], V[VMAX], value[VMAX];
	Edge E[EMAX];
	pair<pair<int, int>, int> root;
	unordered_map<string, int> table;
	unordered_map<int, string> revTable;
	deque<int> Q;
	void init()
	{
		pos = eid = 0;
		memset(V, 0, sizeof(V));
		memset(E, 0, sizeof(E));
		memset(indegree, 0, sizeof(indegree));
		memset(value, 0, sizeof(value));
		table.clear();
		revTable.clear();
		root = make_pair(make_pair(0, 0), 0);
	}
	int id(char x[])
	{
		if(table.find(x) == table.end())
		{
			table[x] = ++pos;
			revTable[pos] = x;
		}
		return table[x];
	}
	void insert(char x[], char y[])
	{
		E[++eid] = (Edge){id(y), V[id(x)]};
		V[id(x)] = eid;
		indegree[id(y)] += 1;
	}
	void solve()
	{
		int i, x, y;
		for(i = 1;i <= pos;i += 1)
		{
			if(indegree[i] <= 1)
			{
				Q.push_back(i);
				indegree[i] = -1;
			}
		}
		while(!Q.empty())
		{
			x = Q.front();
			Q.pop_front();
			value[x] = ((long long)value[x] * A[-indegree[x]] + B[-indegree[x]]) % MOD;
			root = min(root, make_pair(make_pair(indegree[x], value[x]), x));
			for(i = V[x];i;i = E[i].next)
			{
				y = E[i].y;
				if(indegree[y] < 0)
					continue;
				indegree[y] -= 1;
				value[y] = ((long long)value[y] + value[x]) % MOD;
				if(indegree[y] <= 1)
				{
					Q.push_back(y);
					indegree[y] = indegree[x] - 1;
				}
			}
		}
	}
};

Graph X, Y;
vector<pair<int, int> > sonX[VMAX], sonY[VMAX];

void genSol(int x, int y, int prex, int prey)
{
	int i;
	printf("%s %s\n", X.revTable[x].c_str(), Y.revTable[y].c_str());
	sonX[x].clear();
	sonY[y].clear();
	for(i = X.V[x];i;i = X.E[i].next)
	{
		if(X.E[i].y == prex)
			continue;
		sonX[x].push_back(make_pair(X.value[X.E[i].y], X.E[i].y));
	}
	sort(sonX[x].begin(), sonX[x].end());
	for(i = Y.V[y];i;i = Y.E[i].next)
	{
		if(Y.E[i].y == prey)
			continue;
		sonY[y].push_back(make_pair(Y.value[Y.E[i].y], Y.E[i].y));
	}
	sort(sonY[y].begin(), sonY[y].end());
	for(i = 0;i < sonX[x].size();i += 1)
		genSol(sonX[x][i].second, sonY[y][i].second, x, y);
}

int main()
{
	int i;
	char u[LMAX], v[LMAX];
	srand(time(0));
	for(i = 1;i <= 100000;i += 1)
	{
		A[i] = rand();
		B[i] = rand();
	}
	while(scanf("%d", &N) != EOF)
	{
		X.init();
		Y.init();
		for(i = 1;i < N;i += 1)
		{
			scanf("%s %s", u, v);
			X.insert(u, v);
			X.insert(v, u);
		}
		X.solve();
		for(i = 1;i < N;i += 1)
		{
			scanf("%s %s", u, v);
			Y.insert(u, v);
			Y.insert(v, u);
		}
		Y.solve();
		genSol(X.root.second, Y.root.second, -1, -1);
	}
	exit(0);
}
