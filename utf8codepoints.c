#include <stdio.h>

int main(void) {
	while (1) {
		int codepoint = 0;
		int first = getc(stdin);
		if (first == EOF) return 0;
		if ((first & 0b10000000) == 0b00000000) {
			codepoint = first;
		} else if ((first & 0b11000000) == 0b10000000) {
			fprintf(stderr, "[invalid utf-8 (%x)]\n", first);
			codepoint = first;
		} else if ((first & 0b11100000) == 0b11000000) {
			int b = getc(stdin);
			if (b == EOF) return 1;
			codepoint = (first & 0b00011111) << 6 | (b & 0b00111111);
		} else if ((first & 0b11110000) == 0b11100000) {
			int b = getc(stdin);
			if (b == EOF) return 1;
			int c = getc(stdin);
			if (c == EOF) return 1;
			codepoint = (first & 0b00001111) << 12 | (b & 0b00111111) << 6 | (c & 0b00111111);
		} else if ((first & 0b11111000) == 0b11110000) {
			int b = getc(stdin);
			if (b == EOF) return 1;
			int c = getc(stdin);
			if (c == EOF) return 1;
			int d = getc(stdin);
			if (d == EOF) return 1;
			codepoint = (first & 0b00000111) << 18 | (b & 0b00111111) << 12 | (c & 0b00111111) << 6 | (d & 0b00111111);
		} else {
			fprintf(stderr, "[invalid utf-8 (%x)]\n", first);
		}
		printf("U+%x\n", codepoint);
	}
}
