#include <stdio.h>

int main(void) {
	while (1) {
		int a = getc(stdin);
		if (a == EOF) return 0;
		if (a & 0b10000000) {
			//getc(stdin);
			if (a & 0b01000000) {
				getc(stdin);
				if (a& 0b00100000) {
					getc(stdin);
					if (a& 0b00010000) {
						getc(stdin);
					}
				}
			}
		} else putc(a,stdout);
	}
}
