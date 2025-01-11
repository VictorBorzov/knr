#ifndef CALC
#define CALC

#define MAXOP 20 /* max size of operand or operator */

#define NUMBER '0' /* signal that a number was found */
#define COMMAND '1' /* signal that a command was found */
#define VAR '2' /* signal that a variable was found */

/* user input parser */
void parse(const char[], int, int);
int getline2(char buffer[], int lim);

/* stack operations */
void push(double);
double pop(void);
char popvarname(void);
void printstack(void);
void printvars(void);
double gettop(void);
void duplicatetop(void);
void swaplastwo(void);
void clear(void);
void initstackflags(void);
void pushvar(char);
void setvar(char name, double value);
void hvar(char); /* handle variable */
void hnum(double); /* handle number */
void hcom(char[]); /* handle command */
void hunknown(void); /* handle unknown */

/* utils */
int strcmp(char[], char[]); /* compare strings */
#endif
