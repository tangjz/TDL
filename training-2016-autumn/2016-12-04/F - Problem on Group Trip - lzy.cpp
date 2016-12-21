#include <cstdio>
#include <queue>
#include <vector>
#include <functional>

#define N 100
#define TIME 30000
using namespace std;

int n, s[N + 9][3], u[3];
priority_queue<int, vector<int>, greater<int>> que[3];

bool no() {
	for (int j = 0; j < 3; ++j) if (~u[j] || !que[j].empty()) return false;
	return true;
}

int main() {
	int TT;
	scanf("%d", &TT);
	for (int T = 1; T <= TT; ++T) {
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < 3; ++j)
				scanf("%d", s[i] + j);
			for (int j = 0; j < 3; ++j)
				if (s[i][j]) {
					que[j].push(i);
					break;
				}
		}
		for (int j = 0; j < 3; ++j) u[j] = -1;
		for (int t = 0; t <= TIME; ++t) {
			for (int j = 0; j < 3; ++j) {
				if (u[j] == -1) {
					if (!que[j].empty()) {
						u[j] = que[j].top();
						que[j].pop();
					}
					continue;
				}
				if (!--s[u[j]][j]) {
					int p = u[j];
					u[j] = -1;
					if (!que[j].empty()) {
						u[j] = que[j].top();
						que[j].pop();
					}
					for (int k = j + 1; k < 3; ++k)
						if (s[p][k]) {
							que[k].push(p);
							break;
						}
				}
			}
			if (no()) {
				printf("Case #%d: %d\n", T, t);
				break; 
			}
		 }
	}
	return 0;
}
