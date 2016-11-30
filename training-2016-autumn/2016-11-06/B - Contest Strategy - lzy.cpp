#include <cstdio>
#include <algorithm>

#define N 20

using std::sort;

int n, l, a[N + 9];

int main() {
	int TTT;
	scanf("%d", &TTT);
	for (int T = 1; T <= TTT; ++T) {
		scanf("%d%d", &n, &l);
		int m = 0, s = 0, t = 0;
		for (int i = 0; i < n; ++i)
			scanf("%d", a + i);
		sort(a, a + n);
		for (int i = 0; i < n; ++i) {
			if (s + a[i] > l) break;
			++m;
			s += a[i];
			t += s;
		}
		printf("Case %d: %d %d %d\n", T, m, s, t);
	}
	return 0;
}
