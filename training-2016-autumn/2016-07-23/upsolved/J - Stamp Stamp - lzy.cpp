#include <cstdio>
#include <cstring>
#include <algorithm>

struct Point {
	int x,y;
	Point() {}
	Point(int x,int y): x(x),y(y) {}
	bool operator <(const Point &p) const {
		return x == p.x? y < p.y : x < p.x;
	}
	Point operator +(const Point &p) {
		return Point(x + p.x, y + p.y);
	}
	Point operator -(const Point &p) {
		return Point(x - p.x, y - p.y);
	}
	Point &operator +=(const Point &p) {
		 x += p.x, y += p.y;
		 return *this;
	}
	Point &operator -=(const Point &p) {
		x -= p.x, y -= p.y;
		return *this;
	}
	Point operator *(double d) {
		return Point(x*d,y*d);
	}
	double dot(Point p) {
		return x * p.x + y * p.y;
	}
	double det(Point p) {
		return x * p.y - y * p.x;
	}

};

constexpr int N = 300;

int T, w, l, n, m;
int u[N + 9][N + 9];
int s[N * N + 9], z[N * N + 9];
Point Pot[N * N + 9], Con[N * N + 9], F;

int hull(int n)
{
	std::sort(Pot,Pot+n);
	int m=0;
	for (int i=0;i<n;++i) {
		while (m>1 && (Con[m-1]-Con[m-2]).det(Pot[i]-Con[m-1])<0) --m;
		Con[m++]=Pot[i];
	}
	int t=m;
 	for (int i=n-2;i>=0;--i) {
		while (m>t && (Con[m-1]-Con[m-2]).det(Pot[i]-Con[m-1])<0) --m;
		Con[m++]=Pot[i];
	}
	return m-1;
}

int find(int e) {
	return s[e] == e? e : s[e] = find(s[e]);
}

void join(int a, int b) {
	z[b] += z[a];
	s[a] = b;
}

int calc(const Point &F) {
	int sum = 0;
	Point G;
	for (int i = 0; i < n; ++i) {
		s[i] = i;
		z[i] = 1;
	}
	for (int i = 0; i < n; ++i) {
		G = Pot[i] + F;
		if (0 <= G.x && G.x < w &&
			0 <= G.y && G.y < l &&
			~u[G.x][G.y]) join(find(i), find(u[G.x][G.y]));
	}
	for (int i = 0; i < n; ++i)
		if (s[i] == i) {
			if (z[i] == 1) return 0x7fffffff;
			else sum += (z[i] + 1) >> 1;
		}
	return sum;
}

int main() {
	scanf("%d\n", &T);
	while (T--) {
		scanf("%d%d%*c", &w, &l);
		memset(u, -1, sizeof u);
		n = 0;
		for (int i = 0; i < w; ++i) for (int j = 0; j <= l; ++j)
			if (getchar() == '#') {
				u[i][j] = n;
				Pot[n++] = Point(i, j);
			}
		m = hull(n);
		int ans = n;
		for (int i = 0, j; i < m; ++i) {
			for (j = i + 1; j < m; ++j)
				if ((Con[i + 1] - Con[i]).det(Con[j + 1] - Con[i])) break;
			F = Con[j] - Con[i];
			ans = std::min(ans, calc(F));
		}
		printf("%d\n", ans);
	}
	return 0;
}
