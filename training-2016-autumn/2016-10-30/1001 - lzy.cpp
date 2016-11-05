#include <cstdio>

int T, a, b, t;

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &a, &b);
		if (a < b) t = a, a = b, b = t;
		printf("%d\n", 2 * a + b);
	}
	return 0;
}
