#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_WORD_LEN 256
#define BUFFER_BLOCK_SIZE 16

int main(int argc, char **argv) {
	if (argc != 2) {
		printf("usage: %s LEN\n", argv[0]);
		printf("password list is stdin.\n");
		return 1;
	}
	
	char *wordlist_buffer = malloc(MAX_WORD_LEN * BUFFER_BLOCK_SIZE);
	int cur_buffer_cap = BUFFER_BLOCK_SIZE;
	int cur_buffer_len = 0;

	while (1) {
		char* ret = fgets(&wordlist_buffer[cur_buffer_len * MAX_WORD_LEN], MAX_WORD_LEN, stdin);
		if (!ret)
			break;
		cur_buffer_len++;
		if (cur_buffer_len == cur_buffer_cap) {
			wordlist_buffer = realloc(wordlist_buffer, (cur_buffer_cap + BUFFER_BLOCK_SIZE) * MAX_WORD_LEN);
			cur_buffer_cap += BUFFER_BLOCK_SIZE;
		}
	}

	if (cur_buffer_len == 0) {
		printf("Empty password list!!");
		return 1;
	}
	
	printf("Random password is : ");

	char *passlenstr = argv[1];
	int passlen = atoi(passlenstr);
	for (int i = 0; i < passlen; i++) {
		unsigned int idx = 0;
		getrandom(&idx, sizeof(int), 0);
		idx = idx%cur_buffer_len;
		char* word = &wordlist_buffer[MAX_WORD_LEN * idx];
		for (int i = 0; word[i]; i++) {
			if (word[i] == '\n')
				break;
			if (i > MAX_WORD_LEN)
				break;
			printf("%c", word[i]); 
		}
	}
	printf("\n\n");

	double words = cur_buffer_len;
	double bits_per_word = log2f(words);
	double len = passlen;
	double bits_per_password = len*bits_per_word;
	double passwords = powf(2.0,bits_per_password);
	printf("word list size is %f (2^%f)\n", words, bits_per_word);
	printf("entropy per password is %f bits\n", bits_per_password);
	printf("possible passwords: %.6f\n\n", passwords);
	double s = passwords / 1000.0;
	double h_s = fmod(s, 60.0);
	double h_m = fmod(s/60.0, 60.0);
	double h_h = fmod(s/60.0/60.0, 60.0);
	double h_d = fmod(s/86400.0, 30.0);
	double h_y = (s/31536000.0);
	printf("Best case time to crack with web buteforce (1000 passwords/s) %ds, %dm, %dh, %dd, %uy\n", (int)h_s, (int)h_m,(int)h_h, (int)h_d, (unsigned int)h_y);
	
	s = passwords / 1000.0 / 1000.0 / 1000.0;
	h_s = fmod(s,60.0);
	h_m = fmod(s/60.0,60.0);
	h_h = fmod(s/60.0/60.0,60.0);
	h_d = fmod(s/86400.0,30.0);
	h_y = s/31536000.0;
	printf("Best case time to crack with stolen hash (1000,000,000 passwords/s) %ds, %dm, %dh, %dd, %uy\n", (int)h_s, (int)h_m,(int)h_h, (int)h_d, (unsigned int)h_y);
	
	printf("Typical time will be half of best case.\n");

	return 0;
}
