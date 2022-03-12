#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 1024

int main(int argc, char **argv) {
	int files = argc - 1;
	if (argc == 1) {
		printf("%s: A program to xor files\n", argv[0]);
		printf("usage: %s file1 file2\n", argv[0]);
		return 1;
	}
	FILE **handles = malloc(sizeof(FILE*) * files);
	for (int i = 0; i < files; i++) {
		handles[i] = fopen(argv[i + 1], "r");
		if (!handles[i]) {
			fprintf(stderr,"Cant open '%s'.\n", argv[i + 1]);
			return 1;
		}
	}

	while (1) {
		// Alocate 2 zerod
		char *buffer = malloc(BUFFER);
		memset(buffer, 0, BUFFER);
		char* read_buffer = malloc(BUFFER);
		memset(read_buffer, 0, BUFFER);

		int bytes_read = 0;
		int max_bytes_read = 0;

		// read all files into buffer
		for (int i = 0; i < files; i++) {
			memset(read_buffer, 0, BUFFER);
			bytes_read = fread(read_buffer, 1, BUFFER, handles[i]);
			if (bytes_read > max_bytes_read)
				max_bytes_read = bytes_read;
			for (int e = 0; e < bytes_read; e++)
				buffer[e] ^= read_buffer[e];
		}
		// if no data was read we have reached EOF on all files, exit.
		if (max_bytes_read == 0)
			break;

		for (int i = 0; i < max_bytes_read; i++)
			putc(buffer[i],stdout);
	}
	for (int i = 0; i < files; i++) {
		fclose(handles[i]);
	}
	free(handles);
	return 0;
}
