#include <stdlib.h> /* malloc */
#include <unistd.h> /* close */
#include <fcntl.h>		/* open */
#include <errno.h>
#include <err.h>
#include <sys/stat.h>		/* stat/fstat */
#include <sys/syscall.h>	/* syscall */
#include <stdint.h>		/* intmax_t */

#define NAME_MAX 14 /* longest filename component, system-dependent */

#ifndef DIRSIZ
#define DIRSIZ 30
#endif

struct dirent { /* directory entry */
	unsigned long d_ino; /* inode number */
	off_t d_off;
	unsigned short d_reclen;
	char d_name[DIRSIZ+1];
};

typedef struct { /* minimal DIR: no buffering, etc */
	int fd; /* file descriptor for the directory */
	struct dirent d; /* the directory entry */
} DIR;

DIR *opendir(const char *dirname);
struct dirent *readdir(DIR *dfd);
int closedir(DIR *dfd);
int fstat(int fd, struct stat *);

int test(char *);

#define BUF_SIZ 1000000

int test(char *s) {
	size_t bpos = 0;
	int n = 0, j;
	char buf[BUF_SIZ], d_type;
	DIR *d;
	struct dirent *entry;

	d = opendir(s);
	errno = 0;
	if ((d=opendir(s)) == NULL) {
		err(1, "ERROR: couldn't open %s as a directory\n", s);
		/* fprintf(stderr, "ERROR: couldn't open %s as a directory\n", s); */
		/* perror("ERROR"); */
		/* return 1; */
	}

	errno = 0;
	n = syscall(SYS_getdents, d->fd, buf, BUF_SIZ);
	fprintf(stderr, "DEBUG: getdents returned %d\n", n);
	if (n == -1) {
		err(1, "ERROR: getdents failed\n");
		/* fprintf(stderr, "ERROR: getdents failed\n"); */
		/* perror("ERROR"); */
		return 1;
	}
	printf("--------------- nread=%ld ---------------\n", n);
	for (bpos=0, j=0; bpos < n; bpos += entry->d_reclen) {
		entry = (struct dirent *) (buf + bpos);
		fprintf(stdout, "%3d %8lu  ", j++, entry->d_ino);
		fprintf(stdout, "%4d %10jd  %s\n", entry->d_reclen,
			(intmax_t) entry->d_off, entry->d_name);
	}
	errno = 0;
	if ((n=closedir(d)) == EOF) {
		err(1, "ERROR: closing dir failed\n");
		/* fprintf(stderr, "ERROR: closing dir failed\n"); */
		/* if (errno != 0) */
		/* 	perror("ERROR"); */
		return 1;
	}
	return 0;
}

/* opendir: open a directory for readdir calls */
DIR *opendir(const char *dirname) {
	int fd;
	struct stat stbuf;
	DIR *d;

	if ((fd=open(dirname, O_RDONLY, 0)) == -1 ||
		fstat(fd, &stbuf) == -1 ||
		(stbuf.st_mode & S_IFMT) != S_IFDIR ||
		(d=(DIR *) malloc(sizeof(DIR))) == NULL) {
		fprintf(stderr, "ERROR: opendir: couldn't open %s\n", dirname);
		return NULL;
	}
	strcpy(d->d.d_name, dirname);
	d->fd = fd;

	return d;
}

#define BUF_SIZE 1000000
#define MAX_NESTED 100
static char buf[BUF_SIZE * MAX_NESTED] = {}; /* contains all dirents read from all fds */
static int nreads[MAX_NESTED] = {};		     /* number of bytes read for fd */
static int bpos[MAX_NESTED] = {};		     /* last position for fd */
static char *dirs[MAX_NESTED] = {};		     /* read dir names */
static int reads = 0;				     /* number fd read */

/* find_dir: returns an index from dirs or -1 if not found */
int find_dir(DIR *d) {
	int i;
	for (i = 0; i < MAX_NESTED; ++i)
		if (dirs[i] != NULL && strcmp(d->d.d_name, dirs[i]) == 0)
			return i;
	return -1;
}

