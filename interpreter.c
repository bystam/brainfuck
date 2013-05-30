#include <stdio.h>
#include <stdlib.h>

char mem[30000] = {0};
char *ptr = mem;

void interpretBuffer(char *bytes, long len);

int main (int argc, char *argv[]) {
	char *bytes;
	long len;
	if (argc == 1) { // pipe from std in
		len = 0;
		long size = 1024;
		bytes = malloc(size);
		char c;
		while ((c = getchar()) != EOF) {
			bytes[len++] = c;
			if (len == size) {
				size *= 2;
				realloc(bytes, size);
			}
		}
	} else { // has input file name, use first one
		FILE *f = fopen(argv[1], "rb");
		fseek(f, 0, SEEK_END);
		long pos = ftell(f);
		fseek(f, 0, SEEK_SET);

		bytes = malloc(pos);
		len = pos;
		fread(bytes, pos, 1, f);
		fclose(f);
	}

	interpretBuffer (bytes, len);
	free(bytes); // free allocated memory
	return 0;
}

void interpretBuffer(char *bytes, long len) {
	int c;
	unsigned int index = 0;
    while (index < len) {
    	c = bytes[index];
    	switch (c) {
    		case '<':
    		ptr--;
    		break;
    		case '>':
    		ptr++;
    		break;
    		case '+':
    		(*ptr)++;;
    		break;
    		case '-':
    		(*ptr)--;
    		break;
    		case '.':
    		putchar(*ptr);
    		break;
    		case ',':
    		*ptr = getchar();
    		break;
    		case '[':
    		if (*ptr == 0)
    			while (bytes[++index] != ']');
    		break;
    		case ']':
			while (bytes[index--] != '[');
    		break;
    	}
    	index++;
	}
}