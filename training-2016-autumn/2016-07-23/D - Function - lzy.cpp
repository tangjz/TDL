#include <cstdio>
#include <cstring>
#include <algorithm>

int T, n, m, a, b, c, d, r;
double ff[209][109], (*f)[109] = ff + 105;
bool uu[209][109], (*u)[109] = uu + 105;
bool inn[209][109], (*in)[109] = inn + 105;
bool flag;

double fun(int n, int m);

inline
double f1(int n, int m) {
	double t = (double) n / m;
	n = -m - 2 * n;
	return (a + (b + r * t * t) * fun(n, m)) / r;
}

inline
double f2(int n, int m) {
	double t = (double) n / m;
	n = +m - 2 * n;
	return (c + (d + r * t * t) * fun(n, m)) / r;
}

double fun(int n, int m) {
	int g = std::__gcd(n, m);
	n /= g, m /= g;
	if (m < 0) n = -n, m = -m;
	if (u[n][m]) return f[n][m];
	if (flag && in[n][m]) {
		flag = false;
		double A, B;
		u[n][m] = true;
		f[n][m] = 0.;
		B = n <= 0? f1(n, m) : f2(n, m);
		f[n][m] = 1.;
		A = (n <= 0? f1(n, m) : f2(n, m)) - B;
		return f[n][m] = B / (1 - A);
	}
	in[n][m] = true;
	return n <= 0? f1(n, m) : f2(n, m);
	in[n][m] = false;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d%d%d%d%d", &n, &m, &a, &b, &c, &d, &r);
		memset(uu, 0, sizeof uu);
		memset(inn, 0, sizeof inn);
		flag = true;
		printf("%.10f\n", fun(n, m));
	}
	return 0;
}
