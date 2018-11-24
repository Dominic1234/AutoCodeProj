#include <stdio.h>
#include <unistd.h>
#include <termios.h>

#define strcmpi strcmp
#undef CFLAGS
#define CFLAGS ""

#undef COMP_FILE
#undef TC_FILE
#undef OUT_FILE
#undef EXP_FILE

#define COMP_FILE	"submit/tmp/a.exe"
#define TC_FILE		"submit/tmp/tc.txt"
#define OUT_FILE	"submit/tmp/output.txt"
#define EXP_FILE	"submit/tmp/expected.txt"

int getch() {
	int c;
	struct termios old, mod;
	tcgetattr(STDIN_FILENO, &old);
	mod = old;
	mod.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &mod);
	c = getc(stdin);
	tcsetattr(STDIN_FILENO, TCSANOW, &old);
	return c;
}
