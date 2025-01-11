#include <stdio.h>

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

struct point {
	int x;
	int y;
};

struct rect { struct point p1; struct point p2; };

struct point makepoint(int x, int y);
struct point addpoints(struct point, struct point);

int ptinrect(struct point p, struct rect r);
struct rect canonrect(struct rect r); /* make p1 coords are less than p2 */

void printpoint(struct point *p);

int main(void) {
	struct rect screen;
	struct point middle;

	struct { int len; char *str; } *p;
	struct rect *s;

	s = &screen;
	printf("%i\n", s->p1.x++);
	printf("%i\n", s->p1.x);
	printf("%p\n", screen);
	screen = NULL;
	printf("%p\n", screen);
	return 0;
	screen.p1 = makepoint(0, 0);
	screen.p2 = makepoint(1920, 1080);

	middle = makepoint(
		(screen.p1.x + screen.p2.x) / 2,
		(screen.p1.y + screen.p2.y) / 2);

	printpoint(&middle);
	printf("%s\n", ptinrect(middle, screen) ? "inside" : "outside");
	middle = addpoints(middle, middle);
	printpoint(&middle);

	printf("%s\n", ptinrect(middle, screen) ? "inside" : "outside");
}

void printpoint(struct point *p) {
	printf("(%d, %d)\n", p->x, p->y);
}

struct point makepoint(int x, int y) {
	struct point temp = { x, y };
	return temp;
}

struct point addpoints(struct point p1, struct point p2) {
	p1.x += p2.x;
	p1.y += p2.y;
	return p1;
}

/* ptinrect: return 1 if p in r, 0 if not */
int ptinrect(struct point p, struct rect r) {
	return
		p.x >= r.p1.x && p.x < r.p2.x &&
		p.y >= r.p1.y && p.y < r.p2.y;
}

/* canonrect: make p1 coords are less than p2 */
struct rect canonrect(struct rect r) {
	struct rect temp;
	temp.p1.x = min(r.p1.x, r.p2.x);
	temp.p1.y = min(r.p1.y, r.p2.y);
	temp.p2.x = max(r.p1.x, r.p2.x);
	temp.p2.y = max(r.p1.y, r.p2.y);
	return temp;
}