/* closedir: close directory opened by opendir */
int closedir(DIR *d) {
	int i;

	if (d) {
		fprintf(stderr, "DEBUG: closedir: closing %s\n", d->d.d_name);
		close(d->fd);
		free(d);

		i = find_dir(d);
		if (i == -1) {
			err(1, "ERROR: closedir: can't find %s in dirs\n", d->d.d_name);
			free(dirs[i]);
		}
		dirs[i] = NULL;
		bpos[i] = 0;
		nreads[i] = 0;
		--reads;
	}
}

int slen(char *s) {
	int i;
	for (i = 0; *s != '\0'; ++i, ++s);
	return i;
}

/* readdir: read directories entries in sequence */
struct dirent *readdir(DIR *dp) {
	int i, j;
	char *s;
	struct dirent *entry;

	fprintf(stderr, "DEBUG: readdir: trying to strdup %s\n", dp->d.d_name);
	s = strdup(dp->d.d_name);
	fprintf(stderr, "DEBUG: readdir: success! freeing...\n");
	free(s);
	fprintf(stderr, "DEBUG: readdir: success!\n");

	fprintf(stderr, "DEBUG: readdir: reading %s (%d)\n", dp->d.d_name, dp->fd);

	if (dp == NULL) {
		fprintf(stderr, "ERROR: readdir: dp is NULL\n");
		return NULL;
	}
	i = find_dir(dp);

	if (i == -1) {	/* load new fd */
		fprintf(stderr, "DEBUG: readdir: loading new fd for %s\n", dp->d.d_name);
		if (reads >= MAX_NESTED) {
			fprintf(stderr, "ERROR: readdir: can't read another dir\n");
			return NULL;
		}
		i = reads;	/* index is gonna be the next one */
		bpos[i] = 0;
		fprintf(stderr, "DEBUG: readdir: duplicating %s with len %d\n", dp->d.d_name, slen(dp->d.d_name));
		fprintf(stderr, "DEBUG: readdir: i=%d\n", i);
		dirs[i] = strdup(dp->d.d_name);
		fprintf(stderr, "DEBUG: readdir: %s duplicated\n", dp->d.d_name);
		errno = 0;
		nreads[i] = syscall(SYS_getdents, dp->fd, (buf + reads * BUF_SIZE), BUF_SIZE);
		if (errno != 0)
			perror("ERROR: getdents");
		if (nreads[i] == -1) {
			fprintf(stderr, "ERROR: getdents failed\n");
			return NULL;
		}
		++reads;
		/* fprintf(stderr, "DEBUG: entries in %s:\n", dp->d.d_name); */
		/* fprintf(stderr, "--------------- nread=%ld ---------------\n", nreads[i]); */
		/* fprintf(stderr, "bpos=%d,nread=%d\n", bpos[i], nreads[i]); */
		/* j = 0; */
		/* while (bpos[i] < nreads[i]) { */
		/* 	entry = (struct dirent *) (buf + i * BUF_SIZE + bpos[i]); */
		/* 	fprintf(stdout, "%3d %8lu  ", j++, entry->d_ino); */
		/* 	fprintf(stdout, "%4d %10jd  %s\n", entry->d_reclen, */
		/* 		(intmax_t) entry->d_off, entry->d_name); */
		/* 	bpos[i] += entry->d_reclen; */
		/* } */
		/* fprintf(stderr, "DEBUG: exiting...\n"); */
		/* err(1, "DEBUG"); */

	}

	fprintf(stderr, "DEBUG: readdir: on index %d\n", i);

	if (bpos[i] >= nreads[i]) {
		fprintf(stderr, "ERROR: readdir: bpos=%d,nread=%d\n", bpos[i], nreads[i]);
		return NULL;
	}

	entry = (struct dirent *) (buf + i * BUF_SIZE + bpos[i]);
	bpos[i] += entry->d_reclen;

	fprintf(stderr, "DEBUG: readdir: read %s\n", entry->d_name);
	return entry;
}
