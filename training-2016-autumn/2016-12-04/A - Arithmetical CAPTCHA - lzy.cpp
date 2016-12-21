#include <cstdio>

int main() {
	int TT;
	scanf("%d", &TT);
	for (int T = 1; T <= TT; ++T) {
		int a0, a1, a2, a3;
		scanf("%d%d%d%d", &a0, &a1, &a2, &a3);
		printf("Case #%d: ", T);
		if (a0 == a1 + a2 + a3) printf("%d = %d + %d + %d\n", a0, a1, a2, a3);
		else if (a0 == a1 + a2 - a3) printf("%d = %d + %d - %d\n", a0, a1, a2, a3);
		else if (a0 == a1 - a2 + a3) printf("%d = %d - %d + %d\n", a0, a1, a2, a3);
		else if (a0 == a1 - a2 - a3) printf("%d = %d - %d - %d\n", a0, a1, a2, a3);
		
		else if (a0 + a1 == a2 + a3) printf("%d + %d = %d + %d\n", a0, a1, a2, a3);
		else if (a0 + a1 == a2 - a3) printf("%d + %d = %d - %d\n", a0, a1, a2, a3);
		else if (a0 - a1 == a2 + a3) printf("%d - %d = %d + %d\n", a0, a1, a2, a3);
		else if (a0 - a1 == a2 - a3) printf("%d - %d = %d - %d\n", a0, a1, a2, a3);
		
		else if (a0 + a1 + a2 == a3) printf("%d + %d + %d = %d\n", a0, a1, a2, a3);
		else if (a0 - a1 + a2 == a3) printf("%d - %d + %d = %d\n", a0, a1, a2, a3);
		else if (a0 + a1 - a2 == a3) printf("%d + %d - %d = %d\n", a0, a1, a2, a3);
		else if (a0 - a1 - a2 == a3) printf("%d - %d - %d = %d\n", a0, a1, a2, a3);
		
		else if (a0 == a1 && a1 == a2 + a3) printf("%d = %d = %d + %d\n", a0, a1, a2, a3);
		else if (a0 == a1 && a1 == a2 - a3) printf("%d = %d = %d - %d\n", a0, a1, a2, a3);
		
		else if (a0 == a3 && a1 + a2 == a3) printf("%d = %d + %d = %d\n", a0, a1, a2, a3);
		else if (a0 == a3 && a1 - a2 == a3) printf("%d = %d - %d = %d\n", a0, a1, a2, a3);
		
		else if (a0 + a1 == a2 && a2 == a3) printf("%d + %d = %d = %d\n", a0, a1, a2, a3);
		else if (a0 - a1 == a2 && a2 == a3) printf("%d - %d = %d = %d\n", a0, a1, a2, a3);
		
		else if (a0 == a1 && a1 == a2 && a2 == a3) printf("%d - %d = %d = %d\n", a0, a1, a2, a3);
	}
}
