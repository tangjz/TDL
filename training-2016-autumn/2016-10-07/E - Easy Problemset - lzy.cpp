#include <cstdio>


int n, m, p[19], d[19][19];
int num;

int main() {
	freopen("easy.in", "r", stdin);
	freopen("easy.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i) {
		scanf("%d", p + i);
		for (int j = p[i] - 1; j >= 0; --j)
			scanf("%d", d[i] + j);
	}
	int sum = 0;
	LOOP: {
		for (int i = 0; i < n; ++i) {
			int c;
			if (p[i] > 0) {
				c = d[i][--p[i]];
			} else {
				p[i] = -1;
				c = 50;
			}
			//printf("%d %d %d %d\n", i, c, sum, num);
			if (c >= sum || num == n) {
				sum += c;
				if (--m == 0) goto END;
			}
			num += p[i] == 0;
		}
	} goto LOOP;
	END: printf("%d\n", sum);
	return 0;
}
