#include <cstdio>

int T, h, c, o;
char mol[19];

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%s", mol);
		int m = 0;
		for (auto p = mol; *p; ++p) {
			if (*p == 'H') ++m;
			else if (*p == 'C') m += 12;
			else if (*p == 'O') m += 16;
		}
		printf("%d\n", m);
	}
	return 0;
}
