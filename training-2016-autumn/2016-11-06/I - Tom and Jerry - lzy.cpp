#include <cstdio>
#include <cmath>

const double pi = acos(-1.);

int r, v;

int main() {
	int TT;
	scanf("%d", &TT);
	for (int T = 1; T <= TT; ++T) {
		scanf("%d%d", &r, &v);
		printf("Case %d: %.8f\n", T, .5 * r / v * pi);
	}
	return 0;
}
