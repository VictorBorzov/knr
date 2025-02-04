#include <stdio.h>
#include <string.h>
#include <pwd.h>
#include "8.4-sys.c"

DIR *opendir(const char *dirname);
struct dirent *readdir(DIR *dfd);
int closedir(DIR *dfd);

void fsize(char *);

int test(char *);

int main(int argc, char *argv[]) {
	/* return test("/home/vb/src/kernighan-ritchie"); */
	fprintf(stdout, "PERM Type Links Size\t\t USER Name\n");
	if (argc == 1) /* default: current directory */
		fsize(".");
	else
		while (--argc > 0) {
			fsize(*++argv);
		}
	return 0;
}

/* int stat(char *, struct stat *); */
void dirwalk(char *, void (*fcn) (char *));

/* fsize: print the name of file "name" */
void fsize(char *name) {
	struct stat stbuf;

	fprintf(stderr, "DEBUG: fsize: calculating the size of %s\n", name);
	if (stat(name, &stbuf) == -1) {
		fprintf(stderr, "ERROR: fsize: can't access %s\n", name);
		return;
	}
	if ((stbuf.st_mode & S_IFMT) == S_IFDIR) {
		fprintf(stderr, "DEBUG: fsize: %s is a directory, dirwalking...\n", name);
		dirwalk(name, fsize);
	}

	struct passwd *p = getpwuid(stbuf.st_uid);

	printf("%04o %s %6d %-8ld\t %s   %s\n",
		(stbuf.st_mode & 0777),
		S_ISREG(stbuf.st_mode) ? "FIL" :
		S_ISDIR(stbuf.st_mode) ? "DIR" : "OTH",
		stbuf.st_nlink,
		stbuf.st_size,
		p->pw_name,
		name);
}

#define MAX_PATH 1024

/* dirwalk: apply fcn to all files in dir */
void dirwalk(char *dir, void (*fcn)(char *)) {
	char name[MAX_PATH];
	struct dirent *d;
	DIR *dfd;

	fprintf(stderr, "DEBUG: dirwalk: walking through %s\n", dir);
	if ((dfd=opendir(dir)) == NULL) {
		fprintf(stderr, "ERROR: dirwalk: can't open %s\n", dir);
		return;
	}

	fprintf(stderr, "DEBUG: dirwalk: reading %s\n", dfd->d.d_name);
	while ((d=readdir(dfd)) != NULL) {
		fprintf(stderr, "DEBUG: dirwalk: checking %s\n", d->d_name);
		if (d->d_name[0] == '.' || strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0) {
			fprintf(stderr, "DEBUG: dirwalk: skipping\n");
			continue; /* skip self and parent */
		}
		if (strlen(dir) + strlen(d->d_name) + 2 > sizeof(name)) {
			fprintf(stderr, "ERROR: dirwalk name %s %s too long\n", dir, d->d_name);
		} else {
			sprintf(name, "%s/%s", dir, d->d_name);
			fprintf(stderr, "DEBUG: dirwalk: fsize on %s\n", name);
			(*fcn)(name);
		}
	}

	fprintf(stderr, "DEBUG: dirwalk: closing %s\n", dir);
	closedir(dfd);
}
