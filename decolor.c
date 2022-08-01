/* Removes color information (SGR escape codes from a text stream) */

#include <stdio.h>
#include <stdlib.h>

int get_or_exit() {
	/* Gets a char from standard input and calls exit(0) on EOF */
	int c = getc(stdin);
	if (c == EOF) {
		exit(0);
	} else {
		return c;
	}
}

int main() {
	while (1) {
		int a = get_or_exit();
		if (a == 0x1b) {
			int b = get_or_exit();
			if (b == '[') {
				/* Is a SGR code */
				int c = 0;
				do {
					c = getc(stdin);
					if (c == EOF) {
						fprintf(stderr, "Unterminated SGR code.\n");
						exit(0);
					}
				} while (c != 'm');
			} else {
				/* Not a SGR code */
				putc(a, stdout);
				putc(b, stdout);
			}
		} else {
			/* Not a escape code, pass out */
			putc(a, stdout);
		}
	}
}
