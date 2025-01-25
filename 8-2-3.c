#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <assert.h>

#undef NULL
#define NULL     0
#define EOF      (-1)
#define BUFSIZ   1024
#define OPEN_MAX 20 /* max #files open at once */
#define PERMS 0666 /* RW for owner, group, others */

typedef struct _flags {
	unsigned int can_read : 1;
	unsigned int can_write : 1;
	unsigned int no_buf : 1;
	unsigned int eof : 1;
	unsigned int err : 1;
} Flags;


typedef struct _iobuf {
	char *name; /* filename */
	int cnt; /* characters left */
	char *ptr; /* next character position */
	char *base; /* location of buffer */
	Flags flags; /* mode of file access */
	int fd;
} FILE;

FILE _iob[OPEN_MAX] = { /* stdin, stdout, stderr */
	{ "stdin", 0, (char *) 0, (char *) 0, { .can_read=1, .can_write=0, .no_buf=0, .eof=0, .err=0 }, 0 },
	{ "stdout", 0, (char *) 0, (char *) 0, { .can_read=0, .can_write=1, .no_buf=0, .eof=0, .err=0 }, 1 },
	{ "stderr", 0, (char *) 0, (char *) 0, { .can_read=0, .can_write=1, .no_buf=1, .eof=0, .err=0 }, 2 }
};

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p)     ((p)->flags.eof)
#define ferror(p)   ((p)->flags.err)
#define fileno(p)   ((p)->fd)

#define getc(p) (--(p)->cnt >= 0 ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x, p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x), p))

#define getchar() getc(stdin)
#define putchar(x) putc((x), stdout)

FILE *fopen(char *name, char *mode);
int fflush(FILE *);
int fclose(FILE *);

void print_file(int, FILE *);
void print_buffers(int);
void write_string(int, char *);
void write_int(int, int);
void write_flags(int, Flags);

#define err(s) write_string(2, s);

int main(int argc, char *argv[]) {
	char help[] = "Usage: copy FILE1 FILE2\n";
	char c;
	FILE *f1, *f2;

	if (argc != 3) {
		err(help);
		exit(EXIT_FAILURE);
	}

	if ((f1=fopen(argv[1], "r")) > 0) {
		if ((f2=fopen(argv[2], "w")) > 0) {
			while ((c=getc(f1)) != EOF)
				putc(c, f2);
		} else {
			err(help);
			err("ERROR: Couldn't open ");
			err(argv[2]);
			err(" for write\n");
			print_buffers(2);
			exit(EXIT_FAILURE);
		}
	} else {
		err(help);
		err("ERROR: Couldn't open ");
		err(argv[1]);
		err(" for read\n");
		print_buffers(2);
		exit(EXIT_FAILURE);
	}

	fclose(f1);
	fclose(f2);
	exit(EXIT_SUCCESS);
}

static char write_error_msg[] = "ERROR: write error";
void write_string(int fd, char *s) {
	int n;
	n = strlen(s);
	if (write(fd, s, n) != n) {
		write(2, write_error_msg, strlen(write_error_msg));
		exit(EXIT_FAILURE);
	}
}

void write_int(int fd, int n) {
	/*
	  123
	  write 12
	 */
	int div = n / 10;
	char c = '0' + n % 10;
	if (div > 0)
		write_int(fd, div);

	if (write(fd, &c, 1) != 1) {
		write(2, write_error_msg, strlen(write_error_msg));
		exit(EXIT_FAILURE);
	}
}

void write_flags(int fd, Flags flags) {
	write_string(fd, "/");
	if (flags.can_read)
		write_string(fd, "read/");
	if (flags.can_write)
		write_string(fd, "write/");
	if (flags.no_buf)
		write_string(fd, "nobuf/");
	if (flags.eof)
		write_string(fd, "eof/");
	if (flags.err)
		write_string(fd, "err/");

	if (!flags.can_read && !flags.can_write && !flags.no_buf && !flags.eof && !flags.err)
		write_string(fd, "/");
}

