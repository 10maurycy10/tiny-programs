#include <stdio.h>

int is_emoji(int codepoint) {
    // Emoticons
    if ((codepoint >= 0x1F600) && (codepoint <= 0x1F64F)) return 1;
    // Dingbats
    if ((codepoint >= 0x2700) && (codepoint <= 0x27BF)) return 1;
    // Miscellaneous Symbols
    if ((codepoint >= 0x2600) && (codepoint <= 0x26FF)) return 1;
    // Miscellaneous Symbols and Pictographs
    if ((codepoint >= 0x1F300) && (codepoint <= 0x1F5FF)) return 1;
    // Supplemental Symbols and Pictographs
    if ((codepoint >= 0x1F900) && (codepoint <= 0x1F9FF)) return 1;
    // Symbols and Pictographs Extended-A
    if ((codepoint >= 0x1FA70) && (codepoint <= 0x1FAFF)) return 1;
    // Transport and Map Symbols
    if ((codepoint >= 0x1F680) && (codepoint <= 0x1F6FF)) return 1;
    return 0;
}

int main(void) {
	while (1) {
        // store the UTF-8 as well as the codepoint
		int codepoint = 0;
        int bytecount = 0;
        int buffer[16];
		int first = getc(stdin);
		if (first == EOF) return 0;
		if ((first & 0b10000000) == 0b00000000) {
            codepoint = first;
            bytecount = 1;
            buffer[0] = first;
		} else if ((first & 0b11000000) == 0b10000000) {
			fprintf(stderr, "[invalid utf-8 (%x)]\n", first);
			codepoint = first;
		} else if ((first & 0b11100000) == 0b11000000) {
			int b = getc(stdin);
			if (b == EOF) return 1;
            bytecount = 2;
            buffer[0] = first;
            buffer[1] = b;
			codepoint = (first & 0b00011111) << 6 | (b & 0b00111111);
		} else if ((first & 0b11110000) == 0b11100000) {
			int b = getc(stdin);
			if (b == EOF) return 1;
			int c = getc(stdin);
			if (c == EOF) return 1;
            bytecount = 3;
            buffer[0] = first;
            buffer[1] = b;
            buffer[2] = c;
			codepoint = (first & 0b00001111) << 12 | (b & 0b00111111) << 6 | (c & 0b00111111);
		} else if ((first & 0b11111000) == 0b11110000) {
			int b = getc(stdin);
			if (b == EOF) return 1;
			int c = getc(stdin);
			if (c == EOF) return 1;
			int d = getc(stdin);
			if (d == EOF) return 1;
            bytecount = 4;
            buffer[0] = first;
            buffer[1] = b;
            buffer[2] = c;
            buffer[3] = d;
			codepoint = (first & 0b00000111) << 18 | (b & 0b00111111) << 12 | (c & 0b00111111) << 6 | (d & 0b00111111);
		} else {
			fprintf(stderr, "[invalid utf-8 (%x)]\n", first);
		}
		if (!is_emoji(codepoint))
            for (int byte = 0; byte < bytecount; byte++) printf("%c", buffer[byte]);
	}
}
