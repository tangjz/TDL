#include <cstdio>

typedef unsigned u32;
typedef long long u64;

const u32 mod = 2147493647;

const u32 b[7][7] = {
	1, 2, 1, 0, 0, 0, 0,
	1, 0, 0, 0, 0, 0, 0,
	0, 0, 1, 4, 6, 4, 1,
	0, 0, 0, 1, 3, 3, 1,
	0, 0, 0, 0, 1, 2, 1,
	0, 0, 0, 0, 0, 1, 1,
	0, 0, 0, 0, 0, 0, 1
};

u32 n;
u32 x[7] = {0, 0, 81, 27, 9, 3, 1};
u32 d[7][7], a[7][7];

void mul(u32 a[7][7], u32 b[7][7]) {
	static u64 t[7][7];
	for (int i = 0; i < 7; ++i)
		for (int j = 0; j < 7; ++j) {
			t[i][j] = 0;
			for (int k = 0; k < 7; ++k)
				t[i][j] += (u64)a[i][k] * b[k][j] % mod;
		}
	for (int i = 0; i < 7; ++i)
		for (int j = 0; j < 7; ++j)
			a[i][j] = t[i][j] % mod;
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%u%u%u", &n, x + 1, x);
		if (n == 1) {
			printf("%u\n", x[1] % mod);
			continue;
		}
		if (n == 2) {
			printf("%u\n", x[0] % mod);
			continue;
		}
		n -= 2;
		for (int i = 0; i < 7; ++i)
			for (int j = 0; j < 7; ++j) {
				d[i][j] = i == j;
				a[i][j] = b[i][j];
			}
				
		do {
			if (n & 1) mul(d, a);
			mul(a, a);
		} while (n >>= 1);
		u64 ans = 0;
		for (int i = 0; i < 7; ++i)
			ans += (u64)d[0][i] * x[i] % mod;
		printf("%u\n", (u32)(ans % mod));
	}
	return 0;
}