void print_file(int fd, FILE *f) {
	if (!f->flags.can_read && !f->flags.can_write)
		write_string(fd, "DEBUG: [AVAILABLE] ");
	else
		write_string(fd, "DEBUG: [BUSY] ");
	write_string(fd, "{ name=");
	write_string(fd, f->name ? f->name : "NULL");
	write_string(fd, ", cnt=");
	write_int(fd, f->cnt);
	write_string(fd, ", ptr=");
	if (f->ptr)
		write_string(fd, "NOT_NULL");
	else
		write_string(fd, "NULL");
	write_string(fd, ", base=");
	if (f->base)
		write_string(fd, "NOT_NULL");
	else
		write_string(fd, "NULL");
	write_string(fd, ", flags=");
	write_flags(fd, f->flags);
	write_string(fd, ", fd=");
	write_int(fd, f->fd);
	write_string(fd, " }");
}

void print_buffers(int fd) {
	int i;
	write_string(fd, "DEBUG: buffers ->\n");
	for (i = 0; i < OPEN_MAX; ++i) {
		print_file(fd, &_iob[i]);
		write_string(fd, "\n");
	}
	write_string(fd, "DEBUG: <- buffers\n");
}

FILE *fopen(char *name, char *mode) {
	int fd;
	FILE *fp;
	err("DEBUG: fopen: opening ");
	err(name);
	err(" with mode ");
	err(mode);
	err("\n");

	if (*mode != 'r' && *mode != 'w' && *mode != 'a') {
		err("ERROR: fopen: unknown mode\n");
		return NULL;
	}

	for (fp = _iob; fp < _iob + OPEN_MAX; ++fp) {
		if (!fp->flags.can_read && !fp->flags.can_write) {
			err("DEBUG: fopen: found free slot\n");
			break; /* found free slot */
		}
		if (fp >= _iob + OPEN_MAX) /* no free slots */ {
			return NULL;
			err("ERROR: fopen: couldn't found free slot\n");
		}
	}

	if (*mode == 'w') {
		err("DEBUG: fopen: opening for write\n");
		err("DEBUG: fopen: creating file\n");
		fd = creat(name, PERMS);
	}
	else if (*mode == 'a') {
		err("DEBUG: fopen: opening for append\n");
		if ((fd=open(name, O_WRONLY, 0)) == -1) {
			err("DEBUG: fopen: creating file\n");
			fd = creat(name, PERMS);
		}
		err("DEBUG: fopen: lseek to 0\n");
		lseek(fd, 0L, 2);
	} else {
		err("DEBUG: fopen: opening for read-only\n");
		fd = open(name, O_RDONLY, 0);
	}

	if (fd == -1) /* couldn't access name */ {
		err("DEBUG: couldn't access name\n");
		return NULL;
	}

	fp->fd = fd;
	fp->cnt = 0;
	fp->base = NULL;
	fp->name = strdup(name);
	if (*mode == 'r')
		fp->flags.can_read = 1;
	else
		fp->flags.can_write = 1;
	err("DEBUG: fopen: success!\n");
	print_buffers(2);
	return fp;
}



int _fillbuf(FILE *fp) {
	int bufsize;

	err("DEBUG: _filbuf: filling buffer for file ");
	err(fp->name);
	err("\n");
	if (!fp->flags.can_read || fp->flags.eof || fp->flags.err) {
		err("ERROR: _filbuf: flags are ");
		write_flags(2, fp->flags);
		err("\n");
		return EOF;
	}

	bufsize = fp->flags.no_buf ? 1 : BUFSIZ;
	err("DEBUG: _filbuf: bufsize=");
	write_int(2, bufsize);
	err("\n");

	if (fp->base == NULL) /* no buffer yet */ {
		if ((fp->base=(char *) malloc(bufsize)) == NULL) {
			err("ERROR: _filbuf: couldn't allocate buffer\n");
			return EOF; /* can't get buffer */
		}
		err("DEBUG: _filbuf: buffer has been successfully allocated\n");
	}

	fp->ptr = fp->base;
	err("DEBUG: _filbuf: ptr set to base\n");
	fp->cnt = read(fp->fd, fp->ptr, bufsize);
	err("DEBUG: _filbuf: read ");
	write_int(2, fp->cnt);
	err(" bytes\n");
	if (--fp->cnt < 0) {
		if (fp->cnt == -1) {
			fp->flags.eof = 1;
		}
		else {
			fp->flags.err = 1;
		}
		err("ERROR: _filbuf: couln't read buffer, flags=");
		write_flags(2, fp->flags);
		err("\n");
		fp->cnt = 0;
		return EOF;
	}

	err("DEBUG: _filbuf: read buffer successfully\n");
	return (unsigned char) *fp->ptr++;
}

