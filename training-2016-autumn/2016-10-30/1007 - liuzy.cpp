#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>

using namespace std;

const double PI = 3.14159265358979;
const double eps = 1e-9;

int T;
double d, H = 2.0, V;

double sqr(double x) {
	return x * x;
}

double volume(double l)
{
	double x0 = 1. - l, theta = acos(x0), sinTheta = sqrt(1 - x0 * x0);
	return 2 * H / l * (pow(sinTheta, 3) / 3 - x0 * .5 * (theta - x0 * sinTheta));
}

double area(double l)
{
	double r = sqrt(sqr(l) + sqr(H));
	double b = r / l;
	double g = sqrt(1 - sqr(1 - l));
	double f = sqrt(sqr(g) + sqr(b - r));
	double alp = acos(abs(b - r) / f);
	double s;
	if (r + eps < b) {
		s = f * b * alp;
		s -= g * (b - r);
	} else {
		s = PI * b;
		s -= f * b * alp;
		s += g * (r - b);
	}
	return s;
}

int main()
{
	int i, t;
	double L, R, mid, V;
	scanf("%d", &T);
	for(t = 1;t <= T;t += 1)
	{
		scanf("%lf", &d);
		V = PI * d;//
		if(d + eps >= 1.0)
		{
			double x = 2 * d - 2;
			double rr = sqrt(4 + sqr(2 - x));
			double s = PI * .5 * rr;
			printf("%.5f\n", s);
		}
		else if(d < eps)
			printf("%.5f\n", 0.0);
		else
		{
			L = 0.0;
			R = 2.0;
			for(i = 1;i <= 60;i += 1)
			{
				mid = (L + R) * .5;
				if(volume(mid) < V)//precision
					L = mid;
				else
					R = mid;
			}
			printf("%.5f\n", area(L + eps));
		}
	}
	exit(0);
}
