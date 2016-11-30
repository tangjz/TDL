#include <cctype>
#include <cstdio>

int c;

int main() {
	LOOP: {
		bool f = false;
		int d = 0;
		for (;;) {
			f = !f;
			c = getchar();
			if (c == '\n') break;
			if (c == EOF) goto OUT;
			if (isdigit(c)) d = (d << 4) + (c - '0');
			else d = (d << 4) + (c - 'A' + 10);
			if (!f) {
				putchar(d);
				d = 0;
			}
		}
		putchar('\n');
	}
	goto LOOP;
	OUT:
	return 0;
}