int _flushbuf(int c, FILE *fp) {
	int bufsize, n;

	err("DEBUG: _flushbuf: flushing ");
	err(fp->name);
	err(", flags are ");
	write_flags(2, fp->flags);
	err("\n");

	if (fp->base == NULL) { /* no buffer yet */
		if ((fp->base = (char *) malloc(BUFSIZ)) == NULL) {
			err("ERROR: _flushbuf: couldn't allocate buffer\n");
			return EOF;
		}
		fp->cnt = BUFSIZ;
		fp->ptr = fp->base;
		err("DEBUG: _flushbuf: buffer of size ");
		write_int(2, fp->cnt);
		err(" has been successfully allocated\n");
		n = write(fp->fd, &c, 1);
		if (n == 1) {
			err("DEBUG: _flushbuf: char ");
			write(2, &c, 1);
			err(" has been written\n");
			return c;
		} else {
			err("ERROR: couldn't write char ");
			write(2, &c, 1);
			err("\n");
			return EOF;
		}
	}

	bufsize=fp->ptr - fp->base;
	err("DEBUG: _flushbuf: bufsize=");
	write_int(2, bufsize);
	err(", cnt=");
	write_int(2, fp->cnt);
	err("\n");

	if (bufsize > 0 && !fp->flags.err) { /* write buffer */
		err("DEBUG: _flushbuf: writting buffer\n");
		if ((n=write(fp->fd, fp->base, bufsize)) != bufsize) { /* failed to write */
			err("ERROR: _flushbuf: could write only ");
			write_int(2, n);
			err(" out of ");
			write_int(2, bufsize);
			err(" bytes\n");
			fp->flags.err = 1;
			return EOF;
		}
		fp->cnt = bufsize;
		err("DEBUG: _flushbuf: buffer of size ");
		write_int(2, bufsize);
		err(" has been successfully written, _flushbuf: set cnt to ");
		write_int(2, bufsize);
		err("\n");
	}

	/* for fflush */
	if (c == '\0') {
		err("DEBUG: _flushbuf: found '\0', not writing it\n");
		return c;
	}

	err("DEBUG: _flushbuf: writing ");
	write(2, &c, 1);
	err("\n");
	if (write(fp->fd, &c, 1) == 1) {
		err("DEBUG: _flushbuf: success!\n");
		return (unsigned char) c;
	} else {
		err("DEBUG: _flushbuf: failed, setting err\n");
		fp->flags.err = 1;
		return EOF;
	}
}

/* fflush: returns 0 if success, otherwise EOF */
int fflush(FILE *f) {
	err("DEBUG: fflush: flushing ");
	print_file(2, f);
	err("\n");
	if (_flushbuf(0, f) != 0) {
		f->flags.err = 1;
		err("ERROR: couldn't flush buffer!\n");
		return EOF;
	}

	err("DEBUG: fflush: success!\n");
	print_buffers(2);
	return 0;
}

/* fclose: returns 0 if success, otherwise EOF */
int fclose(FILE *f) {
	int n;
	err("DEBUG: fclose: closing ");
	print_file(2, f);
	err("\n");
	if ((n=fflush(f)) != 0 || close(f->fd) != 0) {
		f->flags.err = 1;
		err("ERROR: couldn't close!\n");
		return EOF;
	}
	f->flags.can_read = 0;
	f->flags.can_write = 0;
	free(f->base);
	free(f->name);
	f->base = NULL;
	f->name = NULL;
	err("DEBUG: fclose: success\n");
	print_buffers(2);
}
