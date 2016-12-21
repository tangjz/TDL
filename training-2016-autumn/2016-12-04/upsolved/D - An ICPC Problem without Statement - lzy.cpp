#include <cstdio>
#include <vector>
#include <algorithm>

#define N 100000

using std::vector;

unsigned n, a, b;
int x[N + 9];
vector<int> cc[5], *c = cc + 2;
vector<int> d;

int main() {
	int TT;
	scanf("%d", &TT);
	for (int T = 1; T <= TT; ++T) {
		scanf("%u%u%u", &n, &a, &b);
		for (int i = -2; i <= +2; ++i) c[i].clear();
		
		for (auto i = 1u; i <= n; ++i) {
			scanf("%d", x + i);
			c[x[i]].push_back(i);
		}
		
		d.clear();
		while (d.size() + 2 <= b && c[-2].size() >= 2) {
			d.push_back(c[-2].back()), c[-2].pop_back();
			d.push_back(c[-2].back()), c[-2].pop_back();
		}
		while (d.size() + 1 <= b && c[+2].size() >= 1) {
			d.push_back(c[+2].back()), c[+2].pop_back();
		}
		if (d.size() + 2 <= b && c[-2].size() >= 1 && c[-1].size() >= 1) {
			d.push_back(c[-2].back()), c[-2].pop_back();
			d.push_back(c[-1].back()), c[-1].pop_back();
		}
		while (d.size() + 2 <= b && c[-1].size() >= 2) {
			d.push_back(c[-1].back()), c[-1].pop_back();
			d.push_back(c[-1].back()), c[-1].pop_back();
		}
		while (d.size() + 1 <= a && c[+1].size() >= 1) {
			d.push_back(c[+1].back()), c[+1].pop_back();
		}
		vector<int>::iterator it;
		if (d.size() >= a) goto THERE;
		for (it = d.begin(); it != d.end(); ++it)
			if (x[*it] == +2) break;
		if (it != d.end()) {
			c[+2].push_back(*it);
			d.erase(it);
			if (d.size() + 2 <= b && c[-2].size() >= 1 && c[-1].size() >= 1) {
				d.push_back(c[-2].back()), c[-2].pop_back();
				d.push_back(c[-1].back()), c[-1].pop_back();
			}
			while (d.size() + 2 <= b && c[-1].size() >= 2) {
				d.push_back(c[-1].back()), c[-1].pop_back();
				d.push_back(c[-1].back()), c[-1].pop_back();
			}
			while (d.size() + 1 <= a && c[+1].size() >= 1) {
				d.push_back(c[+1].back()), c[+1].pop_back();
			}
		}
		if (d.size() >= a) goto THERE;
		if (c[0].size()) {
			for (int i = 0; i <= 2; ++i) {
				while (d.size() + 1 <= a && c[+i].size() >= 1) {
					d.push_back(c[+i].back()), c[+i].pop_back();
				}
				while (d.size() + 1 <= a && c[-i].size() >= 1) {
					d.push_back(c[-i].back()), c[-i].pop_back();
				}
			}
		} else {
			while (!d.empty()) {
				c[x[d.back()]].push_back(d.back());
				d.pop_back();
			}
			for (int i = 1; i <= 2; ++i) {
				while (d.size() + 1 <= a && c[+i].size() >= 1) {
					d.push_back(c[+i].back()), c[+i].pop_back();
				}
				while (d.size() + 1 <= a && c[-i].size() >= 1) {
					d.push_back(c[-i].back()), c[-i].pop_back();
				}
			}
		}
		THERE:
		std::sort(d.begin(), d.end());
		printf("Case #%d:\n", T);
		printf("%lu\n", d.size());
		//int m = 0, z = 1;
		for (auto i = 0u; i < d.size(); ++i) {
			//~ m += x[d[i]] == +2 || x[d[i]] == -2;
			//~ if (x[d[i]] == 0) z = 0;
			//~ if (x[d[i]] < 0) z *= -1;
			printf("%d%c", d[i], " \n"[i + 1 == d.size()]);
		}
		//~ if (z == 0) puts("SHIT");
		//~ else if (z < 0) printf("-%d\n", m);
		//~ else printf("+%d\n", m);
			
	}
	return 0;
}
