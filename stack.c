#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char buf[4096];
int pos = -1;
int eof;

char *val;
char *tape;

int exit_code = 0;
int tape_size = 0;
int ptr = 0;

void buf_fill(int fd)
{
	if (pos < 0 || pos > 4096) {
		pos = 0;

		int n = read(fd, buf, 4096);

		if (n < 4096) {
			eof = n;
		}
	}
}

int buf_get(int fd)
{
	buf_fill(fd);

	if (pos == eof) {
		return -1;
	}

	int c = buf[pos];
	pos++;

	return c;
}

void buf_unget()
{
	if (pos > 0 && pos <= 4096) {
		pos--;
	}
}

int is_val(int c)
{
	return isdigit(c) || c == '-';
}

void get_val(int fd)
{
	if (val) {
		free(val);
		val = NULL;
	}

	buf_unget();

	int c = buf_get(fd);

	int start = pos;
	int end;

	while (is_val(c)) {
		c = buf_get(fd);
	}

	end = pos;

	buf_unget();

	int len = end - start;

	val = malloc(len + 1);
	val[len] = '\0';

	for (int i = 0; i < len; i++) {
		val[i] = buf[start + i - 1];
	}
}

int next(int fd)
{
	int c = buf_get(fd);

	if (is_val(c)) {
		get_val(fd);
		c = buf_get(fd);
	}

	return c;
}

int main(int argc, char **argv)
{
	argc--;
	argv++;

	int fd = 0;

	if (argc >= 1) {
		fd = open(argv[0], O_RDONLY);
	}

	if (fd < 0) {
		perror("failed to open file");
		return 1;
	}

	int c = next(fd);

	while (c != -1) {
		switch (c) {
		case '^':
			tape_size += atoi(val);

			if (tape_size < 0) {
				fprintf(stderr, "growing tape to negative size");
				exit_code = 1;
				goto end;
			}

			if ( ! tape) {
				tape = malloc(tape_size);
			} else {
				tape = realloc(tape, tape_size);
			}
			break;
		case '>':
			ptr += atoi(val);

			if (ptr < 0 || ptr > tape_size) {
				fprintf(stderr, "tape out of bounds\n");
				exit_code = 1;
				goto end;
			}
			break;
		case '=':
			if (ptr < 0 || ptr > tape_size) {
				fprintf(stderr, "tape out of bounds\n");
				exit_code = 1;
				goto end;
			}

			tape[ptr] = atoi(val);
			break;
		case '<':
			if (ptr < 0 || ptr > tape_size) {
				fprintf(stderr, "tape out of bounds\n");
				exit_code = 1;
				goto end;
			}

			printf("%c", tape[ptr]);
			break;
		}

		c = next(fd);
	}

end:
	if (tape) {
		free(tape);
		tape = NULL;
	}

	if (val) {
		free(val);
		val = NULL;
	}

	return exit_code;
}
