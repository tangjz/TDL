#include <cmath>
#include <cstdio>

#include <algorithm>
#include <set>

using namespace std;

const double eps = 1e-9;
const double pi = acos(-1.);

int n, m;
double a, s[19], x[1009], y[1009];
set<int> use[19];

inline
int dcmp(double x) {
	return (x > +eps) - (x < -eps);
}

inline
double sqr(double x) {
	return x * x;
}

inline
double cube(double x) {
	return x * x * x;
}

inline
double sum(double alpha, double beta, int k) {
	if (k == -1) return sqr(a) * (cube(beta) - cube(alpha)) / 6;
	else if (k >= 0) return 2 * sqr(a) * sqr(pi) * (2 * k + 1) * (beta - alpha) +
				sqr(a) * pi * (sqr(beta) - sqr(alpha));
	return 0.;
}

int main() {
	int TT;
	scanf("%d", &TT);
	for (int T = 1; T <= TT; ++T) {
		scanf("%lf", &a);
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) {
			scanf("%lf", s + i);
			use[i].clear();
		}
		sort(s, s + n);
		scanf("%d", &m);
		for (int i = 0; i < m; ++i) scanf("%lf%lf", x + i, y + i);
		if (n == 0 && m) {
			printf("Spiral %d: -1\n", T);
			continue;
		}
		double ans = 0.;
		while (m--) {
			int k = (x[m] - a * y[m]) / (2 * a * pi);
			while (dcmp(a * (y[m] + 2 * k * pi) - x[m]) <= 0) ++k;
			--k;
			int i = upper_bound(s, s + n, y[m] + eps) - s;
			if (i == n) i = 0, ++k; 
			if (use[i].count(k)) continue;
			use[i].insert(k);
			if (i) {
				ans += sum(s[i - 1], s[i], k);
			} else {
				ans += sum(0, s[0], k) + sum(s[n - 1], 2 * pi, k - 1);
			}
			
		}
		printf("Spiral %d: %.4f liters\n", T, ans * .1);
	}
	return 0;
}
