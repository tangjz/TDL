#include <cmath>
#include <cstdio>

#include <algorithm>

using namespace std;

#define N 2000


const double inf = 1e36;

int n, m, u, v, w, x[N + 9], y[N + 9];
int S, T, num;
double s[N + 9], t[N + 9];
bool use[N + 9];

inline
double sqr(double x) {
	return x * x;
}

inline
double dist(int i, int j) {
	if (i <= n && j <= n) return sqrt(sqr(x[i] - x[j]) + sqr(y[i] - y[j]));
	else return abs(x[i] - x[j]);
}

void upd(double &a, double b) {
	if (a > b) a = b;
}

void prim(int S, double s[]) {
	for (int i = 0; i <= num; ++i) {
		s[i] = inf;
		use[i] = false;
	}
	s[S] = 0;
	for (int i = 1; i <= num; ++i) {
		int p = 0;
		for (int j = 1; j <= num; ++j)
			if (!use[j] && s[p] >= s[j]) p = j;
		use[p] = true;
		for (int j = 1; j <= num; ++j)
			if (!use[j]) upd(s[j], max(s[p], dist(p, j)));
	}
}

int main() {
	freopen("froggy.in", "r", stdin);
	freopen("froggy.out", "w", stdout);
	scanf("%d%d", &w, &n);
	for (int i = 1; i <= n; ++i)
		scanf("%d%d", x + i, y + i);
	num = n;
	S = ++num, T = ++num;
	x[S] = 0;
	x[T] = w;
	prim(S, s);
	prim(T, t);
	double ans = inf;
	//for (int i = 1; i <= num; ++i) printf("%f %f\n", s[i], t[i]);
	for (int i = 1; i <= num; ++i)
		for (int j = 1; j <= num; ++j)
			if (ans > max(dist(i, j) * .5, max(s[i], t[j]))) {
				ans = max(dist(i, j) * .5, max(s[i], t[j]));
				u = i, v = j;
			}
	if (u > n) y[u] = y[v];
	if (v > n) y[v] = y[u];
	printf("%.6f %.6f\n", (x[u] + x[v]) * .5, (y[u] + y[v]) * .5);
	return 0;
}
